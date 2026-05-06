#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <optional>
#include <utility>

using namespace std;

struct Node {
    int r, c;
};

bool inBounds(int r, int c, int R, int C) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

int main(int argc, char* argv[]) {
    string filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        cout << "Enter maze filename: ";
        cin >> filename;
    }

    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: could not open file " << filename << "\n";
        return 1;
    }

    int R, C;
    fin >> R >> C;

    vector<vector<char>> maze(R, vector<char>(C));
    int startRow = -1, startCol = -1;
    int endRow = -1, endCol = -1;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            fin >> maze[r][c];
            if (maze[r][c] == 'S') {
                startRow = r;
                startCol = c;
            } else if (maze[r][c] == 'E') {
                endRow = r;
                endCol = c;
            }
        }
    }

    if (startRow == -1 || endRow == -1) {
        cerr << "Error: missing start or end position.\n";
        return 1;
    }

    char choice;
    cout << "Solve with BFS or DFS? (b/d): ";
    cin >> choice;
    bool useBFS = (choice == 'b' || choice == 'B');

    vector<vector<bool>> visited(R, vector<bool>(C, false));
    vector<vector<bool>> discovered(R, vector<bool>(C, false));
    vector<vector<pair<int,int>>> parent(R, vector<pair<int,int>>(C, {-1, -1}));
    vector<vector<bool>> onPath(R, vector<bool>(C, false));

    queue<Node> q;
    stack<Node> s;

    discovered[startRow][startCol] = true;
    if (useBFS) q.push({startRow, startCol});
    else s.push({startRow, startCol});

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(15 * C),
                                   static_cast<unsigned int>(15 * R))),
        "Maze Visualizer"
    );

    bool searchDone = false;
    bool found = false;

    while (window.isOpen()) {
        while (const optional<sf::Event> event = window.pollEvent()) {
            // Window closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Key pressed
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape ||
                    keyPressed->code == sf::Keyboard::Key::Q) {
                    window.close();
                }
            }
        }

        if (!searchDone) {
            Node cur;
            bool hasNode = false;

            if (useBFS) {
                if (!q.empty()) {
                    cur = q.front();
                    q.pop();
                    hasNode = true;
                }
            } else {
                if (!s.empty()) {
                    cur = s.top();
                    s.pop();
                    hasNode = true;
                }
            }

            if (hasNode) {
                if (!visited[cur.r][cur.c]) {
                    visited[cur.r][cur.c] = true;

                    if (cur.r == endRow && cur.c == endCol) {
                        cout << "End reached.\n";
                        found = true;
                        searchDone = true;
                    } else {
                        const int dr[4] = {-1, 1, 0, 0};
                        const int dc[4] = {0, 0, -1, 1};

                        for (int i = 0; i < 4; i++) {
                            int nr = cur.r + dr[i];
                            int nc = cur.c + dc[i];

                            if (inBounds(nr, nc, R, C) &&
                                !visited[nr][nc] &&
                                maze[nr][nc] != '#' &&
                                !discovered[nr][nc]) {
                                discovered[nr][nc] = true;
                                parent[nr][nc] = {cur.r, cur.c};

                                if (useBFS) q.push({nr, nc});
                                else s.push({nr, nc});
                            }
                        }
                    }
                }
            } else {
                searchDone = true;
            }

            if (searchDone && found) {
                pair<int,int> cur = {endRow, endCol};
                while (cur.first != -1 && cur.second != -1) {
                    onPath[cur.first][cur.second] = true;
                    if (cur.first == startRow && cur.second == startCol) break;
                    cur = parent[cur.first][cur.second];
                }
            }
        }

        window.clear();

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                sf::RectangleShape cell(sf::Vector2f(15.f, 15.f));
                cell.setPosition(sf::Vector2f(static_cast<float>(c * 15),
                                               static_cast<float>(r * 15)));

                if (maze[r][c] == '#') {
                    cell.setFillColor(sf::Color::Black);
                } else if (maze[r][c] == 'S') {
                    cell.setFillColor(sf::Color::Green);
                } else if (maze[r][c] == 'E') {
                    cell.setFillColor(sf::Color::Red);
                } else if (onPath[r][c]) {
                    cell.setFillColor(sf::Color::Yellow);   // final path
                } else if (visited[r][c]) {
                    cell.setFillColor(sf::Color::Magenta);  // visited cells
                } else if (discovered[r][c]) {
                    cell.setFillColor(sf::Color::Blue);     // frontier
                } else {
                    cell.setFillColor(sf::Color::White);    // unvisited
                }

                window.draw(cell);
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(50));
    }

    return 0;
}
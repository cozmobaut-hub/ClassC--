#include "ConnectFourGame.h"

#include <iostream>
#include <limits>
#include <string>
using namespace std;

const string SAVE_FILENAME = "connect4_save.txt";
const string STATS_FILENAME = "connect4_stats.txt";

/**
 * @brief Read an integer from cin within [minVal, maxVal]
 * @desc Performs input validation and reprompts on invalid input.
 * @param prompt message to display
 * @param minVal minimum acceptable value
 * @param maxVal maximum acceptable value
 * @return int valid integer entered by the user
 */
int get_int_in_range( const string& prompt, int minVal, int maxVal ) {
  int value;
  while( true ) {
    cout << prompt;
    cin >> value;

    if( cin.fail() ) {
      cout << "Invalid input. Please enter an integer." << endl;
      cin.clear();
      cin.ignore( numeric_limits<streamsize>::max(), '\n' );
      continue;
    }
    if( value < minVal || value > maxVal ) {
      cout << "Value must be between " << minVal << " and "
           << maxVal << "." << endl;
      continue;
    }
    cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    return value;
  }
}

/**
 * @brief Display the main menu and get user choice
 * @return int menu selection
 */
int display_main_menu() {
  cout << "=== Connect 4 (Console) ===" << endl;
  cout << "1. Start new game" << endl;
  cout << "2. Load saved game" << endl;
  cout << "3. Show stats" << endl;
  cout << "4. Quit" << endl;
  cout << endl;

  return get_int_in_range( "Enter choice (1-4): ", 1, 4 );
}

/**
 * @brief Run a single game session (new or loaded)
 * @param game reference to game object
 * @return true if user finished this game (win or tie)
 * @return false if user chose to save and return to menu
 */
bool run_game_loop( ConnectFourGame& game ) {
  bool gameOver = false;
  while( !gameOver ) {
    game.printBoard();
    cout << "Current player: " << game.getCurrentPlayer() << endl;
    cout << "Enter column (0-6) to drop, or -1 to save and return to menu." << endl;

    int columnChoice;
    cout << "Column: ";
    cin >> columnChoice;

    if( cin.fail() ) {
      cout << "Invalid input. Please enter an integer." << endl;
      cin.clear();
      cin.ignore( numeric_limits<streamsize>::max(), '\n' );
      continue;
    }

    if( columnChoice == -1 ) {
      cin.ignore( numeric_limits<streamsize>::max(), '\n' );
      if( game.saveGameToFile( SAVE_FILENAME ) ) {
        cout << "Game saved to " << SAVE_FILENAME << "." << endl;
      } else {
        cout << "Error saving game." << endl;
      }
      return false;
    }

    cin.ignore( numeric_limits<streamsize>::max(), '\n' );

    if( columnChoice < 0 || columnChoice > 6 ) {
      cout << "Column must be between 0 and 6." << endl;
      continue;
    }

    if( game.isColumnFull( columnChoice ) ) {
      cout << "That column is full. Choose another column." << endl;
      continue;
    }

    int lastRow = 0;
    int lastCol = 0;
    const bool placed = game.dropPiece( columnChoice, lastRow, lastCol );
    if( !placed ) {
      cout << "Could not place piece. Try again." << endl;
      continue;
    }

    if( game.checkWin( lastRow, lastCol ) ) {
      game.printBoard();
      cout << "Player " << game.getCurrentPlayer() << " wins!" << endl;
      game.recordWin();
      return true;
    }

    if( game.checkTie() ) {
      game.printBoard();
      cout << "The game is a tie." << endl;
      return true;
    }

    game.switchPlayer();
  }

  return true;
}

int main( int argc, char* argv[] ) {
  (void)argc;
  (void)argv;

  ConnectFourGame game;

  if( game.loadStatsFromFile( STATS_FILENAME ) ) {
    cout << "Loaded stats from " << STATS_FILENAME << "." << endl;
  } else {
    cout << "No stats file found. Starting fresh stats." << endl;
  }

  bool running = true;
  while( running ) {
    cout << endl;
    int choice = display_main_menu();

    if( choice == 1 ) {
      game.resetBoard();
      bool finished = run_game_loop( game );
      if( finished ) {
        if( game.saveStatsToFile( STATS_FILENAME ) ) {
          cout << "Stats saved." << endl;
        } else {
          cout << "Error saving stats." << endl;
        }
      }
    } else if( choice == 2 ) {
      const bool loaded = game.loadGameFromFile( SAVE_FILENAME );
      if( !loaded ) {
        cout << "Failed to load saved game from "
             << SAVE_FILENAME << "." << endl;
      } else {
        cout << "Loaded saved game from " << SAVE_FILENAME << "." << endl;
        bool finished = run_game_loop( game );
        if( finished ) {
          if( game.saveStatsToFile( STATS_FILENAME ) ) {
            cout << "Stats saved." << endl;
          } else {
            cout << "Error saving stats." << endl;
          }
        }
      }
    } else if( choice == 3 ) {
      game.printStats();
    } else if( choice == 4 ) {
      running = false;
    }
  }

  cout << "Goodbye!" << endl;
  return 0;
}
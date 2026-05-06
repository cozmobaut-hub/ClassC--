#ifndef CONNECTFOURGAME_H
#define CONNECTFOURGAME_H

#include <string>
#include <vector>

/**
 * @brief Connect Four game logic and persistent stats
 * @desc Encapsulates a 2D board, current player, move tracking,
 *       win detection, and file I/O for game state and statistics.
 */
class ConnectFourGame {
public:
  /**
   * @brief Construct a new Connect Four Game object
   * @desc Initializes a 6x7 empty board, sets current player to 'X',
   *       resets move counter and win statistics.
   */
  ConnectFourGame();

  /**
   * @brief Reset the board for a new game
   * @desc Clears all pieces from the board and resets movesPlayed.
   */
  void resetBoard();

  /**
   * @brief Print the current board to the console
   * @desc Displays column indices and the 6x7 grid of pieces.
   */
  void printBoard() const;

  /**
   * @brief Check if a column is full
   * @param col column index to check
   * @return true if no empty cells remain in this column
   * @return false otherwise
   */
  bool isColumnFull( int col ) const;

  /**
   * @brief Drop the current player's piece into the given column
   * @param col column index to drop into
   * @param lastRow reference set to the row where the piece landed
   * @param lastCol reference set to the column where the piece landed
   * @return true if the piece was successfully placed
   * @return false if the column is full or column index is invalid
   */
  bool dropPiece( int col, int& lastRow, int& lastCol );

  /**
   * @brief Check if the last move created a win
   * @param lastRow row index of the last placed piece
   * @param lastCol column index of the last placed piece
   * @return true if current player has four in a row
   * @return false otherwise
   */
  bool checkWin( int lastRow, int lastCol ) const;

  /**
   * @brief Check if the game is a tie
   * @desc Returns true if the board is full and there is no winner.
   * @return true if the game is tied
   * @return false otherwise
   */
  bool checkTie() const;

  /**
   * @brief Switch the current player
   * @desc Swaps currentPlayer between 'X' and 'O'.
   */
  void switchPlayer();

  /**
   * @brief Record a win for the current player
   * @desc Increments the appropriate win counter.
   */
  void recordWin();

  /**
   * @brief Load a saved game state from file
   * @param filename path to save file
   * @return true on success, false on I/O or format failure
   */
  bool loadGameFromFile( const std::string& filename );

  /**
   * @brief Save current game state to file
   * @param filename path to save file
   * @return true on success, false on I/O failure
   */
  bool saveGameToFile( const std::string& filename ) const;

  /**
   * @brief Load cumulative player win statistics from file
   * @param filename path to stats file
   * @return true on success, false on I/O or format failure
   */
  bool loadStatsFromFile( const std::string& filename );

  /**
   * @brief Save cumulative player win statistics to file
   * @param filename path to stats file
   * @return true on success, false on I/O failure
   */
  bool saveStatsToFile( const std::string& filename ) const;

  /**
   * @brief Print current statistics to the console
   * @desc Displays total wins for player X and player O.
   */
  void printStats() const;

  /**
   * @brief Get the number of wins for player X
   * @return int total wins for X
   */
  int getPlayerXWins() const;

  /**
   * @brief Get the number of wins for player O
   * @return int total wins for O
   */
  int getPlayerOWins() const;

  /**
   * @brief Get the current player symbol
   * @return char 'X' or 'O'
   */
  char getCurrentPlayer() const;

private:
  int _rows;
  int _cols;
  std::vector< std::vector<char> > _board;
  char _currentPlayer;
  int _movesPlayed;
  int _playerXWins;
  int _playerOWins;

  /**
   * @brief Count consecutive pieces in a direction
   * @desc Starting from (startRow, startCol), steps by (deltaRow, deltaCol)
   *       and counts contiguous pieces matching currentPlayer.
   * @param startRow row to start from
   * @param startCol column to start from
   * @param deltaRow row step
   * @param deltaCol column step
   * @return int number of matching pieces in this direction
   */
  int countDirection( int startRow, int startCol,
                      int deltaRow, int deltaCol ) const;

  /**
   * @brief Validate that a position is on the board
   * @param row row index to check
   * @param col column index to check
   * @return true if (row, col) is within bounds
   * @return false otherwise
   */
  bool isInBounds( int row, int col ) const;
};

#endif // CONNECTFOURGAME_H
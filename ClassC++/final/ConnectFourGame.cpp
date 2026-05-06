#include "ConnectFourGame.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

namespace {
  const int DEFAULT_ROWS = 6;
  const int DEFAULT_COLS = 7;
  const char EMPTY_CELL = ' ';
}

ConnectFourGame::ConnectFourGame() {
  _rows = DEFAULT_ROWS;
  _cols = DEFAULT_COLS;
  _board = vector< vector<char> >( _rows, vector<char>( _cols, EMPTY_CELL ) );
  _currentPlayer = 'X';
  _movesPlayed = 0;
  _playerXWins = 0;
  _playerOWins = 0;
}

void ConnectFourGame::resetBoard() {
  for( int r = 0; r < _rows; r++ ) {
    for( int c = 0; c < _cols; c++ ) {
      _board.at( r ).at( c ) = EMPTY_CELL;
    }
  }
  _movesPlayed = 0;
  _currentPlayer = 'X';
}

void ConnectFourGame::printBoard() const {
  cout << endl;
  cout << "  ";
  for( int c = 0; c < _cols; c++ ) {
    cout << c << " ";
  }
  cout << endl;

  for( int r = 0; r < _rows; r++ ) {
    cout << r << " ";
    for( int c = 0; c < _cols; c++ ) {
      cout << _board.at( r ).at( c ) << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool ConnectFourGame::isColumnFull( const int col ) const {
  if( col < 0 || col >= _cols ) {
    return true;
  }
  return _board.at( 0 ).at( col ) != EMPTY_CELL;
}

bool ConnectFourGame::dropPiece( const int col, int& lastRow, int& lastCol ) {
  if( col < 0 || col >= _cols ) {
    return false;
  }
  if( isColumnFull( col ) ) {
    return false;
  }

  for( int r = _rows - 1; r >= 0; r-- ) {
    if( _board.at( r ).at( col ) == EMPTY_CELL ) {
      _board.at( r ).at( col ) = _currentPlayer;
      _movesPlayed++;
      lastRow = r;
      lastCol = col;
      return true;
    }
  }
  return false;
}

bool ConnectFourGame::checkWin( const int lastRow, const int lastCol ) const {
  const int REQUIRED = 4;

  int totalHorizontal = 1;
  totalHorizontal += countDirection( lastRow, lastCol, 0, -1 );
  totalHorizontal += countDirection( lastRow, lastCol, 0, 1 );
  if( totalHorizontal >= REQUIRED ) {
    return true;
  }

  int totalVertical = 1;
  totalVertical += countDirection( lastRow, lastCol, -1, 0 );
  totalVertical += countDirection( lastRow, lastCol, 1, 0 );
  if( totalVertical >= REQUIRED ) {
    return true;
  }

  int totalDiag1 = 1;
  totalDiag1 += countDirection( lastRow, lastCol, -1, -1 );
  totalDiag1 += countDirection( lastRow, lastCol, 1, 1 );
  if( totalDiag1 >= REQUIRED ) {
    return true;
  }

  int totalDiag2 = 1;
  totalDiag2 += countDirection( lastRow, lastCol, -1, 1 );
  totalDiag2 += countDirection( lastRow, lastCol, 1, -1 );
  if( totalDiag2 >= REQUIRED ) {
    return true;
  }

  return false;
}

bool ConnectFourGame::checkTie() const {
  return _movesPlayed >= _rows * _cols;
}

void ConnectFourGame::switchPlayer() {
  if( _currentPlayer == 'X' ) {
    _currentPlayer = 'O';
  } else {
    _currentPlayer = 'X';
  }
}

void ConnectFourGame::recordWin() {
  if( _currentPlayer == 'X' ) {
    _playerXWins++;
  } else if( _currentPlayer == 'O' ) {
    _playerOWins++;
  }
}

bool ConnectFourGame::loadGameFromFile( const string& filename ) {
  ifstream inFile( filename );
  if( inFile.fail() ) {
    return false;
  }

  int rowsInFile;
  int colsInFile;
  inFile >> rowsInFile >> colsInFile;
  if( inFile.fail() ) {
    return false;
  }

  // Discard the rest of the header line to prepare for getline
  inFile.ignore( numeric_limits<streamsize>::max(), '\n' );

  vector< vector<char> > tempBoard( _rows, vector<char>( _cols, EMPTY_CELL ) );

  for( int r = 0; r < _rows; r++ ) {
    string line;
    if( !getline( inFile, line ) ) {
      return false;
    }

    // Each cell is at even indices: 0, 2, 4, ..., 2*_cols - 2
    for( int c = 0; c < _cols; c++ ) {
      int index = 2 * c;
      if( index < static_cast<int>( line.size() ) ) {
        char cell = line.at( index );
        tempBoard.at( r ).at( c ) = cell;
      } else {
        tempBoard.at( r ).at( c ) = EMPTY_CELL;
      }
    }
  }

  char current;
  int moves;
  if( !(inFile >> current >> moves) ) {
    return false;
  }

  int xWinsFromFile;
  int oWinsFromFile;
  if( !(inFile >> xWinsFromFile >> oWinsFromFile) ) {
    return false;
  }

  _board = tempBoard;
  _currentPlayer = current;
  _movesPlayed = moves;
  _playerXWins = xWinsFromFile;
  _playerOWins = oWinsFromFile;

  return true;
}

bool ConnectFourGame::saveGameToFile( const string& filename ) const {
  ofstream outFile( filename );
  if( outFile.fail() ) {
    return false;
  }

  outFile << _rows << " " << _cols << endl;
  for( int r = 0; r < _rows; r++ ) {
    for( int c = 0; c < _cols; c++ ) {
      outFile << _board.at( r ).at( c ) << " ";
    }
    outFile << endl;
  }

  outFile << _currentPlayer << " " << _movesPlayed << endl;
  outFile << _playerXWins << " " << _playerOWins << endl;

  return true;
}

bool ConnectFourGame::loadStatsFromFile( const string& filename ) {
  ifstream inFile( filename );
  if( inFile.fail() ) {
    return false;
  }

  int xWinsFromFile;
  int oWinsFromFile;
  inFile >> xWinsFromFile >> oWinsFromFile;
  if( inFile.fail() ) {
    return false;
  }

  _playerXWins = xWinsFromFile;
  _playerOWins = oWinsFromFile;
  return true;
}

bool ConnectFourGame::saveStatsToFile( const string& filename ) const {
  ofstream outFile( filename );
  if( outFile.fail() ) {
    return false;
  }
  outFile << _playerXWins << " " << _playerOWins << endl;
  return true;
}

void ConnectFourGame::printStats() const {
  cout << "=== Connect 4 Stats ===" << endl;
  cout << "Player X wins: " << _playerXWins << endl;
  cout << "Player O wins: " << _playerOWins << endl;
  cout << endl;
}

int ConnectFourGame::getPlayerXWins() const {
  return _playerXWins;
}

int ConnectFourGame::getPlayerOWins() const {
  return _playerOWins;
}

char ConnectFourGame::getCurrentPlayer() const {
  return _currentPlayer;
}

int ConnectFourGame::countDirection( int startRow, int startCol,
                                     const int deltaRow, const int deltaCol ) const {
  int count = 0;
  int r = startRow + deltaRow;
  int c = startCol + deltaCol;

  while( isInBounds( r, c ) &&
         _board.at( r ).at( c ) == _currentPlayer ) {
    count++;
    r += deltaRow;
    c += deltaCol;
  }
  return count;
}

bool ConnectFourGame::isInBounds( const int row, const int col ) const {
  return row >= 0 && row < _rows && col >= 0 && col < _cols;
}
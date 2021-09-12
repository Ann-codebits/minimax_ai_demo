#pragma once
#include <vector>

class TicTacToe
{
public:
	enum class markers { AVAILABLE, MARKER_AI, MARKER_HUMAN };
	enum class gameState { IN_PROGRESS, DRAW, AI_WIN, HUMAN_WIN };

private:
	markers board[3][3];
	int numCols;
	int numRows;
	char markerToChar(markers markerIn) const;

public:
	
	TicTacToe() 
	{
		numCols = 3;
		numRows = 3;
		int index = 0;
		for(int boardRow=0; boardRow < numRows; boardRow++)
		{ 
			for (int boardCol = 0; boardCol < numCols; boardCol++)
			{
				board[boardRow][boardCol] = markers::AVAILABLE;
			}
		}
	}
	gameState gameStatus() const;
	void drawBoard() const;
	void setBoard(int row, int col, TicTacToe::markers marker);
	std::vector<int> getAvailablePositions() const;
	void applyPosition(int position, bool isMaximizer);
	bool isPositionAvailable(int row, int col) const;
	bool isAI(int row, int col) const;
	bool isHuman(int row, int col) const;
};
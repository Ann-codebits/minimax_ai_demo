#include "Player.h"
#include "TicTacToe.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

TicTacToe::gameState TicTacToe::gameStatus() const
{

	//check if there is a winner

	if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != markers::AVAILABLE))
	{
		if ((board[0][0]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[0][0]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != markers::AVAILABLE))
	{
		if ((board[0][2]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[0][2]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	/*rows*/
	else if ((board[0][0] == board[0][1]) && (board[0][1] == board[0][2]) && (board[0][0] != markers::AVAILABLE))
	{
		if ((board[0][0]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if (board[0][0] == markers::MARKER_HUMAN)  
		{
			return gameState::HUMAN_WIN;
		}
	}
	else if ((board[1][0] == board[1][1]) && (board[1][1] == board[1][2]) && (board[1][0] != markers::AVAILABLE))
	{
		if ((board[1][0]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[1][0]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	else if ((board[2][0] == board[2][1]) && (board[2][1] == board[2][2]) && (board[2][0] != markers::AVAILABLE))
	{
		if ((board[2][0]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[2][0]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	/*columns*/
	else if ((board[0][0] == board[1][0]) && (board[1][0] == board[2][0]) && (board[0][0] != markers::AVAILABLE))
	{
		if ((board[0][0]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[0][0]) == markers::MARKER_HUMAN)  {
			return gameState::HUMAN_WIN;
		}
	}
	else if ((board[0][1] == board[1][1]) && (board[1][1] == board[2][1]) && (board[0][1] != markers::AVAILABLE))
	{
		if ((board[0][1]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[0][1]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	else if ((board[0][2] == board[1][2]) && (board[1][2] == board[2][2]) && (board[0][2] != markers::AVAILABLE))
	{
		if ((board[0][1]) == markers::MARKER_AI)
		{
			return gameState::AI_WIN;
		}
		else if ((board[0][1]) == markers::MARKER_HUMAN) {
			return gameState::HUMAN_WIN;
		}
	}
	else
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (board[row][col] == markers::AVAILABLE)
				{
					//if any space is available we can still progress in this game
					return gameState::IN_PROGRESS;
				}
			}

		}
		return gameState::DRAW;
	}
	
}

void TicTacToe::drawBoard() const
{
	//display the board
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			std::cout << markerToChar(board[row][col]) << " ";
		}
		//display positions alongside
		std::cout << "       ";
		for (int col = 0; col < numCols; col++)
		{
			std::cout << (3 * row + col) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

char TicTacToe::markerToChar(markers markerIn) const
{
	if (markerIn == TicTacToe::markers::MARKER_AI)
	{
		return 'x';
	}
	else if (markerIn == TicTacToe::markers::MARKER_HUMAN)
	{
		return 'o';
	}
	else 
	{
		return '.';
	}
}
void TicTacToe::setBoard(int row, int col, TicTacToe::markers marker) 
{
	if(board[row][col]== TicTacToe::markers::AVAILABLE)
	{
		board[row][col] = marker;
	}
	else
	{
		assert(false && "Choose another position");
	}
}
std::vector<int> TicTacToe::getAvailablePositions() const
{
	std::vector<int> availablePos;
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (board[row][col] == TicTacToe::markers::AVAILABLE)
			{
				availablePos.push_back((row * 3) + col);
			}
		}
	}
	return availablePos;
}

bool TicTacToe::isPositionAvailable(int row, int col) const
{
	return (board[row][col] == TicTacToe::markers::AVAILABLE);
}
void TicTacToe::applyPosition(int position, bool isMaximizer)
{
	int row = position / 3;
	int col = position % 3;

	board[row][col] =isMaximizer? TicTacToe::markers::MARKER_AI: TicTacToe::markers::MARKER_HUMAN;

}

bool TicTacToe::isAI(int row, int col) const
{
	return (board[row][col] == TicTacToe::markers::MARKER_AI);
}

bool TicTacToe::isHuman(int row, int col) const
{
	return (board[row][col] == TicTacToe::markers::MARKER_HUMAN);
}


#include "Player.h"
#include "TicTacToe.h"
#include <string>
#include <iostream>
#include <cassert>

void HumanPlayer::play(TicTacToe& ticTacToe) const
{
	ticTacToe.drawBoard();
	std::string pos;
	int position;
	std::cout << "Enter position" << std::endl;

	while (true)
	{
		std::getline(std::cin, pos);
		if (pos.length() == 1)
		{
			position = pos[0] - '0';
			if (position >= 0 && position <= 8)
			{
				int row = position / 3;
				int col = position % 3;
				if (ticTacToe.isPositionAvailable(row, col))
				{
					ticTacToe.setBoard(row, col, TicTacToe::markers::MARKER_HUMAN);
					break;
				}
				else
				{
					std::cout << "Position not available, choose another position." << std::endl;
					continue;
				}
			}
		}

		std::cout << "Invalid position entered , pick a value from 0 through 8" << std::endl;
	}

}

int AIPlayer::getHeuristic(const TicTacToe& tictactoe) const
{
	int score = computeScore({ 0, 1, 2 },tictactoe) /*row*/
		+ computeScore({ 3, 4, 5 }, tictactoe)       /*row*/
		+ computeScore({ 6, 7, 8 }, tictactoe)       /*row*/
		+ computeScore({ 0, 3, 6 }, tictactoe)       /*column*/
		+ computeScore({ 1, 4, 7 }, tictactoe)       /*column*/
		+ computeScore({ 2, 5, 8 }, tictactoe)       /*column*/
		+ computeScore({ 0, 4, 8 }, tictactoe)       /*diagonal*/
		+ computeScore({ 2, 4, 6 }, tictactoe);      /*diagonal*/

	return score;
}

int AIPlayer::computeScore(const std::vector<int>& lines, const TicTacToe& tictactoe) const
{
	int countAI = 0;
	int countHuman = 0;

	for (auto position : lines)
	{
		int row = position / 3;
		int col = position % 3;

		if (tictactoe.isAI(row,col))
		{
			countAI++;
		}
		else if (tictactoe.isHuman(row,col))
		{
			countHuman++;
		}
	}

	//scores
	// --- = -1, H-- = -10, HH- = -100, HHH = -1000, A-- = +10, AA- = +100, AAA= +1000
	// 0 for others
	if ((countAI == 0) && (countHuman == 0))
	{
		return -1;
	}
	if (countAI == 0)
	{
		if (countHuman == 1)
		{
			return -10;
		}
		else if (countHuman == 2)
		{
			return -100;
		}
		else if (countHuman == 3)
		{
			return -1000;
		}
		else
		{
			assert(false && "Something went wrong in compute score for AI case");
		}
	}
	else if (countHuman == 0)
	{
		if (countAI == 1)
		{
			return 10;
		}
		else if (countAI == 2)
		{
			return 100;
		}
		else if (countAI == 3)
		{
			return 1000;
		}
		else
		{
			assert(false && "Something went wrong in compute score for Human case");
		}
	}

	return 0;
}

int AIPlayer::miniMax(TicTacToe& tictactoe, int depth, int& bestMove, bool isMaximizing) const
{
	int val;
	std::vector<int> availablePos = tictactoe.getAvailablePositions();
	auto state = tictactoe.gameStatus();
	if (depth == 0 || (state != TicTacToe::gameState::IN_PROGRESS)) //if the depth is a zero or the node is terminal node
	{
		int retVal = getHeuristic(tictactoe);
		return retVal;
	}
	else if (isMaximizing) //maximizing player
	{
		val = INT_MIN;

		for (int i = 0; i < availablePos.size(); i++)
		{
			TicTacToe temp = tictactoe;
			temp.applyPosition(availablePos[i], true); //current call was for maximizer
			int tempBestMove;
			int retVal = miniMax(temp, depth - 1, tempBestMove, false); //next call is for minimizer
			if (retVal > val)
			{
				val = retVal;
				bestMove = availablePos[i];
			}
		}
		return val;
	}
	else {//minimizing player
		val = INT_MAX;

		for (int i = 0; i < availablePos.size(); i++)
		{
			TicTacToe temp = tictactoe;
			temp.applyPosition(availablePos[i], false); //current call was for minimizer
			int tempBestMove;
			int retVal = miniMax(temp, depth - 1, tempBestMove, true); //next call is for maximizer
			if (retVal < val)
			{
				val = retVal;
				bestMove = availablePos[i]; //not really the best move, we need it for recursive call
			}
		}
		return val;
	}

}

void AIPlayer::play(TicTacToe& ticTacToe) const
{
	ticTacToe.drawBoard();
	int bestMove = 0;
	int retVal = miniMax(ticTacToe, 2, bestMove, true); //2 ply lookahead
	int row = bestMove / 3;
	int col = bestMove % 3;
	ticTacToe.setBoard(row, col, TicTacToe::markers::MARKER_AI);
}


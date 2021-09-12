#include<iostream>
#include "TicTacToe.h"
#include "Player.h"

int main() 
{
	TicTacToe ticTacToe;
	HumanPlayer hPlayer;
	AIPlayer aiPlayer;

	while (true)
	{
		hPlayer.play(ticTacToe);
		TicTacToe::gameState state = ticTacToe.gameStatus();
		if (state == TicTacToe::gameState::DRAW)
		{
			std::cout << "Game Tie." << std::endl;
			break;
		}
		else if (state == TicTacToe::gameState::HUMAN_WIN)
		{
			std::cout << "Human Player Wins." << std::endl;
			break;
		}

		aiPlayer.play(ticTacToe);
		state = ticTacToe.gameStatus();
		if (state == TicTacToe::gameState::DRAW)
		{
			std::cout << "Game Tie." << std::endl;
			break;
		}
		else if (state == TicTacToe::gameState::AI_WIN)
		{
			std::cout << "AI Player Wins." << std::endl;
			break;
		}
		
	}
	std::cout << "Final game state" << std::endl;
	ticTacToe.drawBoard();
	return 0;
}
#pragma once
#include <vector>

class TicTacToe;
class Player
{
public:
	virtual void play(TicTacToe& ticTacToe) const = 0;
};

class HumanPlayer:public Player
{
public:
	HumanPlayer() = default;
	void play(TicTacToe& ticTacToe) const override;
	
};

class AIPlayer :public Player
{
private:
	int miniMax(TicTacToe& tictactoe, int depth, int& bestMove, bool isMaximizing) const;
	int getHeuristic(const TicTacToe& tictactoe) const;
	int computeScore(const std::vector<int>& lines, const TicTacToe& tictactoe) const;
public:
	AIPlayer() = default;
	void play(TicTacToe& ticTacToe) const override;
};
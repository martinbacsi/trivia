#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() : currentPlayerID(0)
{
	for (int i = 0; i < 50; ++i)
	{
		popQuestions.push_back(CreateQuestion(Pop, i));
		scienceQuestions.push_back(CreateQuestion(Science, i));
		sportsQuestions.push_back(CreateQuestion(Sports, i));
		rockQuestions.push_back(CreateQuestion(Rock, i));
	}
}

Player& Game::CurrentPlayer()
{
	return players[currentPlayerID];
}


string Game::CreateQuestion(const Category category, const int index) const
{
	ostringstream ss;
	switch (category)
	{
		case Pop:
			ss << "Pop";
			break;
		case Science:
			ss << "Science";
			break;
		case Sports:
			ss << "Sports";
			break;
		case Rock:
			ss << "Rock";
			break;
		default:
			throw "Invalid Category";
	}

	ss << " Question " << index;
	return ss.str();
}

bool Game::IsPlayable() const
{
	return (players.size() > 1);
}

void Game::AddPlayer(const string& playerName)
{
	players.push_back(playerName);
	cout << playerName << " was added" << endl;
	cout << "They are player number " << players.size() << endl;
}

void Game::Roll()
{
	int roll = rand() % 5 + 1;

	cout << CurrentPlayer().name << " is the current player" << endl;
	cout << "They have rolled a " << roll << endl;

	if (CurrentPlayer().penaltyBox)
	{
		if (roll % 2)
		{
			CurrentPlayer().penaltyBox = false;
			cout << CurrentPlayer().name << " is getting out of the penalty box" << endl;
		}
		else
		{
			cout << CurrentPlayer().name << " is not getting out of the penalty box" << endl;
		}
	}
	if(!CurrentPlayer().penaltyBox)
	{
		CurrentPlayer().place += roll;
		if (CurrentPlayer().place > 11)
		{
			CurrentPlayer().place -= 12;
		}
		cout << CurrentPlayer().name << "'s new location is " << CurrentPlayer().place << endl;
		cout << "The category is " << CurrentCategory() << endl;
		AskQuestion();
	}
}

void Game::AskQuestion()
{
	switch (CurrentCategory())
	{
		case Pop:
			cout << popQuestions.front() << endl;
			popQuestions.pop_front();
			break;
		case Science:
			cout << scienceQuestions.front() << endl;
			scienceQuestions.pop_front();
			break;
		case Sports:
			cout << sportsQuestions.front() << endl;
			sportsQuestions.pop_front();
			break;
		case Rock:
			cout << rockQuestions.front() << endl;
			rockQuestions.pop_front();
			break;
		default:
			throw "Invalid Category";
	}
}


Category Game::CurrentCategory()
{
	return static_cast<Category>(CurrentPlayer().place % 4);
}

bool Game::Answer(bool correct)
{
	bool winner = false;

	if (correct)
	{
		if (CurrentPlayer().penaltyBox)
		{
			winner = false;
		}
		else
		{
			cout << "Answer was corrent!!!!" << endl;
			++CurrentPlayer().purse;
			cout << CurrentPlayer().name << " now has " << CurrentPlayer().purse << " Gold Coins." << endl;
			winner = Won();
		}
	}
	else
	{
		cout << "Question was incorrectly answered" << endl;
		cout << CurrentPlayer().name << " was sent to the penalty box" << endl;
		CurrentPlayer().penaltyBox = true;
		winner = false;
	}
	NextPlayer();
	return winner;
}

void Game::NextPlayer()
{
	++currentPlayerID;
	if (currentPlayerID == players.size())
	{
		currentPlayerID = 0;
	}
}

bool Game::Won()
{
	return CurrentPlayer().purse == 6;
}

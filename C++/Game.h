#include <iostream>
#include <list>
#include <vector>
#include <memory>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

enum Category
{
	Pop = 0, Science = 1, Sports = 2, Rock = 3
};

class Player
{
public:
	Player(const string& name) : name(name) {}
	const string name;
	int purse = 0;
	int place = 0;
	bool penaltyBox = false;
};

class Game
{
public:
	Game();
	bool IsPlayable() const;
	void AddPlayer(const string& playerName);
	void Roll();
	bool Answer(bool correct);
private:
	vector<Player> players;
	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;
	int currentPlayerID;
	
	Player& CurrentPlayer();
	void AskQuestion();
	Category CurrentCategory();
	string CreateQuestion(const Category category, const int index) const;
	bool Won();
	void NextPlayer();
};

#endif /* GAME_H_ */

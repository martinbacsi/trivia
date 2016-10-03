#include <stdlib.h>
#include "Game.h"


int main()
{
	Game mGame;
	mGame.AddPlayer("Chet");
	mGame.AddPlayer("Pat");
	mGame.AddPlayer("Sue");
	bool winner = false;
	while (!winner && mGame.IsPlayable())
	{
		mGame.Roll();
		winner = mGame.Answer(rand() % 9);
	}
}

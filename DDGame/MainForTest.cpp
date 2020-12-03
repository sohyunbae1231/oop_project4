#include "DDGame.h"

int main(void)
{
    DDGame *game = new DDGame();

    game->StartGame();

    delete game;

    return 0;
}
// Copyright 2025 <MennaAssem>

#include "globals.h"

PlayerManager *PLAYM = new PlayerManager("players.json");
Authentication *AUTH = new Authentication();
GameManager *GAMEM = new GameManager("games.json", *PLAYM);

SessionManager *SM = new SessionManager();

int indexforgames = 0;
bool accountiscreated = false;
int VsAi = 0;

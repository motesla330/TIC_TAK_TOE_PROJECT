// Copyright 2025 MahmoudIsmail

#ifndef FINAL_GLOBA_H_
#define FINAL_GLOBA_H_

#include "Authentication.h"
#include "playermanager.h"
#include "final/gamemanager.h"
#include "final/SessionManagement.h"

extern PlayerManager* PLAYM;
extern Authentication* AUTH;
extern bool accountiscreated;
extern int VsAi;
extern GameManager* GAMEM;
extern SessionManager* SM;
extern int indexforgames;  // Global index for replay feature

#endif  // FINAL_GLOBA_H_

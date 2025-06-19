// Copyright 2025 MahmoudIsmail

#ifndef FINAL_GLOBALS_H_
#define FINAL_GLOBALS_H_

#include "final/Authentication.h"
#include "final/playermanager.h"
#include "final/gamemanager.h"
#include "final/SessionManagement.h"

extern PlayerManager* PLAYM;
extern Authentication* AUTH;
extern bool accountiscreated;
extern int VsAi;
extern GameManager* GAMEM;
extern SessionManager* SM;
extern int indexforgames;  // Global index for replay feature

#endif  // FINAL_GLOBALSS_H_

/*****************************************************************************************************************
* Copyright (C) 2019 by Matthias Birnthaler                                                                      *
*                                                                                                                *
* This file is part of the ItemCap Plugin for Ark Server API                                                     *
*                                                                                                                *
*    This program is free software : you can redistribute it and/or modify                                       *
*    it under the terms of the GNU General Public License as published by                                        *
*    the Free Software Foundation, either version 3 of the License, or                                           *
*    (at your option) any later version.                                                                         *
*                                                                                                                *
*    This program is distributed in the hope that it will be useful,                                             *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of                                              *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                                                 *
*    GNU General Public License for more details.                                                                *
*                                                                                                                *
*    You should have received a copy of the GNU General Public License                                           *
*    along with this program.If not, see <https://www.gnu.org/licenses/>.                                        *
*                                                                                                                *
*****************************************************************************************************************/

/**
* \file Hooks.h
* \author Matthias Birnthaler Matthias-Birnthaler@outlook.com
* \date 2020-05-01
* \brief File containing the implementation for all needed Hooks
*
*/


#ifndef HOOKS_H
#define HOOKS_H


/* =================================================[includes]================================================= */

#include "Tools.h"
#include "Requests.h"
#include "ICommands.h"
#include "IHooks.h"
#include "API/ARK/Ark.h"
#include "json.hpp"
#include <fstream>

/**< \brief declare of AShooterGameMode_ShowMessageOfTheDay Hook */
DECLARE_HOOK(UPrimalItem_InitNewItem, void, UPrimalItem*, float, UPrimalInventoryComponent*, float, float);


/* ================================================[declaration of public functions]=========================== */

extern void InitHooks(void);
extern void RemoveHooks(void);


#endif /* HOOKS_H */

/* ================================================[end of file]=============================================== */

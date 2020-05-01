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
* \file Util.h
* \author Matthias Birnthaler
* \date 2020-05-01
* \brief header file of utility functions
*
*/


#ifndef UTIL_H
#define UTIL_H

/* =================================================[includes]================================================= */

#include "Tools.h"
#include "Requests.h"
#include "ICommands.h"
#include "IHooks.h"
#include "API/ARK/Ark.h"

namespace Util
{
    typedef struct CapEntry
    {
        FString blueprint; 
        float capValue;

    }CapEntry_t;


    /* ================================================[declaration of public functions]=========================== */
    extern void UtilInit(void);

    extern bool IsDinoSaddleCapEnabled();

    extern bool IsWeaponCapEnabled();

    extern float GetDinoSaddleCapMax();

    extern float GetWeaponCapMax();

    extern std::list<CapEntry_t>  GetDinoSaddleSpecialCaps();

    extern std::list<CapEntry_t>  GetWeaponSpecialCaps();

}
 

#endif /* UTIL_H */

/* ================================================[end of file]=============================================== */

/****************************************************************************
* Copyright (C) 2019 by Matthias Birnthaler                                 *
*                                                                           *
* This file is part of the OverwriteCuddleWalking Plugin for Ark Server API *
*                                                                           *
*   The OverwriteCuddleWalking Plugin is free software: you can             *
*	redistribute it and/or modify it under the terms of the GNU Lesser      *
*	General Public License as published by the Free Software Foundation,    *
*	either version 3 of the License, or (at your option) any later version. *
*                                                                           *
*   The OverwriteCuddleWalking Plugin is distributed in the hope that it    *
*   will be useful, but WITHOUT ANY WARRANTY; without even the implied      *
* 	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.        *
* 	See the GNU Lesser General Public License for more details.             *
*                                                                           *
****************************************************************************/

/**
* \file Util.h
* \author Matthias Birnthaler
* \date 19 March 2019
* \brief header file of utility functions
*
*/


#ifndef UTIL_H
#define UTIL_H

#include "Tools.h"
#include "Requests.h"
#include "ICommands.h"
#include "IHooks.h"
#include "API/ARK/Ark.h"

namespace Util
{

	extern void UtilInit(void);

}
 

#endif /* UTIL_H */
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
* \file Util.cpp
* \author Matthias Birnthaler
* \date 19 March 2019
* \brief Implementation of utility functions
*
*/


#include "Util.h"
#include "Tools.h"
#include "json.hpp"
#include <fstream>
#include "Tools.h"


namespace Util
{


	static nlohmann::json config;


	static FString MessageOfDay;
	tm DateClusterOpen;
	tm DateRewipe;

	static void ReadConfig(void);
	static void GetDates(void);


	/**
	* \brief ReadConfig
	*
	* This function reads out the json config file
	*
	* \return  nlohmann::json
	*/
	void ReadConfig(void)
	{


		const std::string config_path = ArkApi::Tools::GetCurrentDir() + "/ArkApi/Plugins/ItemCap/config.json";
		std::ifstream file{ config_path };
		if (!file.is_open())
			throw std::runtime_error("Can't open config.json");

		file >> config;

		file.close();
	}

	void UtilInit(void)
	{
		ReadConfig();
	}

}

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
* \file Util.cpp
* \author Matthias Birnthaler
* \date 2020-05-01
* \brief Implementation of utility functions
*
*/


/* ================================================[includes]================================================ */
#include "Util.h"
#include "Tools.h"
#include "json.hpp"
#include <fstream>
#include "Tools.h"

namespace Util
{


    /* ========================================== [local defines] =============================================== */

    /* ============================================ [local data] ================================================ */

    static nlohmann::json config;
    static bool isDinoSaddleCapEnabled;
    static bool isWeaponCapEnabled;
    static std::list<CapEntry_t> DinoSaddleSpecialCaps;
    static std::list<CapEntry_t> WeaponSpecialCaps;

    /* ===================================== [prototype of local functions] ======================================= */
    static void ReadConfig(void);

    /* ===================================== [definition of local functions] ====================================== */

    /**
    * \brief ReadConfig
    *
    * This function reads out the json config file
    *
    * \return  nlohmann::json
    */
    static void ReadConfig(void)
    {
        const std::string config_path = ArkApi::Tools::GetCurrentDir() + "/ArkApi/Plugins/ItemCap/config.json";
        std::ifstream file{ config_path };
        if (!file.is_open())
            throw std::runtime_error("Can't open config.json");

        file >> config;

        file.close();
    }

    /* ===================================== [definition of global functions] ===================================== */


    bool IsDinoSaddleCapEnabled()
    {
        return isDinoSaddleCapEnabled;
    }

    bool IsWeaponCapEnabled()
    {
        return isWeaponCapEnabled;
    }

    float GetDinoSaddleCapMax()
    {
        return (float)config["DinoSaddle"]["MaxArmor"];
    }

    float GetWeaponCapMax()
    {
        return (float)config["Weapon"]["MaxWeaponDamagePercent"];
    }

    std::list<CapEntry_t>  GetDinoSaddleSpecialCaps()
    {
        return DinoSaddleSpecialCaps;
    }

    std::list<CapEntry_t>  GetWeaponSpecialCaps()
    {
        return WeaponSpecialCaps;
    }

    void UtilInit(void)
    {
        ReadConfig();
        isDinoSaddleCapEnabled = config["DinoSaddle"].value("EnableCap", false);
        isWeaponCapEnabled = config["Weapon"].value("EnableCap", false);

        for (auto& entry : config["DinoSaddle"]["SpecialCaps"]) 
        {
            CapEntry_t CapEntry;


            CapEntry.blueprint = FString(ArkApi::Tools::Utf8Decode(entry["Blueprint"]).c_str());
            CapEntry.capValue = entry["MaxArmor"];

            DinoSaddleSpecialCaps.push_back(CapEntry);
        }

        for (auto& entry : config["Weapon"]["SpecialCaps"])
        {
            CapEntry_t CapEntry;

            CapEntry.blueprint = FString(ArkApi::Tools::Utf8Decode(entry["Blueprint"]).c_str());
            CapEntry.capValue = entry["MaxWeaponDamagePercent"];

            WeaponSpecialCaps.push_back(CapEntry);
        }

        //////////// Debug Logs only //////////// 
        
        Log::GetLog()->error("DinoSaddle_EnableCap: {}", isDinoSaddleCapEnabled);
        Log::GetLog()->error("Weapon_EnableCap: {}", isWeaponCapEnabled);

        Log::GetLog()->error("DinoSaddle_MaxArmor: {}", (float)config["DinoSaddle"]["MaxArmor"]);
        Log::GetLog()->error("Weapon_MaxWeaponDamagePercent: {}", (float)config["Weapon"]["MaxWeaponDamagePercent"]);

        for (auto& entry : DinoSaddleSpecialCaps)
        {
            Log::GetLog()->error("DinoSaddleSpecialCaps_entry_blueprint: {}", entry.blueprint.ToString());
            Log::GetLog()->error("DinoSaddleSpecialCaps_entry_value: {}", entry.capValue);
        }

        for (auto& entry : WeaponSpecialCaps)
        {
            Log::GetLog()->error("WeaponSpecialCaps_entry_blueprint: {}", entry.blueprint.ToString());
            Log::GetLog()->error("WeaponSpecialCaps_entry_value: {}", entry.capValue);
        }


    }

}

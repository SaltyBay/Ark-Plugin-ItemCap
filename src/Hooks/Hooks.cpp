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
* \file Hooks.cpp
* \author Matthias Birnthaler Matthias-Birnthaler@outlook.com
* \date 2020-05-01
* \brief File containing the implementation for all needed Hooks
*
*/


/* ================================================[includes]================================================ */
#include "Hooks.h"
#include "ItemCap.h"
#include "Util.h"


/* ========================================== [local defines] =============================================== */


/* ===================================== [prototype of local functions] ======================================= */

static void  Hook_UPrimalItem_InitNewItem(UPrimalItem* _this, float ItemQuality, UPrimalInventoryComponent* toInventory, float MaxItemDifficultyClamp, float MinRandomQuality);

static void SetItemValueDinoSaddle(UPrimalItem* _this);
static void SetItemValueWappon(UPrimalItem* _this);

/* ===================================== [definition of local functions] ====================================== */

static void SetItemValueWappon(UPrimalItem* _this) 
{
    float newStat;
    float newValue;
    bool doCap = false;


    if (nullptr != _this)
    {
        if (_this->GetItemStatModifier(EPrimalItemStat::WeaponDamagePercent) > Util::GetWeaponCapMax())
        {
            newValue = Util::GetWeaponCapMax();
            doCap = true;
        }

        for (auto& entry : Util::GetDinoSaddleSpecialCaps())
        {
            if (ArkApi::GetApiUtils().GetItemBlueprint(_this).Equals(entry.blueprint))
            {
                if (_this->GetItemStatModifier(EPrimalItemStat::WeaponDamagePercent) > entry.capValue)
                {
                    newValue = entry.capValue;
                    doCap = true;
                }

                break;
            }
        }
    
        if (true == doCap)
        {
            _this->ItemStatValuesField()()[EPrimalItemStat::WeaponDamagePercent] = 0;
            float min_damage = _this->GetItemStatModifier(EPrimalItemStat::WeaponDamagePercent);
            _this->ItemStatValuesField()()[EPrimalItemStat::WeaponDamagePercent] = 65535;
            float max_damage = _this->GetItemStatModifier(EPrimalItemStat::WeaponDamagePercent);

            float diff = max_damage - min_damage;
            float multiplier = 65535 / diff;

            newStat = newValue / 100.f - min_damage;
            newStat *= multiplier;
            newStat += 1.f;
        }


        if (newStat > 65535)
        {
            newStat = 65535;
        }

        _this->ItemStatValuesField()()[EPrimalItemStat::Armor] = newStat;
        _this->UpdatedItem(false);


    }

}


static void SetItemValueDinoSaddle(UPrimalItem* _this)
{
    float newStat;
    float newValue; 
    bool doCap = false; 

    if (nullptr != _this)
    {
        if (_this->GetItemStatModifier(EPrimalItemStat::Armor) > Util::GetDinoSaddleCapMax())
        {
            newValue = Util::GetDinoSaddleCapMax();
            doCap = true;
        }

        for (auto& entry : Util::GetDinoSaddleSpecialCaps())
        {
            if (ArkApi::GetApiUtils().GetItemBlueprint(_this).Equals(entry.blueprint))
            {
                if (_this->GetItemStatModifier(EPrimalItemStat::Armor) > entry.capValue)
                {
                    newValue = entry.capValue;
                    doCap = true;
                }

                break;
            }
        }

        if (true == doCap)
        {
            _this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 0;
            float old_stat_modifier = _this->GetItemStatModifier(EPrimalItemStat::Armor);
            _this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 1;
            newStat = (newValue - old_stat_modifier) / (_this->GetItemStatModifier(EPrimalItemStat::Armor) - old_stat_modifier);
        }


        if (newStat > 65535)
        {
            newStat = 65535;
        }

        _this->ItemStatValuesField()()[EPrimalItemStat::Armor] = newStat;
        _this->UpdatedItem(false);
    }
}


static void  Hook_UPrimalItem_InitNewItem(UPrimalItem* _this, float ItemQuality, UPrimalInventoryComponent* toInventory, float MaxItemDifficultyClamp, float MinRandomQuality)
{
    UPrimalItem_InitNewItem_original(_this, ItemQuality, toInventory, MaxItemDifficultyClamp, MinRandomQuality);

    if (nullptr != _this)
    {

        if ((EPrimalEquipmentType::DinoSaddle == _this->MyEquipmentTypeField()) && (true == Util::IsDinoSaddleCapEnabled()))
        {
            SetItemValueDinoSaddle(_this);
        }

        if ((EPrimalEquipmentType::Weapon == _this->MyEquipmentTypeField()) && (true == Util::IsWeaponCapEnabled()))
        {
            SetItemValueWappon(_this);
        }
    }
}

/* ===================================== [definition of global functions] ===================================== */

/**
* \brief Initialisation of needed Hooks
*
* This function initialise all needed Hooks
*
* \return void
*/
void InitHooks(void)
{
    ArkApi::GetHooks().SetHook("UPrimalItem.InitNewItem", &Hook_UPrimalItem_InitNewItem, 
        &UPrimalItem_InitNewItem_original);
}


/**
* \brief Cancellation of needed Hooks
*
* This function removes all needed Hooks.
*
* \return void
*/
void RemoveHooks(void)
{
    ArkApi::GetHooks().DisableHook("UPrimalItem.InitNewItem", 
        &Hook_UPrimalItem_InitNewItem);

}

/* =================================================[end of file]================================================= */

/*****************************************************************************************************************
* Copyright (C) 2019 by Matthias Birnthaler                                                                      *
*                                                                                                                *
* This file is part of the ItemCap Plugin for Ark Server API                                           *
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
* \date 15 May 2019
* \brief File containing the implementation for all needed Hooks
*
*/


/* ================================================[includes]================================================ */
#include "Hooks.h"
#include "ItemCap.h"
#include "Util.h"


/* ========================================== [local defines] =============================================== */



/* ===================================== [prototype of local functions] ======================================= */


/* ===================================== [definition of local functions] ====================================== */


/* ===================================== [definition of global functions] ===================================== */

void  Hook_UPrimalItem_InitNewItem(UPrimalItem* _this, float ItemQuality, UPrimalInventoryComponent* toInventory, float MaxItemDifficultyClamp, float MinRandomQuality)
{
	UPrimalItem_InitNewItem_original(_this, ItemQuality, toInventory, MaxItemDifficultyClamp, MinRandomQuality);

	if (nullptr != _this)
	{
		auto b_item = ArkApi::GetApiUtils().GetItemBlueprint(_this);


		if (EPrimalEquipmentType::DinoSaddle == _this->MyEquipmentTypeField())
		{
			float newStat = 0.f;


			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 0;
			float old_stat_modifier = _this->GetItemStatModifier(EPrimalItemStat::Armor);
			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 1;
			newStat = (112 - old_stat_modifier) / (_this->GetItemStatModifier(EPrimalItemStat::Armor) - old_stat_modifier);


			if (newStat >= 65536.f)
				newStat = 65535;

			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = newStat;

			_this->UpdatedItem(false);


		//	Log::GetLog()->error("updated: {}", b_item.ToString());

		}
	}
}


void  Hook_UPrimalItem_GetItemBytes(UPrimalItem* _this, TArray<unsigned char>* Bytes)
{
	UPrimalItem_GetItemBytes_original(_this, Bytes);

	if (nullptr != _this)
	{
		auto b_item = ArkApi::GetApiUtils().GetItemBlueprint(_this);


		if (EPrimalEquipmentType::DinoSaddle == _this->MyEquipmentTypeField())
		{
			float newStat = 0.f;


			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 0;
			float old_stat_modifier = _this->GetItemStatModifier(EPrimalItemStat::Armor);
			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = 1;
			newStat = (112 - old_stat_modifier) / (_this->GetItemStatModifier(EPrimalItemStat::Armor) - old_stat_modifier);


			if (newStat >= 65536.f)
				newStat = 65535;

			_this->ItemStatValuesField()()[EPrimalItemStat::Armor] = newStat;

			_this->UpdatedItem(false);


		    Log::GetLog()->error("updated: {}", b_item.ToString());

		}
	}
}


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

	ArkApi::GetHooks().SetHook("UPrimalItem.GetItemBytes", &Hook_UPrimalItem_GetItemBytes, 
		&UPrimalItem_GetItemBytes_original);


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

	ArkApi::GetHooks().DisableHook("UPrimalItem.GetItemBytes", 
		&Hook_UPrimalItem_GetItemBytes);
}

/* =================================================[end of file]================================================= */

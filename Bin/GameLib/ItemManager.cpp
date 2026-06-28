
#ifdef ENABLE_MODEL_RENDER_TARGET
#include "RaceData.h"
bool CItemManager::CanUseByRaceAndGender(int race, const CItemData* itemData) 
{
	static const struct {
		int race;
		DWORD classFlag;
		DWORD genderFlag;
	} raceFlags[] = {
		{ CRaceData::RACE_WARRIOR_M,  CItemData::ITEM_ANTIFLAG_WARRIOR,  CItemData::ITEM_ANTIFLAG_MALE },
		{ CRaceData::RACE_ASSASSIN_W, CItemData::ITEM_ANTIFLAG_ASSASSIN, CItemData::ITEM_ANTIFLAG_FEMALE },
		{ CRaceData::RACE_SURA_M,	 CItemData::ITEM_ANTIFLAG_SURA,	 CItemData::ITEM_ANTIFLAG_MALE },
		{ CRaceData::RACE_SHAMAN_W,   CItemData::ITEM_ANTIFLAG_SHAMAN,   CItemData::ITEM_ANTIFLAG_FEMALE },
		{ CRaceData::RACE_WARRIOR_W,  CItemData::ITEM_ANTIFLAG_WARRIOR,  CItemData::ITEM_ANTIFLAG_FEMALE },
		{ CRaceData::RACE_ASSASSIN_M, CItemData::ITEM_ANTIFLAG_ASSASSIN, CItemData::ITEM_ANTIFLAG_MALE },
		{ CRaceData::RACE_SURA_W,	 CItemData::ITEM_ANTIFLAG_SURA,	 CItemData::ITEM_ANTIFLAG_FEMALE },
		{ CRaceData::RACE_SHAMAN_M,   CItemData::ITEM_ANTIFLAG_SHAMAN,   CItemData::ITEM_ANTIFLAG_MALE }
	};

	for (const auto& flag : raceFlags) {
		if (flag.race == race) {
			return !itemData->IsAntiFlag(flag.classFlag) && !itemData->IsAntiFlag(flag.genderFlag);
		}
	}
	return false;
}
#endif

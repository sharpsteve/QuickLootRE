#pragma once

#include "skse64/GameExtraData.h"  // InventoryEntryData
#include <string>
#include <utility>


class InventoryEntryData;
class TESForm;

namespace QuickLootRE
{
	class ItemData
	{
	private:
		enum Type
		{
			kType_None,
			kType_DefaultWeapon,
			kType_WeaponSword,
			kType_WeaponGreatSword,
			kType_WeaponDaedra,
			kType_WeaponDagger,
			kType_WeaponWarAxe,
			kType_WeaponBattleAxe,
			kType_WeaponMace,
			kType_WeaponHammer,
			kType_WeaponStaff,
			kType_WeaponBow,
			kType_WeaponArrow,
			kType_WeaponPickAxe,
			kType_WeaponWoodAxe,
			kType_WeaponCrossbow,
			kType_WeaponBolt,

			kType_DefaultArmor,

			kType_LightArmorBody,
			kType_LightArmorHead,
			kType_LightArmorHands,
			kType_LightArmorForearms,
			kType_LightArmorFeet,
			kType_LightArmorCalves,
			kType_LightArmorShield,
			kType_LightArmorMask,

			kType_ArmorBody,
			kType_ArmorHead,
			kType_ArmorHands,
			kType_ArmorForearms,
			kType_ArmorFeet,
			kType_ArmorCalves,
			kType_ArmorShield,
			kType_ArmorMask,
			kType_ArmorBracer,
			kType_ArmorDaedra,

			kType_ClothingBody,
			kType_ClothingRobe,
			kType_ClothingHead,
			kType_ClothingPants,
			kType_ClothingHands,
			kType_ClothingForearms,
			kType_ClothingFeet,
			kType_ClothingCalves,
			kType_ClothingShoes,
			kType_ClothingShield,
			kType_ClothingMask,

			kType_ArmorAmulet,
			kType_ArmorRing,
			kType_Circlet,

			kType_DefaultScroll,

			kType_DefaultBook,
			kType_BookRead,
			kType_BookTome,
			kType_TomeRead,
			kType_BookJournal,
			kType_BookNote,
			kType_BookMap,

			kType_DefaultFood,
			kType_FoodWine,
			kType_FoodBeer,

			kType_DefaultIngredient,

			kType_DefaultKey,
			kType_KeyHouse,

			kType_DefaultPotion,
			kType_PotionHealth,
			kType_PotionStam,
			kType_PotionMagic,
			kType_PotionPoison,
			kType_PotionFrost,
			kType_PotionFire,
			kType_PotionShock,

			kType_DefaultMisc,
			kType_MiscArtifact,
			kType_MiscClutter,
			kType_MiscLockPick,
			kType_MiscSoulGem,

			kType_SoulGemEmpty,
			kType_SoulGemPartial,
			kType_SoulGemFull,
			kType_SoulGemGrandEmpty,
			kType_SoulGemGrandPartial,
			kType_SoulGemGrandFull,
			kType_SoulGemAzura,

			kType_MiscGem,
			kType_MiscOre,
			kType_MiscIngot,
			kType_MiscHide,
			kType_MiscStrips,
			kType_MiscLeather,
			kType_MiscWood,
			kType_MiscRemains,
			kType_MiscTrollSkull,
			kType_MiscTorch,
			kType_MiscGoldSack,
			kType_MiscGold,
			kType_MiscDragonClaw
		};

	public:
		ItemData(InventoryEntryData* a_entryData);

	private:
		Type getItemType();

		InventoryEntryData* _entryData;
		Type _type;
		UInt32 _priority;
		const char* _name;
		bool _isStolen;
		bool _isEnchanted;
		bool _isQuestItem;
	};
}

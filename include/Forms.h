#pragma once

#include "skse64/GameForms.h"  // LookupFormByID

class BGSPerk;
class BGSKeyword;

namespace RE
{
	class TESFaction;
}


namespace QuickLootRE
{
	enum FACTFormID : UInt32
	{
		kFACTFormID_CurrentFollowerFaction	= 0x0005C84E
	};


	enum KYWDFormID : UInt32
	{
		kKYWDFormID_VendorItemClothing			= 0x0008F95B,
		kKYWDFormID_VendorItemJewelry			= 0x0008F95A,

		kKYWDFormID_VendorItemRecipe			= 0x000F5CB0,
		kKYWDFormID_VendorItemSpellTome			= 0x000937A5,

		kKYWDFormID_VendorItemAnimalHide		= 0x000914EA,
		kKYWDFormID_VendorItemDaedricArtifact	= 0x000917E8,
		kKYWDFormID_VendorItemGem				= 0x000914ED,
		kKYWDFormID_VendorItemAnimalPart		= 0x000914EB,
		kKYWDFormID_VendorItemOreIngot			= 0x000914EC,
		kKYWDFormID_VendorItemClutter			= 0x000914E9,
		kKYWDFormID_VendorItemFireword			= 0x000BECD7,

		kKYWDFormID_WeapTypeWarhammer			= 0x0006D930,

		kKYWDFormID_ActorTypeCreature			= 0x00013795,
		kKYWDFormID_ActorTypeAnimal				= 0x00013798
	};


	enum MISCFormID : UInt32
	{
		kMISCFormID_LockPick				= 0x0000000A,
		kMISCFormID_Gold					= 0x0000000F,
		kMISCFormID_Leather01				= 0x000DB5D2,
		kMISCFormID_LeatherStrips			= 0x000800E4,

		kMISCFormID_DragonClawIron			= 0x0008CDFA,
		kMISCFormID_DragonClawGoldenE3		= 0x000999E7,
		kMISCFormID_DragonClawGoldenMS13	= 0x00039647,
		kMISCFormID_DragonClawCoral			= 0x000B634C,
		kMISCFormID_DragonClawIvory			= 0x000AB7BB,
		kMISCFormID_DragonClawRuby			= 0x0004B56C,
		kMISCFormID_DragonClawSapphire		= 0x000663D7,
		kMISCFormID_DragonClawEmerald		= 0x000ED417,
		kMISCFormID_DragonClawGlass			= 0x0007C260,
		kMISCFormID_DragonClawEbony			= 0x0005AF48,
		kMISCFormID_DragonClawDiamond		= 0x000AB375,
	};


	enum PERKFormID : UInt32
	{
		kPERKFormID_VampireFeed		= 0x000CF02C,
		kPERKFormID_Cannibalism		= 0x000EE5C3,

		kPERKFormID_Misdirection	= 0x00058201,
		kPERKFormID_PerfectTouch	= 0x00058205
	};


	enum SLGMFormID : UInt32
	{
		kSLGMFormID_DA01SoulGemAzurasStar	= 0x00063B27,
		kSLGMFormID_DA01SoulGemBlackStar	= 0x00063B29
	};


	enum SNDRFormID : UInt32
	{
		kSNDRFormID_ITMPotionUse = 0x000B6435
	};


	template <typename T>
	class Form
	{
	public:
		Form(UInt32 a_formID) : _formID(a_formID) {}

		operator T()
		{
			return static_cast<T>(LookupFormByID(_formID));
		}

	private:
		UInt32 _formID;
	};


	// Factions
	extern Form<RE::TESFaction*>	CurrentFollowerFaction;

	// Keywords
	extern Form<BGSKeyword*>		VendorItemClothing;
	extern Form<BGSKeyword*>		VendorItemJewelry;

	extern Form<BGSKeyword*>		VendorItemRecipe;
	extern Form<BGSKeyword*>		VendorItemSpellTome;

	extern Form<BGSKeyword*>		VendorItemAnimalHide;
	extern Form<BGSKeyword*>		VendorItemDaedricArtifact;
	extern Form<BGSKeyword*>		VendorItemGem;
	extern Form<BGSKeyword*>		VendorItemAnimalPart;
	extern Form<BGSKeyword*>		VendorItemOreIngot;
	extern Form<BGSKeyword*>		VendorItemClutter;
	extern Form<BGSKeyword*>		VendorItemFireword;

	extern Form<BGSKeyword*>		WeapTypeWarhammer;

	extern Form<BGSKeyword*>		ActorTypeCreature;
	extern Form<BGSKeyword*>		ActorTypeAnimal;

	// Perks
	extern Form<BGSPerk*>			Misdirection;
	extern Form<BGSPerk*>			PerfectTouch;
}

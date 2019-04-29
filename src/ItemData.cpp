#include "ItemData.h"

#include <limits>  // numeric_limits
#include <string>  // string

#include "Forms.h"  // keywords, FormID
#include "Settings.h"  // Settings
#include "Utility.h"  // IsValidPickPocketTarget

#include "RE/Skyrim.h"


ItemData::ItemData() :
	_entryData(nullptr),
	_name(""),
	_count(0),
	_value(0),
	_weight(0.0),
	_type(Type::kNone),
	_isStolen(false),
	_isRead(false),
	_isEnchanted(false),
	_canPickPocket(true),
	_pickPocketChance(-1),
	_priority(Priority::kKey)
{}


ItemData::ItemData(ManagedEntryDataPtr a_entryData) :
	_entryData(a_entryData),
	_name(""),
	_count(0),
	_value(0),
	_weight(0.0),
	_type(Type::kNone),
	_isStolen(false),
	_isRead(false),
	_isEnchanted(false),
	_canPickPocket(true),
	_pickPocketChance(-1),
	_priority(Priority::kKey)
{
	_count = _entryData->Get()->countDelta;
	constructCommon();
}


ItemData::ItemData(ManagedEntryDataPtr a_entryData, SInt32 a_count) :
	_entryData(a_entryData),
	_name(""),
	_count(a_count),
	_value(0),
	_weight(0.0),
	_type(Type::kNone),
	_isStolen(false),
	_isRead(false),
	_isEnchanted(false),
	_canPickPocket(true),
	_pickPocketChance(-1),
	_priority(Priority::kKey)
{
	constructCommon();
}


ItemData::~ItemData()
{}


void ItemData::setCompareOrder()
{
	_compares.clear();
	for (auto& compare : Settings::sortOrder) {
		if (compare == NAME) {
			_compares.push_back(&compareByName);
			_DMESSAGE("[DEBUG] Added compare by %s", NAME.c_str());
		} else if (compare == "r_" + NAME) {
			_compares.push_back(&r_compareByName);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", NAME.c_str());
		} else if (compare == COUNT) {
			_compares.push_back(&compareByCount);
			_DMESSAGE("[DEBUG] Added compare by %s", COUNT.c_str());
		} else if (compare == "r_" + COUNT) {
			_compares.push_back(&r_compareByCount);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", COUNT.c_str());
		} else if (compare == VALUE) {
			_compares.push_back(&compareByValue);
			_DMESSAGE("[DEBUG] Added compare by %s", VALUE.c_str());
		} else if (compare == "r_" + VALUE) {
			_compares.push_back(&r_compareByValue);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", VALUE.c_str());
		} else if (compare == WEIGHT) {
			_compares.push_back(&compareByWeight);
			_DMESSAGE("[DEBUG] Added compare by %s", WEIGHT.c_str());
		} else if (compare == "r_" + WEIGHT) {
			_compares.push_back(&r_compareByWeight);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", WEIGHT.c_str());
		} else if (compare == TYPE) {
			_compares.push_back(&compareByType);
			_DMESSAGE("[DEBUG] Added compare by %s", TYPE.c_str());
		} else if (compare == "r_" + TYPE) {
			_compares.push_back(&r_compareByType);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", TYPE.c_str());
		} else if (compare == READ) {
			_compares.push_back(&compareByRead);
			_DMESSAGE("[DEBUG] Added compare by %s", READ.c_str());
		} else if (compare == "r_" + READ) {
			_compares.push_back(&r_compareByRead);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", READ.c_str());
		} else if (compare == ENCHANTED) {
			_compares.push_back(&compareByEnchanted);
			_DMESSAGE("[DEBUG] Added compare by %s", ENCHANTED.c_str());
		} else if (compare == "r_" + ENCHANTED) {
			_compares.push_back(&r_compareByEnchanted);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", ENCHANTED.c_str());
		} else if (compare == PICK_POCKET_CHANCE) {
			_compares.push_back(&compareByPickPocketChance);
			_DMESSAGE("[DEBUG] Added compare by %s", PICK_POCKET_CHANCE.c_str());
		} else if (compare == "r_" + PICK_POCKET_CHANCE) {
			_compares.push_back(&r_compareByPickPocketChance);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", PICK_POCKET_CHANCE.c_str());
		} else if (compare == VALUE_PER_WEIGHT) {
			_compares.push_back(&compareByValuePerWeight);
			_DMESSAGE("[DEBUG] Added compare by %s", VALUE_PER_WEIGHT.c_str());
		} else if (compare == "r_" + VALUE_PER_WEIGHT) {
			_compares.push_back(&r_compareByValuePerWeight);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", VALUE_PER_WEIGHT.c_str());
		} else if (compare == PRIORITY) {
			_compares.push_back(&compareByPriority);
			_DMESSAGE("[DEBUG] Added compare by %s", PRIORITY.c_str());
		} else if (compare == "r_" + PRIORITY) {
			_compares.push_back(&r_compareByPriority);
			_DMESSAGE("[DEBUG] Added compare by reverse %s", PRIORITY.c_str());
		} else {
			_ERROR("[ERROR] Encountered unknown compare (%s)!\n", compare.c_str());
		}
	}
}


void ItemData::setContainer(RE::TESObjectREFR* a_container)
{
	_container = a_container;
}


bool operator==(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return (a_lhs._entryData == a_rhs._entryData &&
			a_lhs._name == a_rhs._name &&
			a_lhs._count == a_rhs._count &&
			a_lhs._value == a_rhs._value &&
			a_lhs._weight == a_rhs._weight &&
			a_lhs._type == a_rhs._type &&
			a_lhs._isStolen == a_rhs._isStolen &&
			a_lhs._isEnchanted == a_rhs._isEnchanted &&
			a_lhs._pickPocketChance == a_rhs._pickPocketChance &&
			a_lhs._priority == a_rhs._priority);
}


bool operator!=(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return !operator==(a_lhs, a_rhs);
}


bool operator<(const ItemData& a_lhs, const ItemData& a_rhs)
{
	if (a_lhs._canPickPocket != a_rhs._canPickPocket) {
		return a_rhs._canPickPocket;  // Ensures items that can't be pickpocketed sort to the end
	}

	for (auto& compare : ItemData::_compares) {
		int cmp = compare(a_lhs, a_rhs);
		if (cmp) {
			return cmp < 0;
		}
	}

	return a_lhs._entryData < a_rhs._entryData;
}


bool operator>(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return operator<(a_rhs, a_lhs);
}


bool operator<=(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return !operator>(a_lhs, a_rhs);
}


bool operator>=(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return !operator<(a_lhs, a_rhs);
}


RE::InventoryEntryData* ItemData::entryData() const
{
	return _entryData->Get();
}


const char* ItemData::name() const
{
	return _name;
}


SInt32 ItemData::count() const
{
	return _count;
}


SInt32 ItemData::value() const
{
	return _value;
}


float ItemData::weight() const
{
	return _weight;
}


const char* ItemData::icon() const
{
	return _strIcons[to_underlying(_type)];
}


bool ItemData::isStolen() const
{
	return _isStolen;
}


bool ItemData::isRead() const
{
	return _isRead;
}


bool ItemData::isEnchanted() const
{
	return _isEnchanted;
}


SInt32 ItemData::pickPocketChance() const
{
	return _pickPocketChance;
}


RE::TESForm* ItemData::form() const
{
	return _entryData->Get()->type;
}


bool ItemData::canPickPocket() const
{
	return _canPickPocket;
}


void ItemData::modCount(SInt32 a_mod)
{
	_count += a_mod;
}


void ItemData::dbgDumpType(UInt32 a_index)
{
	switch (ITEM_DATA_DEBUG_TYPE) {
	case kDebugType_Name:
		_DMESSAGE("[DEBUG] (%s) %s == (%s: %u)", _name, NAME.c_str(), _name, a_index);
		break;
	case kDebugType_Count:
		_DMESSAGE("[DEBUG] (%i) %s == (%s: %u)", _count, COUNT.c_str(), _name, a_index);
		break;
	case kDebugType_Value:
		_DMESSAGE("[DEBUG] (%i) %s == (%s: %u)", _value, VALUE.c_str(), _name, a_index);
		break;
	case kDebugType_Weight:
		_DMESSAGE("[DEBUG] (%F) %s == (%s: %u)", _weight, WEIGHT.c_str(), _name, a_index);
		break;
	case kDebugType_Type:
		_DMESSAGE("[DEBUG] (%u) %s == (%s: %u)", _type, TYPE.c_str(), _name, a_index);
		break;
	case kDebugType_Read:
		_DMESSAGE("[DEBUG] (%s) %s == (%s: %u)", boolToString(_isRead).c_str(), READ.c_str(), _name, a_index);
		break;
	case kDebugType_Enchanted:
		_DMESSAGE("[DEBUG] (%s) %s == (%s: %u)", boolToString(_isEnchanted).c_str(), ENCHANTED.c_str(), _name, a_index);
		break;
	case kDebugType_PickPocketChance:
		_DMESSAGE("[DEBUG] (%i) %s == (%s: %u)", _pickPocketChance, PICK_POCKET_CHANCE.c_str(), _name, a_index);
		break;
	case kDebugType_ValuePerWeight:
		{
			float vpw = _weight ? _value / _weight : std::numeric_limits<float>::infinity();
			_DMESSAGE("[DEBUG] (%F) %s == (%s: %u)", vpw, VALUE_PER_WEIGHT.c_str(), _name, a_index);
			break;
		}
	case kDebugType_Priority:
		_DMESSAGE("[DEBUG] (%u) %s == (%s: %u)", _priority, PRIORITY.c_str(), _name, a_index);
		break;
	}
}


void ItemData::constructCommon()
{
	_name = _entryData->Get()->GenerateName();
	_value = _entryData->Get()->GetValue();
	_weight = getWeight();
	_type = getType();
	_isStolen = getStolen();
	_isRead = getRead();
	_isEnchanted = getEnchanted();
	_canPickPocket = getCanPickPocket();
	_pickPocketChance = getPickPocketChance();
	_priority = getPriority();
}


float ItemData::getWeight()
{
	auto weightForm = skyrim_cast<RE::TESWeightForm*>(_entryData->Get()->type);
	return weightForm ? weightForm->weight : 0.0;
}


ItemData::Type ItemData::getType()
{
	switch (_entryData->Get()->type->formType) {
	case RE::FormType::Scroll:
		return Type::kDefaultScroll;
	case RE::FormType::Armor:
		return getTypeArmor(static_cast<RE::TESObjectARMO*>(_entryData->Get()->type));
	case RE::FormType::Book:
		return getTypeBook(static_cast<RE::TESObjectBOOK*>(_entryData->Get()->type));
	case RE::FormType::Ingredient:
		return Type::kDefaultIngredient;
	case RE::FormType::Light:
		return Type::kMiscTorch;
	case RE::FormType::Misc:
		return getTypeMisc(static_cast<RE::TESObjectMISC*>(_entryData->Get()->type));
	case RE::FormType::Weapon:
		return getTypeWeapon(static_cast<RE::TESObjectWEAP*>(_entryData->Get()->type));
	case RE::FormType::Ammo:
		return (static_cast<RE::TESAmmo*>(_entryData->Get()->type)->IsBolt()) ? Type::kWeaponBolt : Type::kWeaponArrow;
	case RE::FormType::KeyMaster:
		return Type::kDefaultKey;
	case RE::FormType::AlchemyItem:
		return getTypePotion(static_cast<RE::AlchemyItem*>(_entryData->Get()->type));
	case RE::FormType::SoulGem:
		return getTypeSoulGem(static_cast<RE::TESSoulGem*>(_entryData->Get()->type));
	default:
		return Type::kNone;
	}
}


ItemData::Type ItemData::getTypeArmor(RE::TESObjectARMO* a_armor)
{
	using FirstPersonFlag = RE::BGSBipedObjectForm::BipedBodyTemplate::FirstPersonFlag;

	static Type types[] = {
		Type::kLightArmorBody,		// 0
		Type::kLightArmorHead,
		Type::kLightArmorHands,
		Type::kLightArmorForearms,
		Type::kLightArmorFeet,
		Type::kLightArmorCalves,
		Type::kLightArmorShield,
		Type::kLightArmorMask,

		Type::kArmorBody,			// 8
		Type::kArmorHead,
		Type::kArmorHands,
		Type::kArmorForearms,
		Type::kArmorFeet,
		Type::kArmorCalves,
		Type::kArmorShield,
		Type::kArmorMask,

		Type::kClothingBody,		// 16
		Type::kClothingHead,
		Type::kClothingHands,
		Type::kClothingForearms,
		Type::kClothingFeet,
		Type::kClothingCalves,
		Type::kClothingShield,
		Type::kClothingMask,

		Type::kArmorAmulet,			// 24
		Type::kArmorRing,
		Type::kCirclet,

		Type::kDefaultArmor			// 27
	};

	UInt32 index = 0;
	auto bipedObj = static_cast<RE::BGSBipedObjectForm*>(a_armor);

	if (bipedObj->IsLightArmor()) {
		index = 0;
	} else if (bipedObj->IsHeavyArmor()) {
		index = 8;
	} else {
		if (a_armor->HasKeyword(VendorItemClothing)) {
			index = 16;
		} else if (a_armor->HasKeyword(VendorItemJewelry)) {
			if (bipedObj->HasPartOf(FirstPersonFlag::kAmulet)) {
				index = 24;
			} else if (bipedObj->HasPartOf(FirstPersonFlag::kRing)) {
				index = 25;
			} else if (bipedObj->HasPartOf(FirstPersonFlag::kCirclet)) {
				index = 26;
			} else {
				index = 27;
			}
		} else {
			index = 27;
		}
	}

	if (index >= 24) {
		return types[index];
	}

	if (bipedObj->HasPartOf(FirstPersonFlag::kBody | FirstPersonFlag::kTail)) {
		index += 0;
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kHead | FirstPersonFlag::kHair | FirstPersonFlag::kLongHair)) {
		index += 1;
		if (bipedObj->HasPartOf(FirstPersonFlag::kCirclet)) {
			index += 6;
		}
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kHands)) {
		index += 2;
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kForearms)) {
		index += 3;
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kFeet)) {
		index += 4;
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kCalves)) {
		index += 5;
	} else if (bipedObj->HasPartOf(FirstPersonFlag::kShield)) {
		index += 6;
	} else {
		index = 27;
	}

	return types[index];
}


ItemData::Type ItemData::getTypeBook(RE::TESObjectBOOK* a_book)
{
	using BookType = RE::TESObjectBOOK::Data::Type;

	if (a_book->data.type == BookType::kNoteScroll || a_book->HasKeyword(VendorItemRecipe)) {
		return Type::kBookNote;
	} else if (a_book->HasKeyword(VendorItemSpellTome)) {
		return Type::kBookTome;
	} else {
		return Type::kDefaultBook;
	}
}


ItemData::Type ItemData::getTypeMisc(RE::TESObjectMISC* a_misc)
{
	switch (a_misc->formID) {
	case kMISCFormID_LockPick:
		return Type::kMiscLockPick;
	case kMISCFormID_Gold:
		return Type::kMiscGold;
	case kMISCFormID_Leather01:
		return Type::kMiscLeather;
	case kMISCFormID_LeatherStrips:
		return Type::kMiscStrips;
	case kMISCFormID_DragonClawIron:
	case kMISCFormID_DragonClawGoldenE3:
	case kMISCFormID_DragonClawGoldenMS13:
	case kMISCFormID_DragonClawCoral:
	case kMISCFormID_DragonClawIvory:
	case kMISCFormID_DragonClawRuby:
	case kMISCFormID_DragonClawSapphire:
	case kMISCFormID_DragonClawEmerald:
	case kMISCFormID_DragonClawGlass:
	case kMISCFormID_DragonClawEbony:
	case kMISCFormID_DragonClawDiamond:
		return Type::kMiscDragonClaw;
	default:
		if (a_misc->HasKeyword(VendorItemAnimalHide)) {
			return Type::kMiscHide;
		} else if (a_misc->HasKeyword(VendorItemDaedricArtifact)) {
			return Type::kMiscArtifact;
		} else if (a_misc->HasKeyword(VendorItemGem)) {
			return Type::kMiscGem;
		} else if (a_misc->HasKeyword(VendorItemAnimalPart)) {
			return Type::kMiscRemains;
		} else if (a_misc->HasKeyword(VendorItemOreIngot)) {
			return Type::kMiscIngot;
		} else if (a_misc->HasKeyword(VendorItemClutter)) {
			return Type::kMiscClutter;
		} else if (a_misc->HasKeyword(VendorItemFireword)) {
			return Type::kMiscWood;
		} else {
			return Type::kDefaultMisc;
		}
	}
}


ItemData::Type ItemData::getTypeWeapon(RE::TESObjectWEAP* a_weap)
{
	using AnimationType = RE::TESObjectWEAP::Data::AnimationType;

	switch (a_weap->animationType()) {
	case AnimationType::kOneHandSword:
		return Type::kWeaponSword;
	case AnimationType::kOneHandDagger:
		return Type::kWeaponDagger;
	case AnimationType::kOneHandAxe:
		return Type::kWeaponWarAxe;
	case AnimationType::kOneHandMace:
		return Type::kWeaponMace;
	case AnimationType::kTwoHandSword:
		return Type::kWeaponGreatSword;
	case AnimationType::kTwoHandAxe:
		if (a_weap->HasKeyword(WeapTypeWarhammer)) {
			return Type::kWeaponHammer;
		} else {
			return Type::kWeaponBattleAxe;
		}
	case AnimationType::kBow:
		return Type::kWeaponBow;
	case AnimationType::kStaff:
		return Type::kWeaponStaff;
	case AnimationType::kCrossbow:
		return Type::kWeaponCrossbow;
	default:
		return Type::kDefaultWeapon;
	}
}


ItemData::Type ItemData::getTypePotion(RE::AlchemyItem* a_potion)
{
	using RE::ActorValue;

	if (a_potion->IsFoodItem()) {
		return (a_potion->effectData.consumeSound && a_potion->effectData.consumeSound->formID == kSNDRFormID_ITMPotionUse) ? Type::kFoodWine : Type::kDefaultFood;
	} else if (a_potion->IsPoison()) {
		return Type::kPotionPoison;
	} else {
		auto effect = a_potion->GetCostliestEffectItem();
		if (effect && effect->baseEffect) {
			switch (effect->baseEffect->data.primaryActorValue) {
			case ActorValue::kHealth:
				return Type::kPotionHealth;
			case ActorValue::kMagicka:
				return Type::kPotionMagic;
			case ActorValue::kStamina:
				return Type::kPotionStam;
			case ActorValue::kResistFire:
				return Type::kPotionFire;
			case ActorValue::kResistShock:
				return Type::kPotionShock;
			case ActorValue::kResistFrost:
				return Type::kPotionFrost;
			}
		}
	}
	return Type::kDefaultPotion;
}


ItemData::Type ItemData::getTypeSoulGem(RE::TESSoulGem* a_gem)
{
	using RE::SoulLevel;

	switch (a_gem->GetFormID()) {
	case kSLGMFormID_DA01SoulGemBlackStar:
	case kSLGMFormID_DA01SoulGemAzurasStar:
		return Type::kSoulGemAzura;
	default:
		{
			auto soulSize = _entryData->Get()->GetSoulLevel();
			if (a_gem->GetMaximumCapacity() < SoulLevel::kGreater) {
				if (soulSize >= a_gem->GetMaximumCapacity()) {
					return Type::kSoulGemFull;
				} else if (soulSize > SoulLevel::kNone) {
					return Type::kSoulGemPartial;
				} else {
					return Type::kSoulGemEmpty;
				}
			} else {
				if (soulSize >= a_gem->GetMaximumCapacity()) {
					return Type::kSoulGemGrandFull;
				} else if (soulSize > SoulLevel::kNone) {
					return Type::kSoulGemGrandPartial;
				} else {
					return Type::kSoulGemGrandEmpty;
				}
			}
		}
	}
}


bool ItemData::getStolen()
{
	auto player = RE::PlayerCharacter::GetSingleton();

	auto owner = _entryData->Get()->GetOwner();
	if (!owner) {
		owner = _container->GetOwner();
	}
	if (owner) {
		return !_entryData->Get()->IsOwnedBy(player, owner);
	} else {
		return player->IsSneaking() && _container->baseForm->Is(RE::FormType::NPC) && !_container->IsDead(true);
	}
}


bool ItemData::getEnchanted()
{
	if (_entryData->Get()->extraList) {
		for (auto& xList : *_entryData->Get()->extraList) {
			if (xList->HasType(RE::ExtraDataType::kEnchantment)) {
				return true;
			}
		}
	}
	auto enchantForm = skyrim_cast<RE::TESEnchantableForm*>(_entryData->Get()->type);
	if (enchantForm && enchantForm->objectEffect) {
		return true;
	}
	return false;
}


bool ItemData::getCanPickPocket()
{
	if (_container->baseForm->IsNot(RE::FormType::NPC)) {
		return true;
	}

	auto actor = static_cast<RE::Actor*>(_container);
	if (actor->IsDead(true)) {
		return true;
	}

	if (!_entryData->Get()->extraList) {
		return true;
	}

	for (auto& xList : *_entryData->Get()->extraList) {
		if (xList->HasType(RE::ExtraDataType::kWorn) || xList->HasType(RE::ExtraDataType::kWornLeft)) {
			RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
			if (_entryData->Get()->type->Is(RE::FormType::Weapon)) {
				if (!player->HasPerk(Misdirection)) {
					return false;
				}
			} else {
				if (!player->HasPerk(PerfectTouch)) {
					return false;
				}
			}
		}
	}

	return true;
}


SInt32 ItemData::getPickPocketChance()
{
	auto player = RE::PlayerCharacter::GetSingleton();
	if (IsValidPickPocketTarget(_container, player->IsSneaking())) {
		auto targetActor = static_cast<RE::Actor*>(_container);

		float itemWeight = _entryData->Get()->GetWeight();
		UInt32 totalValue = targetActor->CalcEntryValue(_entryData->Get(), _count, true);
		bool isDetected = targetActor->GetDetectionLevel(player, 3) > 0;
		float playerSkill = player->GetPlayerActorValueCurrent(RE::ActorValue::kPickpocket);
		float targetSkill = targetActor->GetActorValueCurrent(RE::ActorValue::kPickpocket);

		UInt32 chance = RE::PlayerCharacter::GetPickpocketChance(playerSkill, targetSkill, totalValue, itemWeight, player, targetActor, isDetected, _entryData->Get()->type);
		if (chance > 100) {
			chance = 100;
		} else if (chance < 0) {
			chance = 0;
		}
		return chance;
	} else {
		return -1;
	}
}


bool ItemData::getRead()
{
	if (_entryData->Get()->type->Is(RE::FormType::Book)) {
		auto book = static_cast<RE::TESObjectBOOK*>(_entryData->Get()->type);
		return book->IsRead();
	} else {
		return false;
	}
}


ItemData::Priority ItemData::getPriority()
{
	switch (_entryData->Get()->type->formType) {
	case RE::FormType::Ammo:
		return Priority::kAmmo;
	case RE::FormType::SoulGem:
		return Priority::kSoulGem;
	case RE::FormType::AlchemyItem:
		switch (_type) {
		case Type::kDefaultFood:
		case Type::kFoodWine:
		case Type::kFoodBeer:
			return Priority::kFood;
		case Type::kPotionPoison:
			return Priority::kPoison;
		default:
			return Priority::kPotion;
		}
	case RE::FormType::Weapon:
		return (_isEnchanted) ? Priority::kEnchantedWeapon : Priority::kWeapon;
	case RE::FormType::Armor:
		if (_isEnchanted) {
			return Priority::kEnchantedArmor;
		} else if (_type == Type::kArmorAmulet) {
			return Priority::kAmulet;
		} else if (_type == Type::kArmorRing) {
			return Priority::kRing;
		} else {
			return Priority::kArmor;
		}
	case RE::FormType::KeyMaster:
		return Priority::kKey;
	case RE::FormType::Misc:
		switch (_type) {
		case Type::kMiscGold:
			return Priority::kGold;
		case Type::kMiscLockPick:
			return Priority::kLockPick;
		case Type::kMiscGem:
			return Priority::kGem;
		default:
			return Priority::kOther;
		}
	default:
		return Priority::kOther;
	}
}


int compareByName(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return strcmp(a_rhs._name, a_lhs._name);	// Intentionally flipped to ensure the list is sorted alphabetically
}


int r_compareByName(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByName(a_lhs, a_rhs);
}


int compareByCount(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return a_lhs._count - a_rhs._count;
}


int r_compareByCount(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByCount(a_lhs, a_rhs);
}


int compareByValue(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return a_lhs._value - a_rhs._value;
}


int r_compareByValue(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByValue(a_lhs, a_rhs);
}


int compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs)
{
	float result = a_lhs._weight - a_rhs._weight;
	if (result < -0.0001) {
		return -1;
	} else if (result > 0.0001) {
		return 1;
	} else {
		return 0;
	}
}


int r_compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByWeight(a_lhs, a_rhs);
}


int compareByType(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return to_underlying(a_lhs._type) - to_underlying(a_rhs._type);
}


int r_compareByType(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByType(a_lhs, a_rhs);
}


int compareByRead(const ItemData& a_lhs, const ItemData& a_rhs)
{
	SInt32 valueLHS = a_lhs._isRead ? 1 : 0;
	SInt32 valueRHS = a_rhs._isRead ? 1 : 0;
	return valueLHS - valueRHS;
}


int r_compareByRead(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByRead(a_lhs, a_rhs);
}


int compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs)
{
	SInt32 valueLHS = a_lhs._isEnchanted ? 1 : 0;
	SInt32 valueRHS = a_rhs._isEnchanted ? 1 : 0;
	return valueLHS - valueRHS;
}


int r_compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByEnchanted(a_lhs, a_rhs);
}


int compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs)
{
	float result = a_lhs._pickPocketChance - a_rhs._pickPocketChance;
	if (result < -0.0001) {
		return -1;
	} else if (result > 0.0001) {
		return 1;
	} else {
		return 0;
	}
}


int r_compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByPickPocketChance(a_lhs, a_rhs);
}


int compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs)
{
	float leftVpW = a_lhs._weight ? a_lhs._value / a_lhs._weight : std::numeric_limits<float>::infinity();
	float rightVpW = a_rhs._weight ? a_rhs._value / a_rhs._weight : std::numeric_limits<float>::infinity();
	float result = leftVpW - rightVpW;
	if (result < -0.0001) {
		return -1;
	} else if (result > 0.0001) {
		return 1;
	} else {
		return 0;
	}
}


int r_compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByValuePerWeight(a_lhs, a_rhs);
}


int compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return to_underlying(a_rhs._priority) - to_underlying(a_lhs._priority);  // Lower numbers have higher priority
}


int r_compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs)
{
	return -1 * compareByPriority(a_lhs, a_rhs);
}


decltype(ItemData::NAME)				ItemData::NAME = "name";
decltype(ItemData::COUNT)				ItemData::COUNT = "count";
decltype(ItemData::VALUE)				ItemData::VALUE = "value";
decltype(ItemData::WEIGHT)				ItemData::WEIGHT = "weight";
decltype(ItemData::TYPE)				ItemData::TYPE = "type";
decltype(ItemData::READ)				ItemData::READ = "read";
decltype(ItemData::ENCHANTED)			ItemData::ENCHANTED = "enchanted";
decltype(ItemData::PICK_POCKET_CHANCE)	ItemData::PICK_POCKET_CHANCE = "pickPocketChance";
decltype(ItemData::VALUE_PER_WEIGHT)	ItemData::VALUE_PER_WEIGHT = "valuePerWeight";
decltype(ItemData::PRIORITY)			ItemData::PRIORITY = "priority";
decltype(ItemData::_compares)			ItemData::_compares;

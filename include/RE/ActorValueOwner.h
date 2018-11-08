#pragma once

#include "skse64_common/Utilities.h"

#include "Offsets.h"


namespace RE
{
	class ActorValueOwner
	{
	public:
		enum ActorValue
		{
			kActorValue_Aggression = 0,
			kActorValue_Confidence,
			kActorValue_Energy,
			kActorValue_Morality,
			kActorValue_Mood,
			kActorValue_Assistance,
			kActorValue_Onehanded,
			kActorValue_Twohanded,
			kActorValue_Marksman,
			kActorValue_Block,
			kActorValue_Smithing,
			kActorValue_HeavyArmor,
			kActorValue_LightArmor,
			kActorValue_Pickpocket,
			kActorValue_Lockpicking,
			kActorValue_Sneak,
			kActorValue_Alchemy,
			kActorValue_Speechcraft,
			kActorValue_Alteration,
			kActorValue_Conjuration,
			kActorValue_Destruction,
			kActorValue_Illusion,
			kActorValue_Restoration,
			kActorValue_Enchanting,
			kActorValue_Health,
			kActorValue_Magicka,
			kActorValue_Stamina,
			kActorValue_Healrate,
			kActorValue_MagickaRate,
			kActorValue_StaminaRate,
			kActorValue_SpeedMult,
			kActorValue_InventoryWeight,
			kActorValue_CarryWeight,
			kActorValue_CritChance,
			kActorValue_MeleeDamage,
			kActorValue_UnarmedDamage,
			kActorValue_Mass,
			kActorValue_VoicePoints,
			kActorValue_VoiceRate,
			kActorValue_DamageResist,
			kActorValue_PoisonResist,
			kActorValue_FireResist,
			kActorValue_ElectricResist,
			kActorValue_FrostResist,
			kActorValue_MagicResist,
			kActorValue_DiseaseResist,
			kActorValue_PerceptionCondition,
			kActorValue_EnduranceCondition,
			kActorValue_LeftAttackCondition,
			kActorValue_RightAttackCondition,
			kActorValue_LeftMobilityCondition,
			kActorValue_RightMobilityCondition,
			kActorValue_BrainCondition,
			kActorValue_Paralysis,
			kActorValue_Invisibility,
			kActorValue_NightEye,
			kActorValue_DetectLifeRange,
			kActorValue_WaterBreathing,
			kActorValue_WaterWalking,
			kActorValue_IgnoreCrippledLimbs,
			kActorValue_Fame,
			kActorValue_Infamy,
			kActorValue_JumpingBonus,
			kActorValue_WardPower,
			kActorValue_RightItemCharge,
			kActorValue_ArmorPerks,
			kActorValue_ShieldPerks,
			kActorValue_WardDeflection,
			kActorValue_Variable01,
			kActorValue_Variable02,
			kActorValue_Variable03,
			kActorValue_Variable04,
			kActorValue_Variable05,
			kActorValue_Variable06,
			kActorValue_Variable07,
			kActorValue_Variable08,
			kActorValue_Variable09,
			kActorValue_Variable10,
			kActorValue_BowSpeedBonus,
			kActorValue_FavorActive,
			kActorValue_FavorSperDay,
			kActorValue_FavorSperDaytimer,
			kActorValue_LeftItemCharge,
			kActorValue_AbsorbChance,
			kActorValue_Blindness,
			kActorValue_WeaponSpeedMult,
			kActorValue_ShoutRecoveryMult,
			kActorValue_BowStaggerBonus,
			kActorValue_Telekinesis,
			kActorValue_FavorPointsBonus,
			kActorValue_LastBribedIntimidated,
			kActorValue_LastFlattered,
			kActorValue_MovementNoiseMult,
			kActorValue_BypassVendorStolenCheck,
			kActorValue_BypassVendorKeywordCheck,
			kActorValue_WaitingForPlayer,
			kActorValue_OnehandedMod,
			kActorValue_TwohandedMod,
			kActorValue_MarksmanMod,
			kActorValue_BlockMod,
			kActorValue_SmithingMod,
			kActorValue_HeavyArmorMod,
			kActorValue_LightArmorMod,
			kActorValue_PickpocketMod,
			kActorValue_LockpickingMod,
			kActorValue_SneakMod,
			kActorValue_AlchemyMod,
			kActorValue_SpeechcraftMod,
			kActorValue_AlterationMod,
			kActorValue_ConjurationMod,
			kActorValue_DestructionMod,
			kActorValue_IllusionMod,
			kActorValue_RestorationMod,
			kActorValue_EnchantingMod,
			kActorValue_OnehandedSkillAdvance,
			kActorValue_TwohandedSkillAdvance,
			kActorValue_MarksmanSkillAdvance,
			kActorValue_BlockSkillAdvance,
			kActorValue_SmithingSkillAdvance,
			kActorValue_HeavyArmorSkillAdvance,
			kActorValue_LightArmorSkillAdvance,
			kActorValue_PickpocketSkillAdvance,
			kActorValue_LockpickingSkillAdvance,
			kActorValue_SneakSkillAdvance,
			kActorValue_AlchemySkillAdvance,
			kActorValue_SpeechcraftSkillAdvance,
			kActorValue_AlterationSkillAdvance,
			kActorValue_ConjurationSkillAdvance,
			kActorValue_DestructionSkillAdvance,
			kActorValue_IllusionSkillAdvance,
			kActorValue_RestorationSkillAdvance,
			kActorValue_EnchantingSkillAdvance,
			kActorValue_LeftWeaponSpeedMult,
			kActorValue_DragonSouls,
			kActorValue_CombatHealthRegenMult,
			kActorValue_OnehandedPowerMod,
			kActorValue_TwohandedPowerMod,
			kActorValue_MarksmanPowerMod,
			kActorValue_BlockPowerMod,
			kActorValue_SmithingPowerMod,
			kActorValue_HeavyarmorPowerMod,
			kActorValue_LightarmorPowerMod,
			kActorValue_PickpocketPowerMod,
			kActorValue_LockpickingPowerMod,
			kActorValue_SneakPowerMod,
			kActorValue_AlchemyPowerMod,
			kActorValue_SpeechcraftPowerMod,
			kActorValue_AlterationPowerMod,
			kActorValue_ConjurationPowerMod,
			kActorValue_DestructionPowerMod,
			kActorValue_IllusionPowerMod,
			kActorValue_RestorationPowerMod,
			kActorValue_EnchantingPowerMod,
			kActorValue_Dragonrend,
			kActorValue_AttackDamageMult,
			kActorValue_HealRateMult,
			kActorValue_MagickaRateMult,
			kActorValue_StaminaRateMult,
			kActorValue_WerewolfPerks,
			kActorValue_VampirePerks,
			kActorValue_GrabActorOffset,
			kActorValue_Grabbed,
			kActorValue_Deprecated05,
			kActorValue_ReflectDamage
		};


		virtual ~ActorValueOwner();

		virtual float	GetActorValueCurrent(ActorValue a_akValue);
		virtual float	GetActorValueMaximum(ActorValue a_akValue);
		virtual float	GetActorValueBase(ActorValue a_akValue);
		virtual void	SetActorValueBase(ActorValue a_akValue, float value);
		virtual void	ModActorValueBase(ActorValue a_akValue, float value);
		virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
		virtual void	SetActorValueCurrent(ActorValue a_akValue, float value);
		virtual bool	Unk_08(void);

		inline float	GetPlayerActorValueCurrent(ActorValue a_akValue)	{ return CALL_MEMBER_FN(this, GetPlayerActorValueCurrent)(a_akValue); }


	private:
		MEMBER_FN_PREFIX(ActorValueOwner);
		DEFINE_MEMBER_FN(GetPlayerActorValueCurrent, float, ACTOR_VALUE_OWNER_GET_PLAYER_ACTOR_VALUE_CURRENT, ActorValue a_akValue);
	};
	STATIC_ASSERT(sizeof(ActorValueOwner) == 0x8);
}
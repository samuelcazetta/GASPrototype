#include "GameplayTags/GASP_AbilityTags.h"

namespace GASPTags
{
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "GASPTags.Abilities.Attack", "Tag for Attack Gameplay Abilities");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttackContinue, "GASPTags.Abilities.AttackContinue", "Tag for Attack Continue Gameplay Abilities");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dash, "GASPTags.Abilities.Dash", "Tag for Dash Gameplay Abilities");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Special, "GASPTags.Abilities.Special", "Tag for Special Gameplay Abilities");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GASPTags.Abilities.ActivateOnGiven", "Tag for Abilities that are activated on given");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GASPTags.Abilities.HitReact", "Tag for Hit React Abilities");
		
	}
}
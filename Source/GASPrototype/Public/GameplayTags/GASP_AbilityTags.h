#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GASPTags
{
	namespace Abilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackContinue);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dash);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Special);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death);
		

		namespace Cooldown
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dash);
		}
	}
}
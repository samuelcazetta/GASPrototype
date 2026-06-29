#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GASPTags
{
	namespace Events
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN (HitReact);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN (Death);
		
		namespace Attack
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (MeleeTraceHit);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (Projectile);
			
		}
		namespace Combo
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (WindowOpen);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (WindowClose);
			
		}
		
	}
}
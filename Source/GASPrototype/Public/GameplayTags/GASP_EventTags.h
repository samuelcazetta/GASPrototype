#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GASPTags
{
	namespace Events
	{
		namespace Attack
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (MeleeTraceHit);
		}
		namespace Combo
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (WindowOpen);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN (WindowClose);
			
		}
		
	}
}
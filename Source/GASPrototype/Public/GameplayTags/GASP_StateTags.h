#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GASPTags
{
	namespace States
	{
		namespace ComboReady
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stage1);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stage2);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stage3);
			
		}

		namespace Movement
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputBlocked);
		}
	}
}

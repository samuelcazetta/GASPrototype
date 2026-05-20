#include "GameplayTags/GASP_StateTags.h"

namespace GASPTags
{
	namespace States
	{
		namespace ComboReady
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stage1, "GASPTags.States.ComboReady.Stage1", "Tag for Combo stage 1 continuation window");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stage2, "GASPTags.States.ComboReady.Stage2", "Tag for Combo stage 2 continuation window");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stage3, "GASPTags.States.ComboReady.Stage3", "Tag for Combo stage 3 continuation window");
			
		}
		
		namespace Movement
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputBlocked, "GASPTags.States.Movement.InputBlocked", "Tag for input blocked state");
		}
	}
}

#include "GameplayTags/GASP_EventTags.h"

namespace GASPTags
{
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GASPTags.Events.HitReact", "Tag for Hit React Event");
		
		namespace Attack
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit, "GASPTags.Events.Attack.MeleeTraceHit", "Tag for Melee Attack Event");
			
		}
		namespace Combo
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(WindowOpen, "GASPTags.Events.Combo.WindowOpen", "Tag for Combo Window Open Event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(WindowClose, "GASPTags.Events.Combo.WindowClose", "Tag for Combo Window Close Event");
			
		}
		
	}
}
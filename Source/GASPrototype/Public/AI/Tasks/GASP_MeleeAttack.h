#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GASP_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class GASPROTOTYPE_API UGASP_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UGASP_MeleeAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

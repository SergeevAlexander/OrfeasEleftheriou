// Fill out your copyright notice in the Description page of Project Settings.

#include "EQSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

AEQSAIController::AEQSAIController()
{
	// Components Init.
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));

	// Create a Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1500.f;
	Sight->PeripheralVisionAngleDegrees = 130.f;

	// Tell the sight sense to detect everything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	// Register the sight sense to our Perception Component
	AIPerceptionComponent->ConfigureSense(*Sight);
}

void AEQSAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (BehaviorTree)
	{
		// Initialize the Blackboard and start the attached behavior tree
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}

	// Register the OnPerceptionUpdated function to fire whenever the AIPerception get's updated
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEQSAIController::OnPerceptionUpdated);
}

AActor* AEQSAIController::GetSeeingPawn()
{
	// Return the seeing pawn
	UObject* Object = BlackboardComp->GetValueAsObject(BlackboardEnemyKey);

	return Object ? Cast<AActor>(Object) : nullptr;
}

void AEQSAIController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	// If our character exists inside the UpdatedActors array, register him
	// to our blackboard component

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor->IsA<ATP_ThirdPersonCharacter>() && !GetSeeingPawn())
		{
			BlackboardComp->SetValueAsObject(BlackboardEnemyKey, Actor);
			return;
		}
	}

	// The character doesn't exist in our updated actors - so make sure
	// to delete any previous reference of him from the blackboard
	BlackboardComp->SetValueAsObject(BlackboardEnemyKey, nullptr);
}
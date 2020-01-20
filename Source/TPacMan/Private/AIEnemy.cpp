// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemy.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "AI/NavigationSystemBase.h"
#include "RecastNavMesh.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"


void AAIEnemy::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	Bot = Cast<AEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	GameMode = Cast<ATPacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	SearchNewPoint();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(11111));

}

void AAIEnemy::SearchNewPoint()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(22222));
	UNavigationSystemV1* NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (NavMesh)
	{
		const float SearchRadius = 10000;
		FNavLocation Randompt;
		const bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, Randompt);
		if (bFound)
		{
			MoveToLocation(Randompt);
		}
	}

}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime,this,&AAIEnemy::ReArm,5.0f,false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	MoveToLocation(Bot->GetActorLocation());
	StopMovement();
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	if (!Bot->bIsDead&&GameMode->GetCurrentState() != EGameState::EPause)
	{
		SearchNewPoint();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include"TPacManGameModeBase.h"
#include "AIEnemy.generated.h"
/**
 *
 */
UCLASS()
class TPACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
public:
	void Possess(class APawn* InPawn) override;

	void SearchNewPoint();

	void GoHome();
	void ReArm();
	void StopMove();
	ATPacManGameModeBase* GameMode;

	virtual void OnMoveCompleted(FAIRequestID RequestID,const FPathFollowingResult& Result) override;
private:
	class AEnemy* Bot;
	FVector HomeLocation;
	FTimerHandle DeadTime;

};

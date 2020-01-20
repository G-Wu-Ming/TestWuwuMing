// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Enemy.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPacManGameModeBase.generated.h"

/**
 * 
 */
//Record game statu;


enum class EGameState : short
{
	EMenu,
	EPlayering,
	EPause,
	EWin,
	EGameover
};


UCLASS()
class TPACMAN_API ATPacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	EGameState CurrentState;

	EGameState GetCurrentState() ;

	void SetCurrentState(EGameState Value );

	void SetEnemyVulnerable();

	virtual void BeginPlay() override;
	//EGameState CurrentState;
private :
	EGameState currentState;
	TArray<class AEnemy*> Enemys;


}; 

  FORCEINLINE   EGameState ATPacManGameModeBase::GetCurrentState() 
	{
		return CurrentState;
	}
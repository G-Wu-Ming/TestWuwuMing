// Fill out your copyright notice in the Description page of Project Settings.

#include "TPacManGameModeBase.h"
#include "EngineUtils.h"
void ATPacManGameModeBase::SetCurrentState(EGameState Value)
{
	CurrentState = Value;
	switch (Value)
	{
	case EGameState::EMenu:
		break;
	case EGameState::EPlayering:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->SetMove(true);
		}
		break;
	case EGameState::EPause:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->SetMove(false);
		}
		break;
	case EGameState::EWin:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->Destroy();
		}
		break;
	case EGameState::EGameover:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->Destroy();
		}
		break;
	default:
		break;
	}
	
}

void ATPacManGameModeBase::SetEnemyVulnerable()
{
	for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetVulnerable();

	}
}

void ATPacManGameModeBase::BeginPlay()
{
	SetCurrentState(EGameState::EMenu);

	for ( TActorIterator<AEnemy>enemyItr(GetWorld()); enemyItr; ++enemyItr)
	{
		AEnemy* enemy = Cast<AEnemy>(*enemyItr);
		if (enemy)
		{
			Enemys.Add(enemy);
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPacManGameModeBase.h"
#include "PacManCharacter.generated.h"


UCLASS()
class TPACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		class UStaticMeshComponent* playerBody;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Bind to movement
	void MoveXAxis(float value);
	void MoveYAxis(float value);
	//Control game state
	void ReStart();
	void NewGame();
	void Pause();

	void killed();

	//FVEctor
	FVector CurrentVector;
	FVector StartPoint;
	//get gamemode
	ATPacManGameModeBase* Gamemode;
	//Set the player to hit the beans
	UFUNCTION()
	void OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	int CollectableToEat;
	int Lives;

};

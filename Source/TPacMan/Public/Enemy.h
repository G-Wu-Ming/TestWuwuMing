// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TPACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//add static mesh 
public:
	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		class UStaticMeshComponent* EnemyBody;
	UFUNCTION()
		void OnCollision(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//set Vulnerable
	void SetVulnerable();
	void SetInVulerable();
	bool bIsVulnerable;
	//set handle time
	FTimerHandle TimeVulnerable;

	void SetMove(bool MoveIt);
	void Killed();
	void ReArm();

	bool bIsDead;

private:
	class UMaterialInterface* DefaultMaterial;
	class UMaterialInterface* VulnerableMaterial;
	
};

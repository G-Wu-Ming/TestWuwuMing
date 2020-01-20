// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "collectable.generated.h"

UCLASS()
class TPACMAN_API Acollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		UStaticMeshComponent* CollectableMesh;
	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		USphereComponent* BaseCollisionComponent;
	UPROPERTY(EditAnywhere, Category = Collectable)
		bool blsSuperCollectable;
};
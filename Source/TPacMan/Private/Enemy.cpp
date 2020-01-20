// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Enemy.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "PacManCharacter.h"
#include"Public/AIEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Enemy(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Enemy.Succeeded())
	{
		EnemyBody->SetStaticMesh(Enemy.Object);
	}
	SetActorEnableCollision(true);
	//set Enemy RLocation
	EnemyBody->SetWorldScale3D(FVector(0.7, 0.7, 1));
	EnemyBody->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(20);
	
	static ConstructorHelpers::FObjectFinder<UMaterial>VulnerableMat(TEXT("Material'/Game/material/M_rad.M_rad'"));
	if (VulnerableMat.Succeeded())
	{
		VulnerableMaterial = Cast<UMaterialInterface>(VulnerableMat.Object);
	}
	AIControllerClass = AAIEnemy::StaticClass();

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
	SetInVulerable();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetVulnerable()
{
	
	GetWorldTimerManager().SetTimer(TimeVulnerable, this, &AEnemy::SetInVulerable,10,false);
	if (bIsVulnerable)
	{
		return;
	}
	bIsVulnerable = true;
	EnemyBody->SetMaterial(0, VulnerableMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemy::SetInVulerable()
{

	bIsVulnerable =  false;
	GetWorldTimerManager().ClearTimer(TimeVulnerable);
	EnemyBody->SetMaterial(0, VulnerableMaterial);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::FromInt(333));
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemy::SetMove(bool MoveIt)
{
	AAIEnemy * AI = Cast<AAIEnemy>(GetController());
	if (MoveIt)
	{
		AI->SearchNewPoint();
	}
	else
	{
		AI->StopMove();
	}
}

void AEnemy::Killed()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;
	AAIEnemy * AI = Cast<AAIEnemy>(GetController());
	AI->GoHome();
}

void AEnemy::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150;
	if (bIsVulnerable)
	{
		SetInVulerable();
	}
	SetMove(true);
}
void AEnemy::OnCollision(UPrimitiveComponent * HitComp, AActor* OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsVulnerable)
		{
			Killed();
		}
		else
		{
			APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
			PacMan->killed();
		}
	}
}

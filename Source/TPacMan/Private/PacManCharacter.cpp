// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Public/collectable.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"


// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	playerBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>player(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (player.Succeeded())
	{
		playerBody->SetStaticMesh(player.Object);
	}

	//set Enemy RLocation
	playerBody->SetWorldScale3D(FVector(0.7, 0.7, 1));
	playerBody->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(20);
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartPoint = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,StartPoint.ToString());
	Gamemode = Cast<ATPacManGameModeBase>(UGameplayStatics::GetGameMode(this));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);

	for (TActorIterator<Acollectable>collectableItr(GetWorld());collectableItr; ++collectableItr)
	{
		CollectableToEat++;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,FString::FromInt(CollectableToEat));

	Lives = 3;
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Control Walking
	PlayerInputComponent->BindAxis("MoveXAxis", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveYAxis", this, &APacManCharacter::MoveYAxis);
	//The binding key
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart);
	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction("Killed", IE_Pressed, this, &APacManCharacter::killed);
}

void APacManCharacter::MoveXAxis(float value)
{
	CurrentVector.X = value;
	AddMovementInput(CurrentVector);
}

void APacManCharacter::MoveYAxis(float value)
{
	CurrentVector.Y = value;
	AddMovementInput(CurrentVector);
}

//ReStart
void APacManCharacter::ReStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("ACollectable"));
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("ReStartLevel"));
}
//NewGame
void APacManCharacter::NewGame()
{
	if (Gamemode->GetCurrentState() == EGameState::EMenu)
	{
		Gamemode->SetCurrentState(EGameState::EPlayering);
	}
}
//Pause
void APacManCharacter::Pause()
{
	if (Gamemode->GetCurrentState()==EGameState::EPlayering)
	{
		Gamemode->SetCurrentState(EGameState::EPause);
	}
	
	else if (Gamemode->GetCurrentState() == EGameState::EPause)
	{
		Gamemode->SetCurrentState(EGameState::EPlayering);
	}
}
void APacManCharacter::killed()
{
	if (--Lives ==0)
	{
		Gamemode->SetCurrentState(EGameState::EGameover);
	}
	else
	{
		SetActorLocation(StartPoint);
	}
}
void APacManCharacter::OnCollision(UPrimitiveComponent * HitComp, AActor* OtherActor, UPrimitiveComponent * OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (Gamemode->GetCurrentState() == EGameState::EPlayering)
	{
		if (OtherActor->IsA(Acollectable::StaticClass()))
		{
			//cast collectable
			Acollectable* collectable = Cast<Acollectable>(OtherActor);
			if (collectable->blsSuperCollectable)
			{
				Gamemode->SetEnemyVulnerable();
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Collision complete, beans disappear !"));
			OtherActor->Destroy();
			if (--CollectableToEat == 0)
			{
				Gamemode->SetCurrentState(EGameState::EWin);
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(CollectableToEat));
		}
	}
}


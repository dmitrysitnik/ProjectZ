// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceShip.h"
#include "ProjectZPawn.h"
#include "ProjectZProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "ProjectZGameMode.h"
#include "Engine/World.h"




const FName ASpaceShip::MoveForwardBinding("MoveForward");
const FName ASpaceShip::MoveRightBinding("MoveRight");
const FName ASpaceShip::FireForwardBinding("FireForward");
const FName ASpaceShip::FireRightBinding("FireRight");



// Sets default values
ASpaceShip::ASpaceShip()
{
 //	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
    
    
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetupAttachment(ShipMeshComponent);
    
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level


	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 100.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
    bCanRestart = false;
    bIsDead = false;
}


void ASpaceShip::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::FireShot);
    PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &ASpaceShip::Restart);
}


void ASpaceShip::Tick(float DeltaSeconds)
{
    
    if(bIsDead) return;
    
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = GetActorRotation();
		//const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// Create fire direction vector
	/*const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
*/
}

void ASpaceShip::FireShot()
{
	
	// If it's ok to fire again
	if (bCanFire == true)
	{

		const FRotator FireRotation = GetActorRotation();
			 //Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + GunOffset;

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				 //spawn the projectile
				World->SpawnActor<AProjectZProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ASpaceShip::ShotTimerExpired, FireRate);

			 //try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
	}
}


//the Function invokes on the timer expired
void ASpaceShip::ShotTimerExpired()
{
	bCanFire = true;
}


void ASpaceShip::Restart(){
    
    AProjectZGameMode* gameMode = (AProjectZGameMode*)GetWorld()->GetAuthGameMode();
    UE_LOG(LogTemp, Warning, TEXT("Restart"));
    
    
    if(gameMode && bCanRestart){
        bCanRestart = false;
        gameMode->RestartLevel(GetWorld(), "main");
    }
    
}



void ASpaceShip::Death(){
    
    //Set the flags of a player state
    //Now can restart and cannot fire
    bCanRestart  = true;
    bIsDead = true;
    bCanFire = false;
    
    
    //Hide the actor on a level
    SetActorHiddenInGame(true);
    
}

//Temp implematation
//void ASpaceShip::SetupUI(){
// 
//    if(wUI){
//        APlayerController* PC = GetWorld()->GetFirstPlayerController();
//        pUI = CreateWidget<UUserWidget>(PC, wUI);
//        
//        if(pUI){
//            pUI->AddToViewport();
//        }
//        
//    }
//    
//}




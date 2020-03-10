// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

UCLASS(Blueprintable)
class PROJECTZ_API ASpaceShip : public APawn
{
	GENERATED_BODY()

    /* The mesh component */
    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComponent;
    
    /** The sphere component */
    UPROPERTY(Category = Spawning, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    class USphereComponent* SphereComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

public:
	ASpaceShip();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;
    
    
    UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
    class USoundBase* mExplosion;
    
    
    UPROPERTY(Category = UI, EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class UUserWidget> AfterDeathWidget;
    
    

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	/* Fire a shot in the specified direction */
	void FireShot();
    
    /* Player death function */
    void Death();
    
    
    /* Set new state for the invulnerable flag **/
    UFUNCTION(BlueprintCallable)
    void SetInvulnerable(bool bInvulnerable, float invulnerableSeconds = 0.0f);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();
    
    
    /* Disable the invulnerable flag**/
    void SetInvulnerableFalse();
    
    
    
    
    /* Method to set slowdown */
    void SetSlowdown(float newSpeed, float slowDownTime);
    
    /* Const for ussual speed of a space ship **/
    const float spaceShipSpeed = 700.0f;
    
    
    UFUNCTION(BlueprintCallable)
    void SetSpaceshipMoveSpeed(float newMoveSpeed = 700.0f);
    
    UFUNCTION(BlueprintCallable)
    void SetSpaceShipMovespeedToDefault();

	//// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;
    
    /** Flag to control spawn ability */
    bool bCanRestart;
    
    /* Flag to control state of player live**/
    bool bIsDead;
    
    /* Flag to control */
    bool bIsGod;
    
    /** Logic bounded with a level restart*/
    void Restart();
    
    /** Add HUD after player has dead */
    void AddAfterDeathHUD();
    
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;
    
    /* Handle invulnerable flag **/
    FTimerHandle TimerHandle_ShieldExpired;
    
    /** Handle slowdown  */
    FTimerHandle TimerHandle_Slowdown;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    
    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool IsDead() const { return bIsDead; }
};

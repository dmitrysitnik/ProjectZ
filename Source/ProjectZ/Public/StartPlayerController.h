// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
    
    
    public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
    TSubclassOf<class UUserWidget> wGameUI;

    // Variable to hold the widget After Creating it.
    UUserWidget* GameUI;
    
    
    void BeginPlay() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AProjectZPlayerController : public APlayerController
{
	GENERATED_BODY()
    
    
public:
    virtual void BeginPlay() override;
    
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
//    TSubclassOf<class UUserWidget> wUI;
//    
//    UUserWidget* pUI;
    
    
protected:
    void SetupUI();
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"
#include "Blueprint/UserWidget.h"


void AStartPlayerController::BeginPlay(){
    if (wGameUI) // Check if the Asset is assigned in the blueprint.
    {
        // Create the widget and store it.
        GameUI = CreateWidget<UUserWidget>(this, wGameUI);

        // now you can use the widget directly since you have a referance for it.
        // Extra check to  make sure the pointer holds the widget.
        if (GameUI)
        {
            //let add it to the view port
            GameUI->AddToViewport();
        }

        //Show the Cursor.
        bShowMouseCursor = true;
    }
}

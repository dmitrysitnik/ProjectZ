// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AsteroidEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"


AAsteroidEnemy::AAsteroidEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));

	smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = smEnemy;
	smEnemy->SetStaticMesh(Mesh.Object);

}

void AAsteroidEnemy::Tick(float deltaSeconds) {

	Super::Tick(deltaSeconds);

	/**«адать направление движени€ дл€ противников */
	FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * deltaSeconds * 600;
	SetActorLocation(newLocation);
}
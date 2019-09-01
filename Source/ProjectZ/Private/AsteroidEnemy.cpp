// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AsteroidEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "SpaceShip.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"


AAsteroidEnemy::AAsteroidEnemy() {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Geometry/Meshes/SM_Rock.SM_Rock"));

	smEnemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = smEnemy;
	smEnemy->SetStaticMesh(Mesh.Object);
	smEnemy->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidEnemy::OnBeginOverlap);
	smEnemy->OnComponentHit.AddDynamic(this, &AAsteroidEnemy::OnHit);

}

void AAsteroidEnemy::Tick(float deltaSeconds) {

	Super::Tick(deltaSeconds);

	/**«адать направление движени€ дл€ противников */
	FVector newLocation = GetActorLocation() + GetActorForwardVector()* -1 * deltaSeconds * 600;
	SetActorLocation(newLocation);
}


void AAsteroidEnemy::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult){



}


void AAsteroidEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{


	if (OtherActor)
	{
		ASpaceShip* spaceShip = Cast<ASpaceShip>(OtherActor);
		if (spaceShip)
		{
			spaceShip->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Destroy"));
		}
	}

}
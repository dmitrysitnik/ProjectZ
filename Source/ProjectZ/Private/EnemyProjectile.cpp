// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "SpaceShip.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectZProjectile.h"

AEnemyProjectile::AEnemyProjectile(): AProjectZProjectile::AProjectZProjectile(){
    ProjectileMovement->InitialSpeed = 1500.0f;
}


void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
    /** Enemy's projectile behavior - destroy player*/
    if (OtherActor)
    {   
        
        ASpaceShip* player = Cast<ASpaceShip>(OtherActor);

        if (player)
        {
            player->Destroy();
        }
        
    }

}

void AEnemyProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
        if (OtherActor)
        {
            ASpaceShip* player = Cast<ASpaceShip>(OtherActor);

            if (player) {
                player->Death();
                Destroy();
            }
        }
        

}


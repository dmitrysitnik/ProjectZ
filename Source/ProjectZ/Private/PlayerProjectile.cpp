// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "EnemyBase.h"


void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
    
UE_LOG(LogTemp, Warning, TEXT("The Projectile hitted something"));

    /** player's projectile behavior - destroy enemies*/
    if (OtherActor)
    {
        AEnemyBase* enemy = Cast<AEnemyBase>(OtherActor);
        
        if (enemy)
        {
            enemy->InputDamage(Damage);
            Destroy();
        }
    }

    
}



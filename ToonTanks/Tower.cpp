// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h" 

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

     if(InFireRange()) 
    {
        //rotates turret towards tank
        RotateTurret(Tank->GetActorLocation());
    }
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    //access to world timer manager
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction() 
{
    //renders effects from basepawn and destroys twer
    Super::HandleDestruction();
    Destroy();
}

//tower timer to fire at tank
void  ATower::CheckFireCondition() 
{
    if(Tank == nullptr) {
        return;
    }
    
    if(InFireRange() && Tank->bAlive) 
    {
        //fires if in range of turrets
        Fire();
    }
}

bool ATower::InFireRange()
{
 if(Tank) 
    {
        //find distance to tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        //sees if tank is in range
        if(Distance <= FireRange) 
        {
            return true;
        }
    }

    return false;
}
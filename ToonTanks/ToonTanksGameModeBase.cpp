// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h" 
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameModeBase::ActorDied(AActor *DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if(ToonTanksPlayerController)
        {
           ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    } 
    else if( ATower* DestroyedTower = Cast<ATower>(DeadActor) )
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers == 0 )
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
    
}

void AToonTanksGameModeBase::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();

    //controller
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));   

    StartGame();

    //disable tank before timer runs out
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );
    }
}

//counts the towers for win/lose functionality
int32 AToonTanksGameModeBase::GetTargetTowerCount() 
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	//allows us to add functionality in blueprints instead of code
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	//allows us to add win/lose functionality in blueprints instead of code
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
public:
	void ActorDied(AActor* DeadActor);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	//we wait 3 seconds before we start the game
	float StartDelay = 3.f;
	void HandleGameStart();

	//counts towers
	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();
};

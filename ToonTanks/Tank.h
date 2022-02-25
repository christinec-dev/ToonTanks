// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController;}

	bool bAlive = true;

private:
	//will create spring arm component for pawn & make visible to blueprints
	UPROPERTY(VisibleAnywhere, Category = "Private Components")	
	class USpringArmComponent* SpringArmComp;

	//will create camera for pawn & make visible to blueprints
	UPROPERTY(VisibleAnywhere, Category = "Private Components")
	class UCameraComponent* CameraComp;

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;
	
	APlayerController* TankPlayerController;

};

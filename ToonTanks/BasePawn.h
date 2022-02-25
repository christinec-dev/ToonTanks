// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//handles destruction of particular pawn
	void HandleDestruction();

protected: 

	//rotate the turret
	void RotateTurret(FVector LookAtTarget);

	//fire actions
	void Fire();

private:

	//we use forward declaration to reduce file bloating and compilation time & make visible to blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Private Components", meta = (AllowPrivateAccess = "true"))	
	class UCapsuleComponent* CapsuleComp;

	//will create meshes for the base and turret of our pawn & make visible to blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Private Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Private Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	//will create spawn point of our pawn & make visible to blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Private Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//allows us to set blueprint objects (projectile) type
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	//death particle
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	//death sound	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	//camera shake
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShake> DeathCameraShakeClass;
};

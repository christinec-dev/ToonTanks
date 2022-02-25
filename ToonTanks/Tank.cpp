// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h" 
#include "Components/InputComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "Tank.h"

ATank::ATank() 
{
    //connects spring arm to tank
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

    //connects camera to spring arm
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController) 
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false , 
            HitResult
        );
        
        //for each frame we rotate turret towards hit point/target
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction() 
{
    //renders effects from basepawn and hides tank
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    //
    //casting changes the pointer type to another type
	TankPlayerController = Cast<APlayerController>(GetController());

}

//handles player input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //bind move forward axis mapping to move function
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    //bind move forward axis mapping to turn function
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    //bind fire action mapping to fire function
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

//tank move function
void ATank::Move(float Value)
{
    //W = 1, S = -1, SW = 0
	FVector DeltaLocation = FVector::ZeroVector;
    //Allow us to change the actor position when key press
    //X = Value * DeltaTime ( time difference between the previous frame that was drawn and the current frame) * Speed
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}


//tank turning function
void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
    //Allow us to change the actor position when key press
    //Yaw = Value * DeltaTime ( time difference between the previous frame that was drawn and the current frame) * TurnRate
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

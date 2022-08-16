// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComp->SetupAttachment(SpringComp);

    AmmoAmount = 8;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction(TEXT("Shift Speed"), IE_Pressed, this, &ATank::SpeedShift);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
 

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {     
        FHitResult HitResult;                                                              
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,//Line Trace channel
            false,
            HitResult
        );

        RotateTurrent(HitResult.ImpactPoint);
    }

    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("Ammo Amount: %i"), AmmoAmount));
    }

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    //Have to use casting Acontroller to APlayerController Cast<>()
    TankPlayerController = Cast<APlayerController>(GetController());

    
	
}

void ATank::Move(float Value)
{
    FVector DeltaLocation(0.f);
    
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    DeltaLocation.X = Value * DeltaTime * Speed;
   // UE_LOG(LogTemp, Display, TEXT("DeltaLocation: %f"), DeltaLocation);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    //Yaw = Value * DeltaTime * TurnRate

    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = Value * DeltaTime * TurnRate;
    AddActorLocalRotation(DeltaRotation, true);

}

void ATank::SpeedShift()
{
    Speed = Speed * 100;
}

void ATank::SetAmmoAmount(int ammo)
{
    AmmoAmount = ammo;
}

int ATank::GetAmmoAmount()
{
    return AmmoAmount;
}

void ATank::AddAmmo()
{
    AmmoAmount++;
}


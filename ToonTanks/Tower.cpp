// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find the distance to the tank
   
     if(InFireRange())
     {
        // If in range, rotate turrent
        RotateTurrent(Tank->GetActorLocation());
     }       
    
      

}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    //Set to be called every 2 seconds
    GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }

    if(InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

bool ATower::InFireRange()
{
    bool InFireRange = false;
    
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        //Check to see if tank in range
        if(Distance <= FireRange)
        {
            InFireRange =  true;
        }
    }

    return InFireRange;
}
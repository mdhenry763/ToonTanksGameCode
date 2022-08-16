// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "CProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//We are constructing the tank with child objects 
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh-> SetupAttachment(CapsuleComp);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);

}

void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurrentMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurrentMesh-> SetWorldRotation(LookAtRotation);

	
}

void ABasePawn::Fire()
{

	FVector SpawnPointLoc = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnPointRot = ProjectileSpawnPoint->GetComponentRotation();

	ACProjectile* Projectile = GetWorld()->SpawnActor<ACProjectile>(ProjectileClass, SpawnPointLoc,SpawnPointRot);
	Projectile->SetOwner(this);//When it spawns it sets the owner
}

void ABasePawn::HandleDestruction()
{
	FVector SpawnPointLoc = CapsuleComp->GetComponentLocation();
	FRotator SpawnPointRot = CapsuleComp->GetComponentRotation();

	if(DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, SpawnPointLoc, SpawnPointRot);
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}





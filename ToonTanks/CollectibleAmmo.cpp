// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleAmmo.h"
#include "Tank.h"

// Sets default values
ACollectibleAmmo::ACollectibleAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Comp"));
	SphereComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACollectibleAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectibleAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime, 0, 0));

}

void ACollectibleAmmo::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	Destroy();

	ATank* Tank = Cast<ATank>(OtherActor);

	if(Tank)
	{
		Tank->AddAmmo();
		Destroy();
	}
}

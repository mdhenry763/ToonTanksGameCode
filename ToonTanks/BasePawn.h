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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ammunition = 10;

	void HandleDestruction();

protected:
	void RotateTurrent(FVector LookAtTarget);

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components",BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;//Forward Declaration(not a member)

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurrentMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//Template, requires a type parameter, Stores a UClass, Subclass of the chosen type, even blueprints based on type
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ACProjectile> ProjectileClass;//c++ variable of class type based on aProjectile

	//We need the Tsubclass because of Spawn Actors
	//SpawnActor<AProjectile>(ProjectileClass, Fvector, Loc, Rot)
	UPROPERTY(EditDefaultsOnly, Category= "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};

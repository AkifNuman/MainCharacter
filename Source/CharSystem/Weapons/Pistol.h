// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SkeletalMesh.h"
#include "D:\Unreal Projects\CharSystem\Source\CharSystem\MainCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Pistol.generated.h"

UCLASS()
class CHARSYSTEM_API APistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PistolMesh;

};

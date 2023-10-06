// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class CHARSYSTEM_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasPistol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCrouching;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	void CharCrouch(float Value);

	void Run(float Value);
};

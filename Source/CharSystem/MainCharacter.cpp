
#include "MainCharacter.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mannequin(TEXT("/Game/MainCharacter/MannequinMesh/Mesh/SK_Mannequin"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("/Game/MainCharacter/Animations/MainCharacterAnimBP"));
	GetMesh()->SetSkeletalMesh(Mannequin.Object);
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GeneratedClass);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	GetCapsuleComponent()->SetVisibility(true);
	GetCapsuleComponent()->bHiddenInGame = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("'SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 21.12540f));
	SpringArm->SetRelativeRotation(FRotator(-8.385537f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	GetCharacterMovement()->MaxWalkSpeed = 225.f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}




// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Run", this, &AMainCharacter::Run);
	PlayerInputComponent->BindAxis("Crouch", this, &AMainCharacter::CharCrouch);
}

void AMainCharacter::MoveForward(float Value)
{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		if ((Value != NULL) && (Value > 0))
		{
			bIsWalking = true;
		}
		else
		{
			bIsWalking = false;
		}
}

void AMainCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::CharCrouch(float Value)
{
	if ((Value))
	{
		Crouch();
		bCrouching = true;
	}
	else
	{
		UnCrouch();
		bCrouching = false;
	}
}

void AMainCharacter::Run(float Value)
{
	if ((Value != NULL) && (Value > 0))
	{
		GetCharacterMovement()->MaxWalkSpeed = 550.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 225.f;
	}

}
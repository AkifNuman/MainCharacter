// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
APistol::APistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PistolMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	PistolMesh->SetupAttachment(RootComponent);
	PistolMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MyMesh(TEXT("/Game/MilitaryWeapSilver/Weapons/Pistols_A"));
	PistolMesh->SetSkeletalMesh(MyMesh.Object);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(PistolMesh);
	SphereCollision->SetSphereRadius(39.f);
	SphereCollision->SetRelativeLocation(FVector(0.f, 7.09f, 0.f));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APistol::OnSphereOverlap);


	Tags.Add(TEXT("Pistol"));
}

// Called when the game starts or when spawned
void APistol::BeginPlay()
{
	Super::BeginPlay();
	
}

void APistol::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MyCarRef = Cast<AMainCharacter>(OtherActor);
	if (MyCarRef)
	{
		MyCarRef->bHasPistol = true;
	}
	Destroy();
}

// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




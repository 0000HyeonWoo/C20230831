// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetBoxExtent(FVector(22.f, 5.f, 5.f));

	//Overlap Event bool
	Box->SetGenerateOverlapEvents(true);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	Body->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	ProjectileMovement->InitialSpeed = 1200.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	//함수의 주소라서 & 붙이기
	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
	//OnActorBeginOverlap.RemoveDynamic(this, &AMyActor::ProcessBeginOverlap);
	//OnActorBeginOverlap.RemoveAll(this);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogClass, Warning, TEXT("ProcessBeginOverlap"));
	CallBlueprintFunctionOrCPP();
	//CallBlueprintFunctionJustBP();
}

void AMyActor::CallBlueprintFunctionOrCPP_Implementation()
{
	UE_LOG(LogClass, Warning, TEXT("Execute CPP"));

}


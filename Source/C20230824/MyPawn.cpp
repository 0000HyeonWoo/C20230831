// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Box Collision, Set RootComponent
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	//StaticMesh, Attach to RootComponent
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	RightPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightPropeller"));
	RightPropeller->SetupAttachment(Body);

	LeftPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftPropeller"));
	LeftPropeller->SetupAttachment(Body);

	//Set Propeller's Location(Relative)
	RightPropeller->SetRelativeLocation(FVector(37.284207f, 20.894921f, 0.589304f));
	LeftPropeller->SetRelativeLocation(FVector(37.284207f, -20.894921f, 0.589304f));

	//Camera, Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Arrow
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);


	//Components
	floatingMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("floatingMovementComponent"));

}


// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//floating Actor Direction to Actor's Forward
	AddMovementInput(GetActorForwardVector(), BoostValue);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Check EnhancedInputComponent
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::Boost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::UnBoost);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AMyPawn::PitchAndRoll);
	}
}

void AMyPawn::Boost(const FInputActionValue& Value)
{
	BoostValue = 1.0f;
}

void AMyPawn::UnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5f;
}

void AMyPawn::Fire(const FInputActionValue& Value)
{
}

void AMyPawn::PitchAndRoll(const FInputActionValue& Value)
{
	FVector2D Input2DVector = Value.Get<FVector2D>();

	float Pitch;
	float Roll;

	Pitch = Input2DVector.X * UGameplayStatics::GetWorldDeltaSeconds(GetController()->GetWorld()) * 60.f;

	Roll = Input2DVector.Y * UGameplayStatics::GetWorldDeltaSeconds(GetController()->GetWorld()) * 60.f;

	FRotator PitchRotator;
	PitchRotator = { Pitch, 0.f, 0.f };

	FRotator RollRotator;
	RollRotator = { 0.f, Roll, 0.f };

	AddActorLocalRotation(PitchRotator);
	AddActorLocalRotation(RollRotator);

}


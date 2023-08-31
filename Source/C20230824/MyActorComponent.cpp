

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//Set RotateAxis
	RotateAxis = { 0.f, 0.f, 1.f };

	//Set Rotation Speed
	RotationSpeed = 3200.f;
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Add Rotation to Scenecomponent in Array
	for (int32 index = 0; index < SceneArray.Num(); ++index)
	{
		SceneArray[index]->AddLocalRotation(RotateAxis * RotationSpeed * DeltaTime, false);
	}
}

void UMyActorComponent::AddSceneComponent(USceneComponent* TargetComponent)
{
	if (TargetComponent)
	{
		//Add Target Component to Array
		SceneArray.Add(TargetComponent);
	}
}


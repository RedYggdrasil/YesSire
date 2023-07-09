// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/GameplayFramework/YSPawn.h"

// Sets default values
AYSPawn::AYSPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYSPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


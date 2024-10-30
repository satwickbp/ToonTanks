// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) {
		//if in the range , rotate turret toward tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay() {
	Super::BeginPlay();

	Tank =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr) {
		return;
	}
	if (InFireRange() && Tank->bAlive) 
	{
		Fire();
	}
}

bool ATower::InFireRange() {
	//Find distence to the tank
	if (Tank) {
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		//check to see if the tank is in range
		if (Distance <= FireRange) {
			return true;
		}
	}
	return false;
}
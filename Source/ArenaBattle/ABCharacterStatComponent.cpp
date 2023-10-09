// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacterStatComponent.h"
#include "ABGameInstance.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UABCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CurrentStatData = ABGameInstance->GetABCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
	}
}

void UABCharacterStatComponent::SetDamage(float NewDamage)
{
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	if (CurrentHP <= 0.0f)
		OnHPIsZero.Broadcast();
}

float UABCharacterStatComponent::GetAttack()
{
	return CurrentStatData->Attack;
}

// Copyright Danny Kay 2021.


#include "Pawns/GSCCharacter.h"
#include "Abilities/GSCAbilitySystemComponent.h"
#include "Abilities/GSCAttributeSet.h"

// Sets default values
AGSCCharacter::AGSCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGSCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UGSCAttributeSet>(TEXT("AttributeSet"));
}

void AGSCCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->GiveStartingAbilities();
	AbilitySystemComponent->GiveDefaultAttribute();
}

UAbilitySystemComponent* AGSCCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGSCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGSCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGSCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AGSCCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float AGSCCharacter::GetHealth() const
{
	return IsValid(AttributeSet) ? AttributeSet->GetHealth() : 0.0f;
}

float AGSCCharacter::GetMaxHealth() const
{
	return IsValid(AttributeSet) ? AttributeSet->GetMaxHealth() : 0.0f;
}

float AGSCCharacter::GetArmor() const
{
	return IsValid(AttributeSet) ? AttributeSet->GetArmor() : 0.0f;
}

float AGSCCharacter::GetMaxArmor() const
{
	return IsValid(AttributeSet) ? AttributeSet->GetMaxArmor() : 0.0f;
}


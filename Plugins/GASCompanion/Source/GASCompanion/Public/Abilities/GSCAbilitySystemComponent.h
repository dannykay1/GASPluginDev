// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GSCAbilitySystemComponent.generated.h"

class UGameplayAbility;

/**
 * 
 */
UCLASS()
class GASCOMPANION_API UGSCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** Constructor to set default values */
	UGSCAbilitySystemComponent();

	void GiveStartingAbilities();
	void GiveDefaultAttribute();

protected:
	/** Starting abilities */
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	/** Default attributes for a character for initializing on spawn/respawn. */
	TSubclassOf<UGameplayEffect> DefaultAttribute;
};
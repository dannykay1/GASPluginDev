// Copyright Danny Kay 2021.


#include "Abilities/GSCAbilitySystemComponent.h"


UGSCAbilitySystemComponent::UGSCAbilitySystemComponent()
{
}

void UGSCAbilitySystemComponent::GiveStartingAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : StartingAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability));
	}
}

void UGSCAbilitySystemComponent::GiveDefaultAttribute()
{
	FGameplayAbilitySpecHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(GetOwner());

	const FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(DefaultAttribute, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToSelf(*NewHandle.Get());
	}
}


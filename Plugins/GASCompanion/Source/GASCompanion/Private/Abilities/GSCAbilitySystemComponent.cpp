// Copyright Danny Kay 2021.


#include "Abilities/GSCAbilitySystemComponent.h"


UGSCAbilitySystemComponent::UGSCAbilitySystemComponent()
{
}

void UGSCAbilitySystemComponent::GiveStartingAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : StartingAbilities)
	{
		if (Ability)
		{
			GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, GetOwner()));			
		}
	}
}

void UGSCAbilitySystemComponent::GiveDefaultAttribute()
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(GetOwner());

	const FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(StartingAttribute, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}


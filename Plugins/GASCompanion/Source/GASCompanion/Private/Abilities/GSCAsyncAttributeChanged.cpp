// Copyright Danny Kay 2021.


#include "Abilities/GSCAsyncAttributeChanged.h"

UGSCAsyncAttributeChanged* UGSCAsyncAttributeChanged::ListenForAttributeChange(class UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UGSCAsyncAttributeChanged* WaitForAttributeChangedTask = NewObject<UGSCAsyncAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Something went wrong!"));
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UGSCAsyncAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}


UGSCAsyncAttributeChanged* UGSCAsyncAttributeChanged::ListenForAttributesChange(class UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UGSCAsyncAttributeChanged* WaitForAttributeChangedTask = NewObject<UGSCAsyncAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UGSCAsyncAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}


void UGSCAsyncAttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}


void UGSCAsyncAttributeChanged::AttributeChanged(const FOnAttributeChangeData& Data) const
{
	UE_LOG(LogTemp, Warning, TEXT("Attribute was changed!"));
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}

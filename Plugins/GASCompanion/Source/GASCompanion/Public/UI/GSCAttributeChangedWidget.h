// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GSCAttributeChangedWidget.generated.h"

/** Base class widget responsible for updating any UI listening for attribute changes. */
UCLASS()
class GASCOMPANION_API UGSCAttributeChangedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Called to update any UI elements on this widget. */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeWidget(class UAbilitySystemComponent* ASC, FGameplayAttribute Current, FGameplayAttribute Max);
};

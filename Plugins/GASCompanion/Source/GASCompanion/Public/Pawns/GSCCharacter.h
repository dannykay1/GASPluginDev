// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GSCCharacter.generated.h"

class UGSCAbilitySystemComponent;

/**
 * Base class for any character that needs to implement the Gameplay Ability System.
 */
UCLASS()
class GASCOMPANION_API AGSCCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGSCCharacter();

	/** Initialize AbilitySystemComponent */
	virtual void PossessedBy(AController* NewController) override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UGSCAbilitySystemComponent* AbilitySystemComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

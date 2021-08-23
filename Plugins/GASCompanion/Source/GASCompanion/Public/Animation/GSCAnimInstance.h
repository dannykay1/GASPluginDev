// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "GSCAnimInstance.generated.h"

class AGSCCharacter;
class UGSCAbilitySystemComponent;

/**
 * Animation instance class to handle character with abilities.
 */
UCLASS()
class GASCOMPANION_API UGSCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/* Sets all default values. */
	UGSCAnimInstance();

	/* Performs initialization. */
	virtual void NativeInitializeAnimation() override;

	/* Checks references and calls UpdateAnimation */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/** Updates the animation every frame. */
	virtual void UpdateAnimation(float DeltaSeconds);

protected:
	/* The owner of the animation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	AGSCCharacter* CharacterOwner;

	/* The ability system component on the owner of this anim instance. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	UGSCAbilitySystemComponent* ASC;

	/** Tag used to determine if owner is sprinting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FGameplayTag SprintingTag;

	/** Tag used to determine if owner is targeting.  Can be ADS-ing or targeting another entity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FGameplayTag TargetingTag;

	/* Is character moving? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsMoving : 1;

	/* Is character sprinting? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsSprinting : 1;

	/* Is the CharacterOwner targeting? This can be ADS-ing or focusing on a target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsTargeting : 1;

	/* Is character falling? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsFalling : 1;

	/* Is character dead? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsDead : 1;

	/* Is character crouching?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsCrouching : 1;

	/* Pitch of character.  Used for aim offsets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Pitch;

	/* Speed of the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Speed;

	/* Direction based on character velocity and rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Direction;
};

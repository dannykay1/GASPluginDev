// Copyright Danny Kay 2021.


#include "Animation/GSCAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "Pawns/GSCCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GSCAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UGSCAnimInstance::UGSCAnimInstance()
{
	bIsMoving = false;
	bIsSprinting = false;
	bIsTargeting = false;
	bIsFalling = false;
	bIsDead = false;
	bIsCrouching = false;
}

void UGSCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterOwner = Cast<AGSCCharacter>(TryGetPawnOwner());
	ASC = Cast<UGSCAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TryGetPawnOwner()));
}

void UGSCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterOwner || !ASC) return;

	UpdateAnimation(DeltaSeconds);
}

void UGSCAnimInstance::UpdateAnimation(float DeltaSeconds)
{
	// Get velocity and zero out z.  Only want the lateral vector.
	FVector Velocity = CharacterOwner->GetVelocity();
	Velocity.Z = 0.0f;

	Speed = Velocity.Size();

	bIsMoving = Speed > 0;
	bIsSprinting = ASC->HasMatchingGameplayTag(SprintingTag);
	bIsTargeting = ASC->HasMatchingGameplayTag(TargetingTag);

	if (CharacterOwner->GetCharacterMovement())
	{
		bIsFalling = CharacterOwner->GetCharacterMovement()->IsFalling();
		bIsCrouching = CharacterOwner->GetCharacterMovement()->IsCrouching();
	}

	Direction = CalculateDirection(Velocity, CharacterOwner->GetActorRotation());

	FRotator ControlRotation = CharacterOwner->GetControlRotation();
	FRotator ActorRotation = CharacterOwner->GetActorRotation();

	FRotator CurrentRotation = FRotator(Pitch, 0.0f, 0.0f);
	FRotator TargetRotation = UKismetMathLibrary::ComposeRotators(ControlRotation, ActorRotation);

	FRotator FinalRotator = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 15.0f);
	Pitch = UKismetMathLibrary::ClampAngle(FinalRotator.Pitch, -90.0f, 90.0f);
}

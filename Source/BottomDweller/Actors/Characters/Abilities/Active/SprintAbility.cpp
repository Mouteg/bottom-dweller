﻿// All rights reserved by Aboba Inc.


#include "SprintAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/PawnMovementComponentProvider.h"
#include "GameFramework/CharacterMovementComponent.h"

USprintAbility::USprintAbility() {
	SprintSpeed = 600;
}

void USprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetBottomDwellerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

bool USprintAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                        FGameplayTagContainer* OptionalRelevantTags) const {
	if (!ActorInfo->AvatarActor.Get()->Implements<UPawnMovementComponentProvider>()) {
		return false;
	}
	const UPawnMovementComponent* MovementComponent = IPawnMovementComponentProvider::Execute_GetPawnMovementComponent(ActorInfo->AvatarActor.Get());
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)
		&& !MovementComponent->IsFalling()
		&& MovementComponent->IsMovingOnGround()
		&& !MovementComponent->GetLastInputVector().IsZero();
}

void USprintAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) {
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	IPawnMovementComponentProvider::Execute_GetPawnMovementComponent(ActorInfo->AvatarActor.Get())->MaxWalkSpeed
		= GetBottomDwellerCharacterFromActorInfo()->WalkSpeed;
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

void USprintAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo) {
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	CancelAbility(Handle, ActorInfo, ActivationInfo, false);
}

void USprintAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) {
	Super::OnGiveAbility(ActorInfo, Spec);
	if (SprintPeriodicCostEffect) {
		CostEffectHandle = GetAbilitySystemComponentFromActorInfo(ActorInfo)->ApplyGameplayEffectToSelf(
			SprintPeriodicCostEffect->GetDefaultObject<UGameplayEffect>(),
			1,
			MakeEffectContext(Spec.Handle, ActorInfo)
		);
	}
}

void USprintAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) {
	Super::OnRemoveAbility(ActorInfo, Spec);
	if (CostEffectHandle.IsValid()) {
		GetAbilitySystemComponentFromActorInfo(ActorInfo)->RemoveActiveGameplayEffect(CostEffectHandle);
	}
}

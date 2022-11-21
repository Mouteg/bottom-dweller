// All rights reserved by Aboba Inc.


#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bAbilitiesInitialized = false;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("Attributes"));
}

float ABaseCharacter::GetHealth()
{
	if (AttributeSet)
	{
		return AttributeSet->GetHealth();
	}
	return 1.f;
}

float ABaseCharacter::GetMaxHealth()
{
	if (AttributeSet)
	{
		return AttributeSet->GetMaxHealth();
	}
	return 1.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::HandleDamage(const float Damage, const FHitResult& HitResult, const FGameplayTagContainer& DamageTags, ABaseCharacter* CharacterInstigator,
                                  AActor* DamageCauser)
{
	OnDamaged(Damage, HitResult, DamageTags, CharacterInstigator, DamageCauser);
}

void ABaseCharacter::HandleHealthChange(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChange(DeltaValue, EventTags);
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (InputComponent && AbilitySystemComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"Confirm",
			"Cancel",
			FTopLevelAssetPath("/Script/BottomDweller", "EInputAbilityId"),
			static_cast<int32>(EInputAbilityId::Confirm),
			static_cast<int32>(EInputAbilityId::Cancel)
		);
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
		AddInitialGameplayAbilities();
	}
}

void ABaseCharacter::AddInitialGameplayAbilities()
{
	if (AbilitySystemComponent && !bAbilitiesInitialized)
	{
		for (TSubclassOf<UBaseGameplayAbility>& Ability : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				Ability,
				1,
				static_cast<int32>(Ability.GetDefaultObject()->AbilityInputId),
				this
			));
		}

		for (const TSubclassOf<UGameplayEffect>& Effect : GameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle EffectHandle = AbilitySystemComponent->MakeOutgoingSpec(
				Effect, 1, EffectContext
			);

			if (EffectHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*EffectHandle.Data.Get(),
					AbilitySystemComponent
				);
			}
		}
		bAbilitiesInitialized = true;
	}
}

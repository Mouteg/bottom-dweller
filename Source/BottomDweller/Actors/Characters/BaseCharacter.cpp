// All rights reserved by Aboba Inc.


#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

float ABaseCharacter::Heal(float HealAmount)
{
	Health = FMath::Min(Health + HealAmount, MaxHealth);
	return Health;
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float const ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (ActualDamage != 0)
	{
		Health -= ActualDamage;
		if (Health <= 0)
			Destroy();
	}
	return ActualDamage;
}


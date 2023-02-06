#include "BottomDwellerCharacter.h"

#include "PlayerAttributeSet.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Components/InteractionComponent.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Actors/Components/WeaponComponent.h"
#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

ABottomDwellerCharacter::ABottomDwellerCharacter()
{
	InitActorComponents();
}

void ABottomDwellerCharacter::InitActorComponents()
{
	Sensitivity = 0.65;
	AttackSensitivityMultiplier = 0.2;
	WalkSpeed = 350;
	AttackWalkSpeed = 250;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = 700;
	GetCharacterMovement()->GravityScale = 2;
	GetCharacterMovement()->BrakingFrictionFactor = 1;
	GetCharacterMovement()->BrakingFriction = 6.0f;
	GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1400.f;
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	bUseControllerRotationYaw = true;
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->Length = 500.f;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	WeaponComponent->SetupAttachment(GetMesh(), TEXT("hand_r_weapon_socket"));
	WeaponComponent->SetVisibility(false);
	WeaponComponent->SetCastShadow(false);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), TEXT("CameraSocket"));
	FollowCamera->SetRelativeLocation(FVector(-0.7, 9, 5));
	FollowCamera->SetRelativeRotation(FRotator(-90, 0, 95));
	FollowCamera->SetFieldOfView(100);
	FollowCamera->bUsePawnControlRotation = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetIntensity(500);
	PointLight->SetSourceRadius(100);
	PointLight->SetSoftSourceRadius(100);
	PointLight->SetLightColor(FLinearColor::FromSRGBColor(FColor::FromHex(TEXT("FFAD5DFF"))));
	PointLight->SetupAttachment(FollowCamera);
}

void ABottomDwellerCharacter::RecalculateDamage()
{
	const UPlayerAttributeSet* PlayerAttributeSet = Cast<const
		UPlayerAttributeSet>(AbilitySystemComponent->GetAttributeSet(UPlayerAttributeSet::StaticClass()));

	const float BluntDamage = PlayerAttributeSet->GetWeaponBluntDamage() + PlayerAttributeSet->GetStrength();
	const float SlashingDamage = PlayerAttributeSet->GetWeaponSlashingDamage() + PlayerAttributeSet->GetStrength() * 0.5 + PlayerAttributeSet->GetDexterity() *
		0.5;
	const float PiercingDamage = PlayerAttributeSet->GetWeaponPiercingDamage() + PlayerAttributeSet->GetDexterity();

	AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetBluntDamageAttribute(), BluntDamage);
	AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetSlashingDamageAttribute(), SlashingDamage);
	AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetPiercingDamageAttribute(), PiercingDamage);
}

void ABottomDwellerCharacter::BeginPlay()
{
	Cast<ABottomDwellerPlayerController>(GetController())->InitializeHUD();
	Super::BeginPlay();
}

void ABottomDwellerCharacter::Move(float ForwardValue, float RightValue)
{
	if ((Controller != nullptr) && (ForwardValue != 0.0f || RightValue != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector DirectionForward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector DirectionRight = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement in that direction
		AddMovementInput(DirectionForward, ForwardValue);
		AddMovementInput(DirectionRight, RightValue);
	}
}

float ABottomDwellerCharacter::GetSensitivity()
{
	if (AbilitySystemComponent->HasMatchingGameplayTag(Tag_Event_Attack))
	{
		return AttackSensitivityMultiplier;
	}
	return Sensitivity;
}

void ABottomDwellerCharacter::OnActorLoaded_Implementation()
{
	Super::OnActorLoaded_Implementation();
}

void ABottomDwellerCharacter::BeginAttack_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = AttackWalkSpeed;
}

void ABottomDwellerCharacter::EndAttack_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ABottomDwellerCharacter::EnableWeaponTracing_Implementation()
{
	WeaponComponent->SetCanTrace(true);
}

void ABottomDwellerCharacter::DisableWeaponTracing_Implementation()
{
	WeaponComponent->SetCanTrace(false);
}

#include "BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InteractionComponent/InteractionComponent.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

ABottomDwellerCharacter::ABottomDwellerCharacter()
{
	InitActorComponents();
}

void ABottomDwellerCharacter::InitActorComponents()
{
	WalkSpeed = 500;
	AttackWalkSpeed = 100;
	RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AttackRotationRate = FRotator(0.0f, 200.0f, 0.0f);
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 700;;
	GetCharacterMovement()->BrakingFrictionFactor = 1;
	GetCharacterMovement()->BrakingFriction = 6.0f;
	GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = RotationRate;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1400.f;
	// bUseControllerRotationPitch = true;
	// bUseControllerRotationYaw = true;
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->Length = 500.f;

	// GetCharacterMovement()->bOrientRotationToMovement = false;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponComponent->SetupAttachment(GetMesh(), TEXT("hand_r_weapon_socket"));
	WeaponComponent->SetVisibility(false);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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

void ABottomDwellerCharacter::OnActorLoaded_Implementation()
{
	Super::OnActorLoaded_Implementation();
}

void ABottomDwellerCharacter::BeginAttack_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = AttackWalkSpeed;
	GetCharacterMovement()->RotationRate = AttackRotationRate;
}

void ABottomDwellerCharacter::EndAttack_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->RotationRate = RotationRate;
}

void ABottomDwellerCharacter::EnableWeaponCollision_Implementation()
{
	WeaponComponent->SetCollisionProfileName(EName::Actor);
}

void ABottomDwellerCharacter::DisableWeaponCollision_Implementation()
{
	WeaponComponent->SetCollisionProfileName(EName::None);
}

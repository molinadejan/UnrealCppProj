#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CRifle.h"
#include "Widgets/CUserWidget_CrossHair.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent< USpringArmComponent>(
				this, &SpringArm, "SpringArm", GetCapsuleComponent()
		); 
	CHelpers::CreateComponent< UCameraComponent>(
		this, &Camera, "Camera",SpringArm
		);

	bUseControllerRotationYaw = false; 
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->MaxWalkSpeed = 400.0f; 

	USkeletalMesh* mesh; 
	CHelpers::GetAsset<USkeletalMesh>(&mesh,
		"SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"); 
	GetMesh()->SetSkeletalMesh(mesh); 
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90)); 
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // pitch yaw , roll

	TSubclassOf<UAnimInstance> animInstance; 
	CHelpers::GetClass<UAnimInstance>(&animInstance,
		"AnimBlueprint'/Game/ABP_CPlayer.ABP_CPlayer_C'"); 
	GetMesh()->SetAnimInstanceClass(animInstance); 

	SpringArm->SetRelativeLocation(FVector(0, 0, 60)); 
	SpringArm->TargetArmLength = 200.0f; 
	SpringArm->bDoCollisionTest = false; 
	SpringArm->bUsePawnControlRotation = true; 
	SpringArm->SocketOffset = FVector(0, 60, 0); 

	CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'"); 
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// : Materail 
	UMaterialInstanceConstant* bodyMaterial; 
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(
			&bodyMaterial, 
			"MaterialInstanceConstant'/Game/Material/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'"
			); 

	UMaterialInstanceConstant* logoMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(
			&logoMaterial, 
			"MaterialInstanceConstant'/Game/Material/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'"
			);

	BodyMaterial = UMaterialInstanceDynamic::Create(
		bodyMaterial, this); 
	LogoMaterial = UMaterialInstanceDynamic::Create(
		logoMaterial, this);

	GetMesh()->SetMaterial(0, BodyMaterial); 
	GetMesh()->SetMaterial(1, LogoMaterial);

	Rifle = ACRifle::Spawn(GetWorld(), this); 

	CrossHair = CreateWidget<UCUserWidget_CrossHair, APlayerController>
		(GetController<APlayerController>(), CrossHairClass); 
	CrossHair->AddToViewport(); 
	CrossHair->SetVisibility(ESlateVisibility::Hidden); 

	OnRifle(); // << : 
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward); 
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning); 
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle); 
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0); 
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D(); 
	AddMovementInput(direction, Axis); 
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();
	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis); 
}

void ACPlayer::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f; 
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor); 
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ACPlayer::OnRifle()
{
	if (Rifle->GetEquipped())
	{
		Rifle->Unequip(); 
		return; 
	}
	Rifle->Equip(); 
}

void ACPlayer::OnAim()
{
	CheckFalse(Rifle->GetEquipped()); 
	CheckTrue(Rifle->GetEquipping()); 

	bUseControllerRotationYaw = true; 
	GetCharacterMovement()->bOrientRotationToMovement = false; 

	SpringArm->TargetArmLength = 100.0f; 
	SpringArm->SocketOffset = FVector(0, 30, 10);
	//Camera->FieldOfView = 40.0f; 

	OnZoomIn(); 
	Rifle->Begin_Aiming(); 
	CrossHair->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 60, 0);
	//Camera->FieldOfView = 90.0f;
	OnZoomOut(); 
	Rifle->End_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);
}


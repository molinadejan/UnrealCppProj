#include "CAnimInstance.h"
#include "Global.h"
#include "GameFrameWork/Character.h"
#include "IRifle.h"
#include "CRifle.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner()); 
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds); 

	CheckNull(OwnerCharacter); 

	Speed = OwnerCharacter->GetVelocity().Size2D(); 
	Direction = CalculateDirection(OwnerCharacter->GetVelocity() ,
		OwnerCharacter->GetControlRotation()); 

	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch; 

	IIRifle* rifle = Cast<IIRifle>(OwnerCharacter); 
	if (!!rifle)
	{
		bEquipped = rifle->GetRifle()->GetEquipped(); 
		bAiming = rifle->GetRifle()->GetAiming(); 
	}
}

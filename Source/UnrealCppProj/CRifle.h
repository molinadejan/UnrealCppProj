#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACRifle : public AActor
{
	GENERATED_BODY()

private : 
	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class USkeletalMeshComponent* Mesh; 

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName	HandSocket = "Hand_Rifle"; 

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		FName	HolsterSocket = "Holster_Rifle";

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* GrabMontage; 

	UPROPERTY(VisibleDefaultsOnly, Category = "Rifle")
		class UAnimMontage* UngrabMontage;




public :
	static ACRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner); 


public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	class ACharacter* OwnerCharacter; 

private :
	bool bEquipped; 
	bool bEquipping; 
	bool bAiming; 

public : 
	FORCEINLINE bool GetEquipped() { return bEquipped;  }
	FORCEINLINE bool GetEquipping() { return bEquipping; }
	FORCEINLINE bool GetAiming() { return bAiming; }

	void Equip(); 
	void Begin_Equip(); 
	void End_Equip(); 

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aiming(); 
	void End_Aiming();
};

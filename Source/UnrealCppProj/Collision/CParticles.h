#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent*		Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystem*		Particles[3]; 

protected:
	virtual void BeginPlay() override;

private :
	UFUNCTION()
		void PlayParticle(int32 InIndex); 
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CComponentOverlap.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACComponentOverlap : public AActor
{
	GENERATED_BODY()
	
public:	
	ACComponentOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent*		Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent*		Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight; 

private :
	UFUNCTION()
		void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, 
						const FHitResult& SweepResult);
	UFUNCTION()
		void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex);

};

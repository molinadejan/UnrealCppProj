#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMulticastTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightBeginOverlap, int32, FLinearColor); 

UCLASS()
class UNREALCPPPROJ_API ACMulticastTrigger : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:	
	ACMulticastTrigger();

protected:
	virtual void BeginPlay() override;

public :
	FMultiLightBeginOverlap		OnMultiLightBeginOverlap; 
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTrigger.generated.h"

DECLARE_DELEGATE(FBoxLightBeginOverlap); 
DECLARE_DELEGATE(FBoxLightEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor); 


UCLASS()
class UNREALCPPPROJ_API ACTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTrigger();

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene; 

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box; 

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private  : 
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor); 
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public :
	FBoxLightBeginOverlap		OnBoxLightBeginOverlap;
	FBoxLightEndOverlap			OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap	OnBoxLightRandomBeginOverlap; 
};

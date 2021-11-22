#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEventTrigger.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEventTrigger();

public :
	DECLARE_EVENT_OneParam(ACEventTrigger, FEventTrigger, int32) 

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

protected:
	virtual void BeginPlay() override;

public :
	FEventTrigger	OnEventTrigger; 
};

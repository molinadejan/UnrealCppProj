#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, 
					class AActor*, InActor, 
					FLinearColor, InColor); 

UCLASS()
class UNREALCPPPROJ_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private :
	TArray<class ACCylinder*>	Cylinders; 

public :
	UPROPERTY(BlueprintAssignable)
		FTraceResult	OnTraceResult; 

protected :
	UFUNCTION(BlueprintCallable)
		void RestoreColor(class ACPlayer* InPlayer); 

private :
	UFUNCTION()
		void StartJump(class AActor* InActor, FLinearColor InColor); 
};

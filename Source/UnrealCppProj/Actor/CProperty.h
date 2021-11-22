#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACProperty : public AActor
{
	GENERATED_BODY()
	
private :
	UPROPERTY(EditAnywhere)
		int A = 10; 
	UPROPERTY(EditInstanceOnly)
		int B = 20; 
	UPROPERTY(EditDefaultsOnly)
		int C; 
protected :
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int D = 40; 

public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

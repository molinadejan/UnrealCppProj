#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawnActor.generated.h"

UCLASS()
class UNREALCPPPROJ_API ACSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawnActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh; 

private :
	class UMaterialInstanceDynamic* Material; 

	UFUNCTION()
		void ChangeColor(); 
};

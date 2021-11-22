#include "CProperty.h"

ACProperty::ACProperty()
{
	PrimaryActorTick.bCanEverTick = true;
	C = 55; 
}

void ACProperty::BeginPlay()
{
	Super::BeginPlay();

	FString str; 
	str.Append("A : "); 
	str.Append(FString::FromInt(A)); 

	str.Append(" , B : "); 
	str.Append(FString::FromInt(B));

	str.Append(" , C : ");
	str.Append(FString::FromInt(C));

	str.Append(" , D : ");
	str.Append(FString::FromInt(D));

	GLog->Log(str); 	
}

void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


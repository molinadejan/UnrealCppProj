#include "CActorOverlap.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


ACActorOverlap::ACActorOverlap()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene"); 
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene); 
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene); 

	Box->SetRelativeScale3D(FVector(3)); 
	Box->bHiddenInGame = false; 

	Text->SetRelativeLocation(FVector(0, 0, 100)); 
	Text->SetRelativeRotation(FRotator(0, 90, 0)); 
	Text->SetRelativeScale3D(FVector(2)); 
	Text->TextRenderColor = FColor::Red; 
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center; 
	Text->Text = FText::FromString(GetName()); 
}

void ACActorOverlap::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACActorOverlap::ActorBeginOverlap); 
	OnActorEndOverlap.AddDynamic(this, &ACActorOverlap::ActorEndOverlap);
}

void ACActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = ""; 
	str.Append(__FUNCTION__);
	str.Append(" : "); 
	str.Append(OtherActor->GetActorLabel()); // > GetName());
	CLog::Log(str); 
}

void ACActorOverlap::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString str = "";
	str.Append(__FUNCTION__);
	str.Append(" : ");
	str.Append(OtherActor->GetActorLabel()); // > GetName());
	CLog::Log(str);
}
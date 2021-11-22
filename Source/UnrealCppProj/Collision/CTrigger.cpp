#include "CTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


ACTrigger::ACTrigger()
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

void ACTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACTrigger::ActorBeginOverlap); 
	OnActorEndOverlap.AddDynamic(this, &ACTrigger::ActorEndOverlap);
}

void ACTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnBoxLightBeginOverlap.IsBound())
		OnBoxLightBeginOverlap.Execute(); 

	if (OnBoxLightRandomBeginOverlap.IsBound())
	{
		FLinearColor color; 
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1); 
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f; 

		FString str = OnBoxLightRandomBeginOverlap.Execute(color); 
		CLog::Log(str); 
	}
}

void ACTrigger::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnBoxLightEndOverlap.IsBound())
		OnBoxLightEndOverlap.Execute();
}
#include "CLineTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "CCylinder.h"
#include "CPlayer.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 90, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	CHelpers::FindActor<ACCylinder>(GetWorld(), Cylinders); 
	OnTraceResult.AddDynamic(this, &ACLineTrace::StartJump); 
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = Cylinders[0]->GetActorLocation(); 
	FVector end	  = Cylinders[1]->GetActorLocation();

	start.Z -= 10; 
	end.Z -= 10; 

	DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false); 

	TArray<AActor*> ignoreActors; 
	ignoreActors.Add(Cylinders[0]); 
	ignoreActors.Add(Cylinders[1]);

	FHitResult	hitResult; 
	if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(),
		start, end, "Pawn", false, ignoreActors, EDrawDebugTrace::ForOneFrame,
		hitResult, true , FLinearColor::Green, FLinearColor::Red))
	{
		//CLog::Log(hitResult.GetActor()->GetName());
		if (OnTraceResult.IsBound())
		{
			FLinearColor color; 
			color.R = UKismetMathLibrary::RandomFloatInRange(0, 1); 
			color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
			color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
			color.A = 1.0f; 
			OnTraceResult.Broadcast(hitResult.GetActor(), color); 
		}

	}
}

void ACLineTrace::StartJump(class AActor* InActor, FLinearColor InColor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor); 
	CheckNull(player); 

	player->Jump(); 
}

void ACLineTrace::RestoreColor(ACPlayer* InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1)); 
}

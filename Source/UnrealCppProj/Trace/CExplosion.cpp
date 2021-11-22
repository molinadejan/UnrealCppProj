#include "CExplosion.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

// // ParticleSystem'/Game/Effects/P_Explosion2.P_Explosion2'

ACExplosion::ACExplosion()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle"); 

	UParticleSystem* particle; 
	CHelpers::GetAsset<UParticleSystem>(&particle,
		"ParticleSystem'/Game/Effects/P_Explosion2.P_Explosion2'");
	
	Particle->SetTemplate(particle); 
	Particle->bAutoActivate = false; 
}

void ACExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACExplosion::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Particle->ResetParticles(); 
	Particle->SetActive(true); 

	FVector start = GetActorLocation(); 
	FVector end = FVector(start.X, start.Y, start.Z + 10); 

	TArray<TEnumAsByte<EObjectTypeQuery>> queries; 
	queries.Add(EObjectTypeQuery::ObjectTypeQuery4); 

	TArray<AActor*> ignoreActors; 
	ignoreActors.Add(this); 

	TArray<FHitResult> hitResults; 
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 200, queries, false,
		ignoreActors, EDrawDebugTrace::ForOneFrame, hitResults, true))
	{
		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>
				(hitResult.GetActor()->GetRootComponent()); 
			if (!!meshComponent)
				meshComponent->AddRadialImpulse(GetActorLocation(), 1000,
					meshComponent->GetMass() * 700.0f, ERadialImpulseFalloff::RIF_Linear); 
		}
	}

}
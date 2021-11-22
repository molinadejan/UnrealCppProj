#include "CLogActor.h"
#include "Global.h"

ACLogActor::ACLogActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLogActor::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(10); 
	CLog::Print(20, 1); 
	CLog::Print(30, 2, 20.0f); 
	CLog::Print(40, 3, 2.0f); 
	CLog::Print("UnrealCppProj"); 
	CLog::Print(GetActorLocation()); 
	CLog::Print(GetActorRotation()); 
	CLog::Log(33); 
	CLog::Log(PI); 
	CLog::Log("UnrealCppProj");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());

	CLog::Log(this); 
	// CLog::Log(__FUNCDNAME__, __LINE__ ); 
	PrintLine(); 
}

void ACLogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime; 
	CLog::Print(Time , 4); 
}


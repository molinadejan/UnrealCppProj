#include "UnrealCppProjGameModeBase.h"
#include "Global.h"

//    Blueprint'/Game/BP_CPlayer.BP_CPlayer'

AUnrealCppProjGameModeBase::AUnrealCppProjGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"); 
}
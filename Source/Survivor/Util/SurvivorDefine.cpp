#include "SurvivorDefine.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

bool FSurvivorDefine::IsGameRunning()
{
#if WITH_EDITOR
	return (GEditor && GEditor->IsPlaySessionInProgress());
#endif
	return true;
}

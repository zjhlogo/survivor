#include "DebugUtil.h"

#if defined UE_BUILD_DEBUG

void FDebugUtil::Print(const FString& Str, const FColor& Color, float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Str);
}

#endif

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Debug.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVOR_API UDebug : public UObject
{
	GENERATED_BODY()

public:
	static void PrintOnScreen(const FString& FormatString);

	template <typename Arg1>
	static void PrintOnScreen(const TCHAR* FormatString, Arg1 arg1)
	{
		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(arg1));
		PrintOnScreen(FString::Format(FormatString, args));
	}

	template <typename Arg1, typename Arg2>
	static void PrintOnScreen(const TCHAR* FormatString, Arg1 arg1, Arg2 arg2)
	{
		TArray<FStringFormatArg> args;
		args.Add(FStringFormatArg(arg1));
		args.Add(FStringFormatArg(arg2));
		PrintOnScreen(FString::Format(FormatString, args));
	}
};

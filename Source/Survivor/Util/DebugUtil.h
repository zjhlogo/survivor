// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"

#if defined UE_BUILD_DEBUG
class FDebugUtil
{
public:
	static void Print(const FString& Str, const FColor& Color = FColor::Red, float Duration = 2.0f);

	template <typename T1>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Args.Add(FStringFormatArg(Arg5));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Args.Add(FStringFormatArg(Arg5));
		Args.Add(FStringFormatArg(Arg6));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Args.Add(FStringFormatArg(Arg5));
		Args.Add(FStringFormatArg(Arg6));
		Args.Add(FStringFormatArg(Arg7));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7, T8 Arg8)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Args.Add(FStringFormatArg(Arg5));
		Args.Add(FStringFormatArg(Arg6));
		Args.Add(FStringFormatArg(Arg7));
		Args.Add(FStringFormatArg(Arg8));
		Print(FString::Format(Fmt, Args), Color);
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	static void PrintOnScreen(const TCHAR* Fmt, const FColor& Color, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5, T6 Arg6, T7 Arg7, T8 Arg8, T9 Arg9)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(FStringFormatArg(Arg1));
		Args.Add(FStringFormatArg(Arg2));
		Args.Add(FStringFormatArg(Arg3));
		Args.Add(FStringFormatArg(Arg4));
		Args.Add(FStringFormatArg(Arg5));
		Args.Add(FStringFormatArg(Arg6));
		Args.Add(FStringFormatArg(Arg7));
		Args.Add(FStringFormatArg(Arg8));
		Args.Add(FStringFormatArg(Arg9));
		Print(FString::Format(Fmt, Args), Color);
	}
};

#define PRINT_R(Fmt, ...) FDebugUtil::PrintOnScreen(TEXT(Fmt), FColor::Red, __VA_ARGS__)
#define PRINT_G(Fmt, ...) FDebugUtil::PrintOnScreen(TEXT(Fmt), FColor::Green, __VA_ARGS__)
#define PRINT_B(Fmt, ...) FDebugUtil::PrintOnScreen(TEXT(Fmt), FColor::Blue, __VA_ARGS__)
#define LOG_D(Fmt, ...) UE_LOGFMT(LogTemp, Log, Fmt, __VA_ARGS__)
#define LOG_W(Fmt, ...) UE_LOGFMT(LogTemp, Warning, Fmt, __VA_ARGS__)
#define LOG_E(Fmt, ...) UE_LOGFMT(LogTemp, Error, Fmt, __VA_ARGS__)
#else
#define SCREEN_R(Fmt, ...)
#define SCREEN_G(Fmt, ...)
#define SCREEN_B(Fmt, ...)
#define LOG_D(Fmt, ...)
#define LOG_W(Fmt, ...)
#define LOG_E(Fmt, ...)
#endif

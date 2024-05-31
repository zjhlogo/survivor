// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug.h"

void UDebug::PrintOnScreen(const FString& FormatString)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FormatString);
}

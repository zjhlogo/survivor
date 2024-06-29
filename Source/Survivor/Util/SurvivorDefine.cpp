#include "SurvivorDefine.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

const float FSurvivorDefine::DefaultPickupRadius = 200.0f;
const float FSurvivorDefine::DefaultMovementSpeed = 300.0f;

bool FSurvivorDefine::IsGameRunning()
{
#if WITH_EDITOR
	return (GEditor && GEditor->IsPlaySessionInProgress());
#endif
	return true;
}

void FSurvivorDefine::CalculateAccumulateWeights(TArray<float>& OutAccumulateWeights, const TArray<float>& Weights)
{
	OutAccumulateWeights.Empty();
	float TotalWeight = 0.0f;
	for (const auto& Weight : Weights)
	{
		TotalWeight += Weight;
		OutAccumulateWeights.Add(TotalWeight);
	}
}

int32 FSurvivorDefine::ChoiceByAccumulateWeights(const TArray<float>& AccumulateWeights)
{
	float TotalWeight = AccumulateWeights.Last();
	float ChooseCumWeight = FMath::RandRange(0.0f, TotalWeight);
	int32 Index = 0;
	for (const auto& AccumulateWeight : AccumulateWeights)
	{
		if (ChooseCumWeight < AccumulateWeight)
		{
			return Index;
		}
		++Index;
	}

	return Index;
}

int32 FSurvivorDefine::ChoiceByWeights(const TArray<float>& Weights)
{
	TArray<float> AccumulateWeights;
	CalculateAccumulateWeights(AccumulateWeights, Weights);
	return ChoiceByAccumulateWeights(AccumulateWeights);
}

bool FSurvivorDefine::ChoiceByAccumulateWeights(TArray<int32>& OutChoices, const TArray<float>& AccumulateWeights, int32 Count)
{
	if (AccumulateWeights.Num() <= 0)
	{
		return false;
	}

	OutChoices.Empty();
	for (int i = 0; i < Count; ++i)
	{
		auto Index = ChoiceByAccumulateWeights(AccumulateWeights);
		OutChoices.Add(Index);
	}

	return true;
}

bool FSurvivorDefine::ChoiceByWeights(TArray<int32>& OutChoices, const TArray<float>& Weights, int32 Count)
{
	TArray<float> AccumulateWeights;
	CalculateAccumulateWeights(AccumulateWeights, Weights);
	return ChoiceByAccumulateWeights(OutChoices, AccumulateWeights, Count);
}

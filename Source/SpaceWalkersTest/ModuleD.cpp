// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleD.h"

#include "GameBoard.h"

UModuleD::UModuleD()
{
	Cost = 750.f;
	TickDelay = 10.f;
	LevelUpCost = 1000.f;
	MaxLevel = 3;
	StartingTicks.Init(-1.f, 8);
}

FText UModuleD::GetModuleInfo() const
{
	return MODULE_TEXT_FORMAT("Reduces the tick of all adjecent modules by {0}%\n up to {1}% of its starting tick", TickDecreasePercent, MinLeftTickPercent);
}

bool UModuleD::IsInfluenced(UModuleBase* Module) const
{
	return Module && !Module->IsA(UModuleD::StaticClass()) && (Module->X <= (X + 1) && Module->X >= (X - 1) && Module->Y <= (Y + 1) && Module->Y >= (Y - 1));
}

void UModuleD::ModuleTick()
{
	Super::ModuleTick();

	auto Adj = GameBoard->GetMatchingModules(this, [this](UModuleBase* Module){ return IsInfluenced(Module); });

	for(auto It : Adj)
	{
		if(!It || It->IsFailed())
			continue;

		// 0 1 2
		// 3 + 4
		// 5 6 7
		int32 ConIndex = (It->Y - Y + 1) * 3 + (It->X - X + 1);
		if(ConIndex > 3) --ConIndex;

		if(StartingTicks[ConIndex] < 0.f)
			StartingTicks[ConIndex] = It->GetModuleTick();

		float AfterDecrease = It->GetModuleTick() - It->GetModuleTick() * (TickDecreasePercent / 100.f);
		if(StartingTicks[ConIndex] / 2.f < AfterDecrease)
		{
			It->UpdateTickTime(AfterDecrease);
			It->OnPopUp.Broadcast(MODULE_TEXT_FORMAT("Tick -{0}%", TickDecreasePercent), FLinearColor(0.8f, 0.2f, 0.3f, 1.f));
		}
		else if(It->GetModuleTick() > StartingTicks[ConIndex] / 2.f)
		{
			float Diff = It->GetModuleTick() - StartingTicks[ConIndex] / 2.f;
			It->UpdateTickTime(StartingTicks[ConIndex] / 2.f);
			It->OnPopUp.Broadcast(MODULE_TEXT_FORMAT("Tick -{0}%", Diff / StartingTicks[ConIndex] * 100.f), FLinearColor(0.8f, 0.2f, 0.3f, 1.f));
		}
	}
}

void UModuleD::OnLevelUp()
{
	TickDecreasePercent += 10.f;
}

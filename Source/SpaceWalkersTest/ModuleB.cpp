// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleB.h"
#include "GameBoard.h"
#include "ModuleA.h"

void UModuleB::Init()
{
	Super::Init();

	MaxLevel = 5;
	TickDelay = 2.f;
}

void UModuleB::ModuleTick()
{
	Super::ModuleTick();

	if(GameBoard.Get())
	{
		auto Adj = GameBoard->GetMatchingModules(this, [this](UModuleBase* Module){ return IsInfluenced(Module); });

		float ResToGen = 0.f;
		for(auto& It : Adj)
		{
			if(!It->IsFailed())
			{
				UModuleA* ModA = Cast<UModuleA>(It);
				if(ModA)
					ResToGen += ModA->ResourceGenerated * (PercentToGen / 100.f);
			}
		}
		if(ResToGen > 0.f)
		{
			GameBoard->ModifyResource(ResToGen);
			OnPopUp.Broadcast(MODULE_TEXT_FORMAT("Plus {0}", ResToGen), FLinearColor::Green);
		}
	}
}

FText UModuleB::GetModuleInfo() const
{
	auto Adj = GameBoard->GetMatchingModules(this, [this](UModuleBase* Module){ return IsInfluenced(Module); });

	float ResToGen = 0.f;
	for(auto& It : Adj)
	{
		if(It && !It->IsFailed())
		{
			UModuleA* ModA = Cast<UModuleA>(It);
			if(ModA)
				ResToGen += ModA->ResourceGenerated * (PercentToGen / 100.f);
		}
	}

	return MODULE_TEXT_FORMAT("nAcquired from nearby modules: {0}\nAcquired Resource: {1}%", ResToGen, PercentToGen);
}

bool UModuleB::IsInfluenced(UModuleBase* Module) const
{
	return Module && Module->IsA(UModuleA::StaticClass()) && (Module->X <= (X + 1) && Module->X >= (X - 1) && Module->Y <= (Y + 1) && Module->Y >= (Y - 1)); 
}

void UModuleB::OnLevelUp()
{
	Super::OnLevelUp();

	PercentToGen += 10.f;
}

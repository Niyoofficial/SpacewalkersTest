// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleC.h"

#include "GameBoard.h"

UModuleC::UModuleC()
{
	Cost = 500.f;
	TickDelay = 10.f;
}

void UModuleC::ModuleTick()
{
	Super::ModuleTick();

	if(GameBoard.Get())
	{
		auto Adj = GameBoard->GetMatchingModules(this, [this](UModuleBase* Module){ return IsInfluenced(Module); });

		for(auto& It : Adj)
		{
			if(It && !It->IsFailed())
			{
				It->LevelUp();
			}
		}
	}
}

bool UModuleC::IsInfluenced(UModuleBase* Module) const
{
	return Module && !Module->IsA(UModuleC::StaticClass()) && (Module->X <= (X + 1) && Module->X >= (X - 1) && Module->Y <= (Y + 1) && Module->Y >= (Y - 1)); 
}

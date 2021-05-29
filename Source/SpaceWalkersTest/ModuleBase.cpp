// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleBase.h"

#include "GameBoard.h"


void UModuleBase::Fix()
{
	if(bFail)
	{
		bFail = false;
		GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UModuleBase::ModuleManager, TickDelay);
		OnModuleTickStarted.Broadcast();
		OnModuleFixed.Broadcast();
	}
}

UModuleBase::UModuleBase()
{
}

void UModuleBase::Init()
{
	GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UModuleBase::ModuleManager, TickDelay);
	OnModuleTickStarted.Broadcast();
}

void UModuleBase::Destroy()
{
	GetWorld()->GetTimerManager().ClearTimer(TickHandle);
}

void UModuleBase::ModuleManager()
{
	if(!bFail)
	{
		ModuleTick();

		if(!CalcFail())
		{
			GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UModuleBase::ModuleManager, TickDelay);
			OnModuleTickStarted.Broadcast();
		}
	}
}

void UModuleBase::LevelUp()
{
	if(Level < MaxLevel)
	{
		++Level;
		FixCost += FixCostIncrease;
		OnLevelUp();
		if(GameBoard.Get())
			GameBoard->OnLevelUp.Broadcast(X, Y);

		OnPopUp.Broadcast(MODULE_TEXT("Level Up!"), FLinearColor(0.f, 1.f, 1.f, 1.f));
	}
}

void UModuleBase::UpdateTickTime(float NewTickTime)
{
	if(NewTickTime > 0.f)
	{
		if(TickHandle.IsValid())
		{
			float NewTime = GetWorld()->GetTimerManager().GetTimerRemaining(TickHandle) / TickDelay * NewTickTime;
			GetWorld()->GetTimerManager().ClearTimer(TickHandle);
			GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UModuleBase::ModuleManager, NewTime);
		}
		TickDelay = NewTickTime;
		OnTickTimeUpdated.Broadcast(TickDelay);
	}
}

bool UModuleBase::CalcFail()
{
	if(FMath::RandRange(0.f, 100.f) < FailChance)
	{
		bFail = true;
		OnModuleFailed.Broadcast();
		OnPopUp.Broadcast(MODULE_TEXT("Crash!"), FLinearColor::Red);
		return true;
	}
	return false;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "ModuleB.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SPACEWALKERSTEST_API UModuleB : public UModuleBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void ModuleTick() override;

	virtual FText GetModuleName() const override { return MODULE_TEXT("Module B"); }

	virtual FText GetModuleInfo() const override;
	
	virtual bool IsInfluenced(UModuleBase* Module) const override;

	virtual void OnLevelUp() override;

private:
	float PercentToGen = 20.f;
};

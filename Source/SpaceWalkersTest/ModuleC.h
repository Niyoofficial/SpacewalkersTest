// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "ModuleC.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SPACEWALKERSTEST_API UModuleC : public UModuleBase
{
	GENERATED_BODY()

public:
	UModuleC();

	virtual void ModuleTick() override;

	virtual bool IsInfluenced(UModuleBase* Module) const override;

	virtual FText GetModuleName() const override { return MODULE_TEXT("Module C"); }

	virtual FText GetModuleInfo() const override { return MODULE_TEXT("Levels up all adjecent modules every tick"); }
};

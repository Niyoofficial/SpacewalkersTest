// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "ModuleA.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SPACEWALKERSTEST_API UModuleA : public UModuleBase
{
	GENERATED_BODY()

public:
	UModuleA();

	virtual void ModuleTick() override;

	virtual FText GetModuleName() const override { return MODULE_TEXT("Module A"); }

	virtual FText GetModuleInfo() const override { return MODULE_TEXT_FORMAT("Generates: {0}", ResourceGenerated); }

	virtual void OnLevelUp() override;

public:
	UPROPERTY(EditDefaultsOnly)
	float ResourceGenerated = 10.f;
};

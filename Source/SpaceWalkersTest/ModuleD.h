// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "ModuleD.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SPACEWALKERSTEST_API UModuleD : public UModuleBase
{
	GENERATED_BODY()

public:
	UModuleD();

	virtual FText GetModuleName() const override { return MODULE_TEXT("Module D"); }

	virtual FText GetModuleInfo() const override;

	virtual bool IsInfluenced(UModuleBase* Module) const override;

	virtual void ModuleTick() override;

	virtual void OnLevelUp() override;

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess))
	float TickDecreasePercent = 10.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess))
	float MinLeftTickPercent = 50.f;

private:
	//TArray<float, TInlineAllocator<8>> StartingTicks;
	TArray<float> StartingTicks;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "ModuleA.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWALKERSTEST_API AModuleA : public AModuleBase
{
	GENERATED_BODY()

public:
	AModuleA();

protected:
	virtual void BeginPlay() override;

public:
	virtual void ModuleTick() override;
	
};

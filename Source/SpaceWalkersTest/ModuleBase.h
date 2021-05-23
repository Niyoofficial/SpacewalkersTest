// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModuleBase.generated.h"

UCLASS()
class SPACEWALKERSTEST_API AModuleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AModuleBase();

protected:
	virtual void BeginPlay() override;

public:
	void ModuleManager();

	virtual void ModuleTick();

	void Test();

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMesh* ModuleMesh; 

private:
	float TickDelay = 1.f;

	FTimerHandle TickHandle;
};

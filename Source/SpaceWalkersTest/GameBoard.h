// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoard.generated.h"

class AModuleBase;

UCLASS()
class SPACEWALKERSTEST_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameBoard();

protected:
	virtual void BeginPlay() override;

public:
	void AddModule(AModuleBase* Module, int32 X, int32 Y);

private:
	TArray<TArray<AModuleBase*, TInlineAllocator<5>>, TInlineAllocator<5>> Board;
};

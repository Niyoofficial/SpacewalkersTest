// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BoardPlayer.generated.h"

UCLASS()
class SPACEWALKERSTEST_API ABoardPlayer : public APawn
{
	GENERATED_BODY()

public:
	ABoardPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

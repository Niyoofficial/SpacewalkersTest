// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameBoard.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class UGameBoard;
/**
 * 
 */
UCLASS()
class SPACEWALKERSTEST_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintGetter)
	UGameBoard* GetGameBoard() const { return GameBoard; }

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameBoard> GameBoardClass = UGameBoard::StaticClass();

	UPROPERTY(BlueprintGetter=GetGameBoard)
	UGameBoard* GameBoard;
};

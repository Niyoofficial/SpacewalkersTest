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

public:
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TSubclassOf<UGameBoard> GameBoardClass = UGameBoard::StaticClass();

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float StartResource = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TArray<float> Tiers = {10000.f, 30000.f, 100000.f};

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	int32 BoardSizeX = 5;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	int32 BoardSizeY = 5;

private:
	UPROPERTY(BlueprintGetter=GetGameBoard)
	UGameBoard* GameBoard;
};

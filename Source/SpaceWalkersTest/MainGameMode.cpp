// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "GameBoard.h"

void AMainGameMode::BeginPlay()
{
	GameBoard = NewObject<UGameBoard>(this, GameBoardClass.Get());
	GameBoard->Init(StartResource, Tiers, BoardSizeX, BoardSizeY);
}

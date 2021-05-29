// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"

#include "ModuleA.h"

void UGameBoard::Init()
{
	ModifyResource(200.f);

	//Default construct all of the subarrays and zero the memory of the subarrays so we can check for nullptr
	Board.SetNum(5);
	for(int32 i = 0, j = 0; i < Board.Num(); ++i)
		Board[i]->SetNumZeroed(5);
}

void UGameBoard::AddModule(TSubclassOf<UModuleBase> ModuleClass, int32 X, int32 Y)
{
	UModuleBase* ModuleDefaults = Cast<UModuleBase>(ModuleClass.Get()->GetDefaultObject());
	if(ModuleDefaults && Resource >= ModuleDefaults->Cost)
	{
		if(!Board[X][Y])
		{
			ModifyResource(-ModuleDefaults->Cost);
			Board[X][Y] = NewObject<UModuleBase>(this, ModuleClass.Get());
			Board[X][Y]->GameBoard = this;
			Board[X][Y]->X = X;
			Board[X][Y]->Y = Y;
			Board[X][Y]->Init();
			OnModuleAdded.Broadcast(Board[X][Y], X, Y);
		}
		else
			OnBoardPopUp.Broadcast(BOARD_TEXT("Place already occupied!"));
	}
	else
		OnBoardPopUp.Broadcast(BOARD_TEXT("Not enough resource!"));
}

void UGameBoard::LevelUpModule(int32 X, int32 Y)
{
	if(Board[X][Y]->LevelUpCost <= Resource)
	{
		if(Board[X][Y]->Level < Board[X][Y]->MaxLevel)
		{
			ModifyResource(-Board[X][Y]->LevelUpCost);
			Board[X][Y]->LevelUp();
			OnLevelUp.Broadcast(X, Y);
		}
	}
	else
		OnBoardPopUp.Broadcast(BOARD_TEXT("Not enough resource!"));
}

void UGameBoard::TierUp()
{
	if(Tiers.IsValidIndex(CurrentTier - 1))
	{
		if(Resource >= Tiers[CurrentTier - 1])
		{
			ModifyResource(-Resource);

			for(int32 i = 0; i < Board.Num(); ++i)
			{
				for(int32 j = 0; j < Board[i]->Num(); ++j)
				{
					if(Board[i][j])
						Board[i][j]->Destroy();
				}
			}
			Board.Empty(5);
			Board.SetNum(5);
			for(int32 i = 0, j = 0; i < Board.Num(); ++i)
				Board[i]->SetNumZeroed(5);

			ModifyResource(StartResource);

			OnTierUp.Broadcast(++CurrentTier);
		}
	}
}

void UGameBoard::FixModule(int32 X, int32 Y)
{
	if(Resource >= Board[X][Y]->FixCost)
	{
		ModifyResource(-Board[X][Y]->FixCost);
		Board[X][Y]->Fix();
	}
	else
		OnBoardPopUp.Broadcast(BOARD_TEXT("Not enough resource!"));
}

void UGameBoard::ModifyResource(float Amount)
{
	Resource = FMath::Clamp((double)Resource + (double)Amount, 0.0, (double)TNumericLimits<float>::Max());
	OnResourceChanged.Broadcast(Resource);
}

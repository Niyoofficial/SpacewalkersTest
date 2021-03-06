// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameBoard.generated.h"

#define BOARD_TEXT_FORMAT(Fmt, ...) FText::Format(NSLOCTEXT("Board", Fmt, Fmt), __VA_ARGS__)
#define BOARD_TEXT(Fmt) NSLOCTEXT("Board", Fmt, Fmt)

class UModuleBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FModuleAddedSignature, UModuleBase*, Module, int32, X, int32, Y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResourceChangedSignature, float, Resource);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoardPopUpSignature, FText, Text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FModuleLevelUpSignature, int32, X, int32, Y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTierUpSignature, int32, NewTier);

USTRUCT()
struct FGridRow
{
	GENERATED_BODY()

	FORCEINLINE UModuleBase*& operator[](int32 index)
	{
		return Row[index];
	}

	TArray<UModuleBase*>* operator->()
	{
		return &Row;
	}

	UPROPERTY()
	TArray<UModuleBase*> Row;
};

UCLASS()
class SPACEWALKERSTEST_API UGameBoard : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddModule(TSubclassOf<UModuleBase> ModuleClass, int32 X, int32 Y);

	UFUNCTION(BlueprintCallable)
	void LevelUpModule(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable)
	void TierUp();

	UFUNCTION(BlueprintCallable)
	void FixModule(int32 X, int32 Y);

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE UModuleBase* GetModule(int32 X, int32 Y) const { return Board[X].Row[Y]; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE int32 GetCurrentTier() const { return CurrentTier; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE int32 GetBoardSizeX() const { return BoardSizeX; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE int32 GetBoardSizeY() const { return BoardSizeY; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetResource() const { return Resource; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetTierTarget(int32 Tier) const { return Tiers.IsValidIndex(Tier - 1) ? Tiers[Tier - 1] : -1.f; }

public:
	void ModifyResource(float Amount);

public:
	template<typename PREDICATE>
	TArray<UModuleBase*, TInlineAllocator<8>> GetMatchingModules(UModuleBase* SourceModule, const PREDICATE& Predicate)
	{
		TArray<UModuleBase*, TInlineAllocator<8>> Adj;

		for(auto& It : Board)
			for(int32 i = 0; i < It->Num(); ++i)
				if(It[i] && Predicate(It[i]))
					Adj.Emplace(It[i]);

		return Adj;
	}

	template<typename PREDICATE>
	TArray<UModuleBase*, TInlineAllocator<8>> GetMatchingModules(const UModuleBase* SourceModule, const PREDICATE& Predicate) const
	{
		TArray<UModuleBase*, TInlineAllocator<8>> Adj;

		for(auto& It : Board)
			for(int32 i = 0; i < It.Row.Num(); ++i)
				if(It.Row[i] && Predicate(It.Row[i]))
					Adj.Emplace(It.Row[i]);

		return Adj;
	}

public:	
	virtual void Init(float StartingRes, TArray<float> TiersArray, int32 XSize, int32 YSize);

public:
	UPROPERTY(Category = GameBoard, BlueprintAssignable)
	FModuleAddedSignature OnModuleAdded;

	UPROPERTY(Category = GameBoard, BlueprintAssignable)
	FResourceChangedSignature OnResourceChanged;

	UPROPERTY(Category = GameBoard, BlueprintAssignable)
	FBoardPopUpSignature OnBoardPopUp;

	UPROPERTY(Category = GameBoard, BlueprintAssignable)
	FModuleLevelUpSignature OnLevelUp;

	UPROPERTY(Category = GameBoard, BlueprintAssignable)
	FTierUpSignature OnTierUp;

private:
	float StartResource = 500.f;

	TArray<float> Tiers;

	UPROPERTY(BlueprintGetter=GetBoardSizeX)
	int32 BoardSizeX = 5;

	UPROPERTY(BlueprintGetter=GetBoardSizeY)
	int32 BoardSizeY = 5;

	UPROPERTY(BlueprintGetter=GetCurrentTier)
	int32 CurrentTier = 1;

private:
	bool bCanTierUp = false;

	float Resource;

	UPROPERTY()
	TArray<FGridRow> Board;
};

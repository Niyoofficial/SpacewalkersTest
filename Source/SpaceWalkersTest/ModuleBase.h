// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModuleBase.generated.h"

#define MODULE_TEXT_FORMAT(Fmt, ...) FText::Format(NSLOCTEXT("Module", Fmt, Fmt), __VA_ARGS__)
#define MODULE_TEXT(Fmt) NSLOCTEXT("Module", Fmt, Fmt)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPopUpSignature, FText, PopUpText, FLinearColor, Color);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FModuleTickSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FModuleTickTimeUpdatedSignature, float, NewTickTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFixedSignature);

class UGameBoard;

UCLASS(Abstract, BlueprintType)
class SPACEWALKERSTEST_API UModuleBase : public UObject
{
	GENERATED_BODY()

	friend UGameBoard;

public:
	UFUNCTION(BlueprintGetter)
	FORCEINLINE int32 GetModuleLevel() const { return Level; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE int32 GetModuleMaxLevel() const { return MaxLevel; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE float GetLevelUpCost() const { return LevelUpCost; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE float GetModuleTick() const { return TickDelay; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE bool IsFailed() const { return bFail; }

	UFUNCTION(BlueprintPure)
	virtual FText GetModuleName() const { return MODULE_TEXT("None"); }

	UFUNCTION(BlueprintPure)
	virtual FText GetModuleInfo() const { return MODULE_TEXT("None"); }

	UFUNCTION(BlueprintPure)
	virtual bool IsInfluenced(UModuleBase* Module) const { return false; }

public:	
	UModuleBase();

	virtual void Init();

	virtual void Destroy();

	void ModuleManager();

	virtual void ModuleTick() {}

	virtual void OnLevelUp() {}

	void LevelUp();

	void UpdateTickTime(float NewTickTime);

	void Fix();

private:
	inline bool CalcFail();

public:
	TWeakObjectPtr<UGameBoard> GameBoard;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMesh* ModuleMesh;

	UPROPERTY(BlueprintReadOnly)
	int32 X;

	UPROPERTY(BlueprintReadOnly)
	int32 Y;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Cost = 100.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 UnlockTier = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FailChance = 5.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FixCost = 100.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FixCostIncrease = FixCost;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter=GetLevelUpCost)
	float LevelUpCost = Cost;

	UPROPERTY(Category = Module, BlueprintAssignable)
	FPopUpSignature OnPopUp;

	UPROPERTY(Category = Module, BlueprintAssignable)
	FModuleTickSignature OnModuleTickStarted;

	UPROPERTY(Category = Module, BlueprintAssignable)
	FModuleTickTimeUpdatedSignature OnTickTimeUpdated;

	UPROPERTY(Category = Module, BlueprintAssignable)
	FFailSignature OnModuleFailed;

	UPROPERTY(Category = Module, BlueprintAssignable)
	FFixedSignature OnModuleFixed;

protected:		
	UPROPERTY(BlueprintGetter=GetModuleLevel)
	int32 Level = 1;

	UPROPERTY(BlueprintGetter=GetModuleMaxLevel)
	int32 MaxLevel = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter=GetModuleTick)
	float TickDelay = 1.f;

private:
	UPROPERTY(BlueprintGetter=IsFailed)
	bool bFail = false;

	FTimerHandle TickHandle;
};

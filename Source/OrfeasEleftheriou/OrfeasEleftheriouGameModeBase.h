// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OrfeasEleftheriouGameModeBase.generated.h"

/**
 
	In order to delete a C++ class from your project follow the steps below:

	- Close Visual Studio
	- Close UE4 Editor
	- Remove the corresponding .cpp and .h file from your disk in explorer
	- Remove everything in the folder Binaries
	- Right click the .uproject file and click Generate Visual Studio project Files
	- Get back to your normal activity

 */
UCLASS()
class ORFEASELEFTHERIOU_API AOrfeasEleftheriouGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AOrfeasEleftheriouGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void PrintOnScreen(int32 IntToPrint);

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void DoSomething();

protected:



private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Health = 10.f;
	
};

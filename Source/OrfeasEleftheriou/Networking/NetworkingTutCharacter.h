// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "NetworkingTutCharacter.generated.h"

/**
 * 
 */
class ABomb;

UCLASS()
class ORFEASELEFTHERIOU_API ANetworkingTutCharacter : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:

	ANetworkingTutCharacter();

	// SetupPlayerInputComponent
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	/** Bomb Blueprint */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABomb> BombActorBP;

protected:

	/** The health of the character */
	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_Health, Category = Stats)
	float Health;

	/** The max health of the character */
	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxHealth = 100.f;

	/** The number of bombs that the character carries */
	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_BombCount, Category = Stats)
	int32 BombCount;

	/** The max number of bombs that a character can have */
	UPROPERTY(EditAnywhere, Category = Stats)
	int32 MaxBombCount = 3;

	/** Text render component - used instead of UMG, to keep the tutorial short */
	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* CharText;

private:

	/** Called when the Health variable gets updated */
	UFUNCTION()
	void OnRep_Health();

	/** Called when the BombCount variable gets updated */
	UFUNCTION()
	void OnRep_BombCount();

	/** Initializes health */
	void InitHealth();

	/** Initializes bomb count */
	void InitBombCount();

	/** Updates the character's text to match with the updated stats */
	void UpdateCharText();

	/**
	* TakeDamage Server version. Call this instead of TakeDamage when you're a client
	* You don't have to generate an implementation. It will automatically call the ServerTakeDamage_Implementation function
	*/
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	/** Contains the actual implementation of the ServerTakeDamage function */
	void ServerTakeDamage_Implementation(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	/** Validates the client. If the result is false the client will be disconnected */
	bool ServerTakeDamage_Validate(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	// Bomb related functions

	/** Will try to spawn a bomb */
	void AttempToSpawnBomb();

	/** Returns true if we can throw a bomb */
	bool HasBombs() { return BombCount > 0; }

	/**
	* Spawns a bomb. Call this function when you're authorized to.
	* In case you're not authorized, use the ServerSpawnBomb function.
	*/
	void SpawnBomb();

	/**
	* SpawnBomb Server version. Call this instead of SpawnBomb when you're a client
	* You don't have to generate an implementation for this. It will automatically call the ServerSpawnBomb_Implementation function
	*/
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawnBomb();

	/** Contains the actual implementation of the ServerSpawnBomb function */
	void ServerSpawnBomb_Implementation();

	/** Validates the client. If the result is false the client will be disconnected */
	bool ServerSpawnBomb_Validate();

	/** Applies damage to the character */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};

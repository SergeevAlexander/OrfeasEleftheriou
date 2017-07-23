// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ORFEASELEFTHERIOU_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	APickup();

	/* Enables/Disables the glow effect on the pickup */
	void SetGlowEffect(bool Status);

	/* Returns the Texture of our Pickup */
	FORCEINLINE UTexture2D* GetPickupTexture() { return PickupTexture; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/* The Static Mesh of the pickup */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PickupSM;

	/* The Texture of the item in case we want to add it in the secrets or inventory */
	UPROPERTY(EditAnywhere, Category = "PickupProperties")
	UTexture2D* PickupTexture;

	/* The name of the item */
	UPROPERTY(EditAnywhere, Category = "PickupProperties")
	FString ItemName;
	
};



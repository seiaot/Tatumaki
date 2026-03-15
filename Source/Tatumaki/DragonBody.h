// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "PlayerChara.h"
#include "DragonBody.generated.h"

/**
 * 
 */
UCLASS()
class TATUMAKI_API ADragonBody : public AMyActor
{
	GENERATED_BODY()

public:
	ADragonBody();

	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayer(APlayerChara* pPlayer);

private:
	APlayerChara* m_pPLayer;
	
};

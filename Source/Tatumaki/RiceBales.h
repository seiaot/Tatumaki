// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Offering.h"
#include "RiceBales.generated.h"

/**
 * 
 */
UCLASS()
class TATUMAKI_API ARiceBales : public AOffering
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
};

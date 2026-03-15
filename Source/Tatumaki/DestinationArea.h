// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Area.h"
#include "DestinationArea.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAddInsideED);

UCLASS()
class TATUMAKI_API ADestinationArea : public AArea
{
	GENERATED_BODY()
	
public:
	ADestinationArea();

	UFUNCTION(BlueprintCallable)
	int GetNowOffering() const;

	//オーバーラップ時
	void OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void ChangeInside(int num);

	UFUNCTION(BlueprintCallable)
	void SetDesOffering();

public:
	UPROPERTY(BlueprintAssignable)
	FAddInsideED AddInsideED;

public:
	int m_NowInside;

private:
	int m_InsideRice;	//米俵の数
	int m_InsideFruit;	//果物の数
};

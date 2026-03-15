// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationArea.h"
#include "MyGameInstance.h"

ADestinationArea::ADestinationArea()
	: m_NowInside(0)
{
	m_OverlapTargets.Add("Offering");
}

int ADestinationArea::GetNowOffering() const
{
	return m_NowInside;
}

//オーバーラップ時
void ADestinationArea::OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//増加
	ChangeInside(1);
	if (OtherComp->ComponentHasTag("RiceBales"))
	{
		m_InsideRice += 1;
	}
	else
	{
		m_InsideFruit += 1;
	}
	//配信
	if (AddInsideED.IsBound()) { AddInsideED.Broadcast(); }
}
void ADestinationArea::OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//減少
	ChangeInside(-1);
	if (OtherComp->ComponentHasTag("RiceBales"))
	{
		m_InsideRice -= 1;
	}
	else
	{
		m_InsideFruit -= 1;
	}
}

void ADestinationArea::ChangeInside(int num)
{
	m_NowInside += num;
}

void ADestinationArea::SetDesOffering()
{
	UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();

	GameInstance->m_RiceNum = m_InsideRice;
	GameInstance->m_Fruit = m_InsideFruit;
}
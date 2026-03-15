// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerChara.h"

void UMyGameInstance::SetPlayer(APlayerChara* _pPLayer)
{
	pPlayerChara = _pPLayer;
}

APlayerChara* UMyGameInstance::GetPlayer() const
{
	return pPlayerChara;
}

void UMyGameInstance::SetDesOffering(int _RiceNum, int _Fruit)
{
	m_RiceNum = _RiceNum;
	m_Fruit = _Fruit;
}

int UMyGameInstance::GetDefRice() const
{
	return m_RiceNum;
}
int UMyGameInstance::GetDefFruit() const
{
	return m_Fruit;
}

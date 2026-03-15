// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"

ATerrain::ATerrain()
{
	//メッシュの生成
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("m_pMesh");
	if (m_pMesh)
	{
		//ルートにアタッチ
		m_pMesh->SetupAttachment(RootComponent);
		//プリセット変更
		m_pMesh->SetCollisionProfileName("MyBlockAllStatic");
	}
}
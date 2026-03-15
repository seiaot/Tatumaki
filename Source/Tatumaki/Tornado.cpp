// Fill out your copyright notice in the Description page of Project Settings.


#include "Tornado.h"
#include "Components/SphereComponent.h"
#include "PlayerChara.h"

// Sets default values
ATornado::ATornado()
	: m_Rot(0.0f)
{
	//判定とメッシュの生成
	CreateCollisionAndMesh<USphereComponent, UStaticMeshComponent>();

	if (m_pCollision)
	{
		//物理挙動は行わない
		m_pCollision->SetSimulatePhysics(false);
		//コリジョンプリセット
		m_pCollision->SetCollisionProfileName("MyOverlapAllDynamic");
		//タグの追加
		m_pCollision->ComponentTags.Add("Tornado");
	}

	//中層メッシュの生成
	m_pMesh_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pMesh_2"));
	if (m_pMesh_2)
	{
		//ルートにアタッチ
		m_pMesh_2->SetupAttachment(RootComponent);
		//メッシュは衝突判定を持たない
		m_pMesh_2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	//外層メッシュの生成
	m_pMesh_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pMesh_3"));
	if (m_pMesh_3)
	{
		//ルートにアタッチ
		m_pMesh_3->SetupAttachment(RootComponent);
		//メッシュは衝突判定を持たない
		m_pMesh_3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

//コリジョンの大きさを変更
void ATornado::SetSize(FVector _size)
{
	if (m_pCollision)
	{
		m_pCollision->SetWorldScale3D(_size * 2.0f);
	}
}

//竜巻（メッシュ）回転
void ATornado::RotationTornado(float rot)
{
	m_Rot += rot;

	//中心ほど速く回る
	m_pMesh->SetWorldRotation(FRotator(0.0f, m_Rot * 4.0f, 0.0f));
	m_pMesh_2->SetWorldRotation(FRotator(0.0f, m_Rot * 2.0f, 0.0f));
	m_pMesh_3->SetWorldRotation(FRotator(0.0f, m_Rot, 0.0f));
}
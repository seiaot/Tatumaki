// Fill out your copyright notice in the Description page of Project Settings.


#include "NoCollisionActor.h"

// Sets default values
ANoCollisionActor::ANoCollisionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//メッシュの生成
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pMesh"));
	if (m_pMesh)
	{
		//ルートにアタッチ
		m_pMesh->SetupAttachment(RootComponent);
		//メッシュは衝突判定を持たない
		m_pMesh->SetCollisionProfileName("AllIgnore");
	}
}

// Called when the game starts or when spawned
void ANoCollisionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoCollisionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
	: m_pCollision(NULL)
	, m_pMesh(NULL)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), 0.0f);
}

void AMyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//タグが対応してる時のみ処理
	for (int i = 0; i < m_OverlapTargets.Num(); ++i)
	{
		if (OtherComp->ComponentHasTag(m_OverlapTargets[i])) { break; }

		if (i == m_OverlapTargets.Num() - 1) { return; }
	}

	OverlapBeginEvent(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AMyActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//タグが対応してる時のみ処理
	for (int i = 0; i < m_OverlapTargets.Num(); ++i)
	{
		if (OtherComp->ComponentHasTag(m_OverlapTargets[i])) { break; }

		if (i == m_OverlapTargets.Num() - 1) { return; }
	}

	OverlapEndEvent(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

//オーバーラップ時の関数が呼ぶ用の関数
void AMyActor::OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}
void AMyActor::OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

//消滅
void AMyActor::DestroyAll()
{
	m_pMesh->DestroyComponent();
	m_pCollision->DestroyComponent();
	Destroy();
}
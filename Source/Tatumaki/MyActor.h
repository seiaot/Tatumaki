// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TATUMAKI_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//コリジョンとメッシュの生成
	template<class Collision,class Mesh>
	void CreateCollisionAndMesh()
	{
		//衝突判定の生成
		m_pCollision = CreateDefaultSubobject<Collision>(TEXT("m_pCollision"));
		if (m_pCollision)
		{
			//衝突判定をルートにする
			RootComponent = m_pCollision;

			//コリジョンイベントの有効化・登録
			m_pCollision->SetGenerateOverlapEvents(true);
			m_pCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnOverlapBegin);
			m_pCollision->OnComponentEndOverlap.AddDynamic(this, &AMyActor::OnOverlapEnd);
		}

		//メッシュの生成
		m_pMesh = CreateDefaultSubobject<Mesh>(TEXT("m_pMesh"));
		if (m_pMesh)
		{
			//ルートにアタッチ
			m_pMesh->SetupAttachment(RootComponent);
			//メッシュは衝突判定を持たない
			m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//オーバーラップ時
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//!オーバーラップ時
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	//オーバーラップ時の関数が呼ぶ用の関数
	virtual void OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	//消滅
	void DestroyAll();

protected:
	//衝突時処理を行う対象のタグ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target, meta = (AllowPrivateAccess = "true"));
	TArray<FName> m_OverlapTargets;

	//衝突判定
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"));
	UPrimitiveComponent* m_pCollision;

	//スタティックメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* m_pMesh;

};

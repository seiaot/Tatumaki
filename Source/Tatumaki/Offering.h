// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MyActor.h"
#include "Offering.generated.h"

//前方宣言
class APlayerChara;

enum class State
{
	Idle,
	Go,
	Drift,
	fall
};

UCLASS()
class TATUMAKI_API AOffering : public AMyActor
{
	GENERATED_BODY()

public:
	AOffering();
	
	virtual void Tick(float DeltaTime) override;

	//オーバーラップ時
	virtual void OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//竜巻に向かう処理
	void GoTornado(float DeltaTime);
	//竜巻の周りを回る処理
	void AroundTornado(float DeltaTime);
	//竜巻から離れた時の処理
	void LeftTornado(float DeltaTime);

	//速度の更新

	//移動の更新
	void UpdateMove(float DeltaTime);

private:

	APlayerChara* m_pPlayer;

	//周回前の目的地
	FVector m_TargrtLoc;

	//回転させる対象のベクター
	FVector m_RotVec;

	//移動方向
	FVector m_MoveDire;


	//移動速度
	float m_MoveSpeed;
	//移動速度の減衰率
	float m_SpeedAttenuate;


	//竜巻と重なっているか
	bool m_bOverlapTornado;

	//状態
	State m_State;

	float m_Speed;
	float m_Radius;

	float m_ZDire;

	bool m_bUp;

protected:
	//重なった対象
	UPrimitiveComponent* m_pOverlapComp;
};

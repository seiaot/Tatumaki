// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "PlayerChara.h"
#include "MyGameInstance.h"

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	if (InputComponent)
	{
		//入力バインド
		InputComponent->BindAxis("RightShoulder", this, &APlayerCamera::InputRightShoulder);
		InputComponent->BindAxis("LeftShoulder", this, &APlayerCamera::InputLeftShoulder);
		InputComponent->BindAxis("RightTrigger", this, &APlayerCamera::InputRightTrigger);
		InputComponent->BindAxis("LeftTrigger", this, &APlayerCamera::InputLeftTrigger);
	}
}

//カメラの更新
void APlayerCamera::UpdateCamera(float DeltaTime)
{
	//プレイヤーのアドレスを取得
	if (!m_pPlayer)
	{
		m_pPlayer = GetGameInstance<UMyGameInstance>()->GetPlayer();
		if (m_pPlayer)
		{
			m_pPlayer->SetCamera(m_pCamera);
		}
	}

	UpdateMove(DeltaTime);

	//距離の変更
	float AbsRadius = fabs(m_pPlayer->GetRadius());
	/*if (AbsRadius < 1500.0f)
	{
		AbsRadius = 150.0f;
	}*/

	m_pSpringArm->TargetArmLength = 300.0f + AbsRadius * 4.5f;

	//UE_LOG(LogTemp, Warning, TEXT("%f"), m_pSpringArm->TargetArmLength);
}

//移動の更新
void APlayerCamera::UpdateMove(float DeltaTime)
{
	if (m_pPlayer)
	{
		SetActorLocation(m_pPlayer->GetActorLocation());
	}
}

//ゲームパッド入力
void APlayerCamera::InputRightShoulder(float _value)
{
	if (_value != 0.0f)
	{
		AddActorWorldRotation(FRotator(0.0f, -_value, 0.0f));
	}
}
void APlayerCamera::InputLeftShoulder(float _value)
{
	if (_value != 0.0f)
	{
		AddActorWorldRotation(FRotator(0.0f, -_value, 0.0f));
	}
}
void APlayerCamera::InputRightTrigger(float _value)
{
	if (_value != 0.0f)
	{
		m_pSpringArm->TargetArmLength -= _value * 10.0f;
	}
}
void APlayerCamera::InputLeftTrigger(float _value)
{
	if (_value != 0.0f)
	{
		m_pSpringArm->TargetArmLength += _value * 10.0f;
	}
}
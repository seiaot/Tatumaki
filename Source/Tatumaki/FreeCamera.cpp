// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeCamera.h"

void AFreeCamera::BeginPlay()
{
	Super::BeginPlay();

	if (InputComponent)
	{
		//入力バインド
		InputComponent->BindAxis("D", this, &AFreeCamera::MoveRight);
		InputComponent->BindAxis("A", this, &AFreeCamera::MoveLeft);
		InputComponent->BindAxis("W", this, &AFreeCamera::MoveUp);
		InputComponent->BindAxis("S", this, &AFreeCamera::MoveDown);
		InputComponent->BindAxis("MouseMoveX", this, &AFreeCamera::InputMouseX);
		InputComponent->BindAxis("MouseMoveY", this, &AFreeCamera::InputMouseY);
	}
}

//移動の更新
void AFreeCamera::UpdateMove(float DeltaTime)
{
	if (!m_Move.IsZero())
	{
		//カメラの向きに合わせて移動
		SetActorLocation(GetActorLocation() + m_pCamera->GetRightVector() * m_Move.X * 5.0f + m_pCamera->GetForwardVector() * m_Move.Y * 5.0f);
		//次の入力に備える
		m_Move = FVector2D(0.0f, 0.0f);
	}
}
//回転の更新
void AFreeCamera::UpdateRotation(float DeltaTime)
{
	if (!m_CameraRot.IsZero())
	{
		//回転後のPitchの角度の絶対値
		float PitchAbs = fabs(m_pCamera->GetComponentRotation().Pitch + m_CameraRot.Pitch);
		//指定の方向にカメラを回転させる(Pitchには上下限あり)
		m_pCamera->AddLocalRotation(FRotator(PitchAbs < 85.0f ? m_CameraRot.Pitch : 0.0f, m_CameraRot.Yaw, 0.0f));
		//回転を記録
		FRotator CRot = m_pCamera->GetComponentRotation();
		//ロールを消す
		m_pCamera->SetWorldRotation(FRotator(CRot.Pitch, CRot.Yaw, 0.0f));
		//入力をリセット
		m_CameraRot = FRotator(0.0f, 0.0f, 0.0f);
	}
}

//移動 入力
void AFreeCamera::MoveRight(float _value)
{
	if (_value != 0.0f)
	{
		m_Move.X = _value;
	}
}
void AFreeCamera::MoveLeft(float _value)
{
	if (_value != 0.0f)
	{
		m_Move.X = _value;
	}
}
void AFreeCamera::MoveUp(float _value)
{
	if (_value != 0.0f)
	{
		m_Move.Y = _value;
	}
}
void AFreeCamera::MoveDown(float _value)
{
	if (_value != 0.0f)
	{
		m_Move.Y = _value;
	}
}
//マウスの入力(2D)
void AFreeCamera::InputMouseX(float _value)
{
	if (_value != 0.0f)
	{
		m_CameraRot.Yaw = _value;
	}
}
void AFreeCamera::InputMouseY(float _value)
{
	if (_value != 0.0f)
	{
		m_CameraRot.Pitch = _value;
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCamera.h"
#include "FreeCamera.generated.h"

/**
 * 
 */
UCLASS()
class TATUMAKI_API AFreeCamera : public AMyCamera
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;

private:
	//移動の更新
	void UpdateMove(float DeltaTime) override;
	//回転の更新
	void UpdateRotation(float DeltaTime) override;

private:
	//移動 入力
	void MoveRight(float _value);
	void MoveLeft(float _value);
	void MoveUp(float _value);
	void MoveDown(float _value);
	//マウスの入力(2D)
	void InputMouseX(float _value);
	void InputMouseY(float _value);

private:
	FVector2D m_Move;
	FRotator m_CameraRot;
	
};

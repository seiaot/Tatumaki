// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCamera.h"
#include "PlayerCamera.generated.h"

//前方宣言
class APlayerChara;

/**
 * 
 */
UCLASS()
class TATUMAKI_API APlayerCamera : public AMyCamera
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
	//カメラの更新
	void UpdateCamera(float DeltaTime);
	//移動の更新
	void UpdateMove(float DeltaTime) override;

private:
	//ゲームパッド入力
	void InputRightShoulder(float _value);
	void InputLeftShoulder(float _value);
	void InputRightTrigger(float _value);
	void InputLeftTrigger(float _value);
	
private:
	APlayerChara* m_pPlayer;	//プレイヤー

	float m_Rot;		//カメラの回転
	float m_Distance;	//カメラの距離
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerChara.generated.h"

//前方宣言
class ATornado;
class USphereComponent;
class UCameraComponent;

UCLASS()
class TATUMAKI_API APlayerChara : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//スティックの回転を更新
	void UpdateStickRot();

	//移動の中心点の更新
	void UpdateMovePivot(float DeltaTime);
	//移動更新
	void UpdateSpiral(float DeltaTime);
	//回転更新
	void UpdateRotation(float DeltaTime);
	//竜巻の更新
	void UpdateTornado(float DeltaTime);

public:
	//回転方向の取得
	int GetRotDire() const;
	//半径の取得
	float GetRadius() const;
	//回転速度の取得
	float GetSpeed() const;

	//カメラの登録
	void SetCamera(UCameraComponent* _pCamera);

private:
	//入力バインド【左スティック横方向】
	void LeftStickInputX(float value);
	//入力バインド【左スティック縦方向】
	void LeftStickInputY(float value);

	//入力バインド【右スティック横方向】
	void RightStickInputX(float value);
	//入力バインド【右スティック縦方向】
	void RightStickInputY(float value);

private:
	//竜巻
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tornado, meta = (AllowPrivateAccess = "true"))
	ATornado* m_pTornado;

	//追加のコリジョン
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USphereComponent* m_pRootCollision;

	//移動の中心位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Location, meta = (AllowPrivateAccess = "true"))
	FVector m_MovePivot;

	//最大回転速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RotSpeed, meta = (AllowPrivateAccess = "true"))
	float m_MaxRotSpeed;	
	//回転速度の減衰率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RotSpeed, meta = (AllowPrivateAccess = "true"))
	float m_RotAttenuate;	
	//速度に足す倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = RotSpeed, meta = (AllowPrivateAccess = "true"))
	float m_AddRotRate;	

	//最低半径
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Radius, meta = (AllowPrivateAccess = "true"))
	float m_MinRadius;
	//最大半径
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Radius, meta = (AllowPrivateAccess = "true"))
	float m_MaxRadius;
	//半径の減少
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Radius, meta = (AllowPrivateAccess = "true"))
	float m_RadiusAttenuate;
	//半径に足す倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Radius, meta = (AllowPrivateAccess = "true"))
	float m_AddRadiusRate;


	//上下移動の大きさ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown, meta = (AllowPrivateAccess = "true"))
	float m_UpDownSize;
	//上下移動の倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UpDown, meta = (AllowPrivateAccess = "true"))
	float m_UpDownRate;

	//中心の移動速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, meta = (AllowPrivateAccess = "true"))
	float m_MoveSpeed;

	//中心の移動速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Loc, meta = (AllowPrivateAccess = "true"))
	FVector m_RelativeLoc;
private:

	UCameraComponent* m_pCamera;	//カメラ
	
	FVector2f m_LeftStickInput2D;	//右スティック入力用
	FVector2f m_RightStickInput2D;	//左スティック入力用
	FVector2f m_PreInput;			//直前の入力

	FVector m_TarGetLoc;	//移動の目的位置

	float m_TotalDeg;		//合計回転角度
	float m_PreDeg;			//直前の角度
	float m_NowDeg;			//今動いた角度

	float m_RotSpeed;		//現在の回転速度

	float m_Radius;			//現在の半径

	float m_CosZ;			//Z軸の高さを作るのに使用する値

	int m_RotDire;		//回転方向(1で右、-1で左回転)

	float m_r;
	float m_RightInputTrigger;	//右トリガー入力用
};

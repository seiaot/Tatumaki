// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChara.h"
#include "Tornado.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "MyGameInstance.h"

// Sets default values
APlayerChara::APlayerChara()
	: m_pTornado(NULL)
	, m_pRootCollision(NULL)
	, m_LeftStickInput2D(FVector2f(0.0f, 0.0f))
	, m_RightStickInput2D(FVector2f(0.0f, 0.0f))
	, m_PreInput(FVector2f(0.0f, 0.0f))
	, m_TarGetLoc(FVector(1.0f, 0.0f, 0.0f))
	, m_TotalDeg(0.0f)
	, m_PreDeg(0.0f)
	, m_NowDeg(0.0f)
	, m_RotSpeed(1.0f)
	, m_Radius(0.0f)
	, m_CosZ(0.0f)
	, m_RotDire(1)
	, m_r(0.0f)
	, m_RightInputTrigger(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pRootCollision = CreateDefaultSubobject<USphereComponent>("m_RootComponent");
	if (m_pRootCollision)
	{
		//ルートにする
		RootComponent = m_pRootCollision;
	}

	//当たり判定を使わない
	GetCapsuleComponent()->SetCollisionProfileName("AllIgnore");
	GetCapsuleComponent()->Activate(false);
	GetMesh()->SetCollisionProfileName("AllIgnore");
	GetMesh()->Activate(false);
}

// Called when the game starts or when spawned
void APlayerChara::BeginPlay()
{
	Super::BeginPlay();

	//生成と同時にゲームインスタンスへ登録
	GetGameInstance<UMyGameInstance>()->SetPlayer(this);

	//最初はでかい
	m_Radius = 1000.0f;
}

// Called every frame
void APlayerChara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStickRot();

	UpdateMovePivot(DeltaTime);
	UpdateSpiral(DeltaTime);
	UpdateRotation(DeltaTime);
	UpdateTornado(DeltaTime);
}

// Called to bind functionality to input
void APlayerChara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//入力を繋げる
	//左スティック
	PlayerInputComponent->BindAxis("LeftStickInputX", this, &APlayerChara::LeftStickInputX);
	PlayerInputComponent->BindAxis("LeftStickInputY", this, &APlayerChara::LeftStickInputY);
	//右スティック
	PlayerInputComponent->BindAxis("RightStickInputX", this, &APlayerChara::RightStickInputX);
	PlayerInputComponent->BindAxis("RightStickInputY", this, &APlayerChara::RightStickInputY);
}

//移動の中心点の更新
void APlayerChara::UpdateMovePivot(float DeltaTime)
{
	//プレイヤー用のカメラがある時
	if (m_pCamera)
	{
		//移動方向前方
		FVector MoveDireForward = m_pCamera->GetForwardVector();
		MoveDireForward.Z = 0.0f;
		MoveDireForward.Normalize();
		//移動方向右
		FVector MoveDireRight = m_pCamera->GetRightVector();
		MoveDireRight.Z = 0.0f;
		MoveDireRight.Normalize();

		//移動速度
		float Speed = m_MoveSpeed * DeltaTime;

		AddActorWorldOffset(MoveDireRight * m_RightStickInput2D.X * Speed + MoveDireForward * m_RightStickInput2D.Y * Speed);
	}
	else
	{
		m_MovePivot.X += m_RightStickInput2D.X * DeltaTime * 100.0f;
		m_MovePivot.Y += m_RightStickInput2D.Y * DeltaTime * 100.0f;

		FVector2f move = m_RightStickInput2D * DeltaTime * 100.0f;

		AddActorWorldOffset(FVector(move.X, move.Y, 0.0f));
	}
}

//移動更新
void APlayerChara::UpdateSpiral(float DeltaTime)
{
	//毎フレーム速度減衰
	m_RotSpeed *= m_RotAttenuate;
	//現在の速度に回転速度の一部を加算
	m_RotSpeed += m_NowDeg * m_AddRotRate * DeltaTime;
	//回転速度の絶対値
	float AbsRotSpeed = fabs(m_RotSpeed);
	//最大速度に収める
	m_RotSpeed = ((AbsRotSpeed > m_MaxRotSpeed) ? m_MaxRotSpeed * (float)m_RotDire : m_RotSpeed);

	//半径の減少
	m_Radius *= m_RadiusAttenuate;
	//動けば広がる
	m_Radius += m_RotSpeed * m_AddRadiusRate;
	//半径の絶対値
	float AbsRadius = fabs(m_Radius);
	//最大半径に収める
	m_Radius = ((AbsRadius < m_MaxRadius) ? m_Radius : (m_Radius >= 0.0f) ? m_MaxRadius : -m_MaxRadius);

	//単位ベクトルを速度分回転させていく
	m_TarGetLoc = m_TarGetLoc.RotateAngleAxis(m_RotSpeed, FVector(0.0f, 0.0f, 1.0f));
	//移動の中心点から見た時の相対的なXYの位置を作成(半径は一定以下にならないようにする)
	AbsRadius = fabs(m_Radius);
	FVector RelativeLoc = m_TarGetLoc * ((AbsRadius > m_MinRadius) ? AbsRadius : m_MinRadius);
	//Z軸の高さの素を変更(cosを回すため符号は不要)
	m_CosZ += AbsRotSpeed * m_UpDownRate;
	//位置の適用
	GetCapsuleComponent()->SetWorldLocation(GetActorLocation() + FVector(RelativeLoc.X, RelativeLoc.Y, m_UpDownSize * cosf(FMath::DegreesToRadians(m_CosZ))));


	m_RelativeLoc = FVector(RelativeLoc.X, RelativeLoc.Y, m_UpDownSize * cosf(FMath::DegreesToRadians(m_CosZ)));
	//確認用
	//UE_LOG(LogTemp, Warning, TEXT("%f"), m_UpDownSize * cosf(FMath::DegreesToRadians(m_CosZ)));
	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), m_TarGetLoc.X, m_TarGetLoc.Y, m_TarGetLoc.Z);
}

//回転更新
void APlayerChara::UpdateRotation(float DeltaTime)
{
	//移動の中心から見た相対的位置
	FVector difLoc = GetMesh()->GetComponentLocation() - GetActorLocation();
	//相対角度(XYを入れ替え)
	float difRot = FMath::RadiansToDegrees(atan2(difLoc.Y, difLoc.X));
	//回転を適用(進行方向により反転)
	GetMesh()->SetWorldRotation(FRotator(0.0f, difRot + ((m_RotDire > 0) ? 0.0f : -180.0f), 0.0f));

	//確認用
	//UE_LOG(LogTemp, Warning, TEXT("%f"), difRot);
}


//竜巻の更新
void APlayerChara::UpdateTornado(float DeltaTime)
{
	//竜巻と回転の中心は同じ
	if (m_pTornado)
	{
		m_pTornado->SetActorLocation(GetActorLocation());
	}

	float f = fabs(m_Radius) * 0.05;

	m_pTornado->SetSize(FVector(f, f, f));

	m_r += m_RotSpeed * 2.5f;

	m_pTornado->RotationTornado(m_RotSpeed);
}

//スティックの回転を更新
void APlayerChara::UpdateStickRot()
{
	//入力がある時のみ更新
	if (!m_LeftStickInput2D.IsZero())
	{
		//入力の角度を取得。度数に変換
		float Rad = atan2(m_LeftStickInput2D.X, m_LeftStickInput2D.Y);
		float Deg = FMath::RadiansToDegrees(Rad);

		//ひとつ前で入力がないもしくは、角度が変化していないなら差の角度を求めない
		if (m_PreDeg && (Deg != m_PreDeg))
		{
			//直前と今回の差を得る
			float DegDif = Deg - m_PreDeg;

			//180の境目を超えるときの処理
			if (fabs(DegDif) > 180.0f)
			{
				//現在の角度の符号に合わせて符号が変更
				DegDif = ((Deg > 0) ? -360.0f : 360.0f) + Deg - m_PreDeg;
			}

			//合計角度に足す
			m_TotalDeg += DegDif;
			//差の符号により回転方向を判定
			m_RotDire = (DegDif >= 0.0f) ? 1 : -1;

			//確認用
			//UE_LOG(LogTemp, Warning, TEXT("PreDeg: %f , NowDeg: %f , Dif: %f , TortalDeg: %f , ClockWise: %i"), m_PreDeg, Deg, DegDif, m_TotalDeg,m_ClockWise);

			//次フレームで使用
			m_LeftStickInput2D = { 0.0f,0.0f };

			m_NowDeg = DegDif;
		}
		else
		{
			//今回は回転していない
			m_NowDeg = 0.0f;
		}
		m_PreDeg = Deg;
	}
	//入力が途切れたら直前の角度は存在しない
	else
	{
		m_PreDeg = 0.0f;
		m_NowDeg = 0.0f;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), m_NowDeg);
}

//回転方向の取得
int APlayerChara::GetRotDire() const
{
	return m_RotDire;
}

//半径の取得
float APlayerChara::GetRadius() const
{
	return m_Radius;
}

//回転速度の取得
float APlayerChara::GetSpeed() const
{
	return m_RotSpeed;
}

//カメラの登録
void APlayerChara::SetCamera(UCameraComponent* _pCamera)
{
	m_pCamera = _pCamera;
}

//入力バインド【左スティック横方向】
void APlayerChara::LeftStickInputX(float value)
{
	m_LeftStickInput2D.X = value;
}
//入力バインド【左スティック縦方向】
void APlayerChara::LeftStickInputY(float value)
{
	m_LeftStickInput2D.Y = value;
}

//入力バインド【右スティック横方向】
void APlayerChara::RightStickInputX(float value)
{
	m_RightStickInput2D.X = value;
}
//入力バインド【右スティック縦方向】
void APlayerChara::RightStickInputY(float value)
{
	m_RightStickInput2D.Y = value;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Offering.h"
#include "DrawDebugHelpers.h"
#include "PlayerChara.h"
#include "DestinationArea.h"
#include "MyGameInstance.h"

AOffering::AOffering()
	: m_State(State::Idle)
	, m_pPlayer(NULL)
	, m_TargrtLoc(0.0f,0.0f,0.0f)
	, m_RotVec(0.0f,0.0f,0.0f)
	, m_pOverlapComp(NULL)
	, m_ZDire(0.0f)
	, m_bUp(false)
	, m_Speed(120.0f)
	, m_bOverlapTornado(false)
{
	//コリジョンとメッシュの生成
	CreateCollisionAndMesh<UBoxComponent,UStaticMeshComponent>();

	//コリジョンの設定
	if (m_pCollision)
	{
		//物理挙動は行わない
		m_pCollision->SetSimulatePhysics(false);

		m_pCollision->SetCollisionProfileName("MyBlockAllDynamic");

		//タグ付け
		m_pCollision->ComponentTags.Add("Offering");
	}

	//衝突対象のタグを追加
	m_OverlapTargets.Add("Tornado");
}

void AOffering::BeginPlay()
{
	Super::BeginPlay();

	if (m_pCollision)
	{
		m_pCollision->SetSimulatePhysics(true);

	}

	m_ZDire = GetActorLocation().X;
}

void AOffering::OverlapBeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ぶつかった対象を保存
	m_pOverlapComp = OtherComp; 
	//状態を変更
	m_State = State::Go;

	m_pCollision->SetEnableGravity(false);

	//プレイヤーの情報を取得
	if (!m_pPlayer)
	{
		m_pPlayer = GetGameInstance<UMyGameInstance>()->GetPlayer();
	}
}

void AOffering::OverlapEndEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_pOverlapComp = NULL;
	m_State = State::fall;

	//重力
	m_pCollision->SetEnableGravity(true);
}

void AOffering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//状態による動きの変化
	switch ((int)m_State)
	{
	case 0:
		if (fabs(m_ZDire - GetActorLocation().X) < 500.0f)
		{
			//SetActorLocation(GetActorLocation() + FVector(50.0f, 0.0f, 50.0f));
		}
		break;

	//竜巻に向かうとき
	case 1:
		UpdateMove(DeltaTime);
		break;

	//竜巻の周りにいるとき
	case 2:
		AroundTornado(DeltaTime);
		break;

	case 3:
		LeftTornado(DeltaTime);
		break;
	default:
		break;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"),0.0f);
}

//竜巻に向かう処理
void AOffering::GoTornado(float DeltaTime)
{
	FVector ove = m_pOverlapComp->GetComponentLocation();
	FVector box = GetActorLocation();
	
	FVector dire = (ove - box).GetSafeNormal() * 200.0f * DeltaTime;
	AddActorWorldOffset(dire);

	if ((ove - box).Length() <= 100.0f)
	{
		m_State = State::Drift;

		m_Speed = float(FMath::Rand() % 201 + 100);
		m_Radius = float(FMath::Rand() % 401 + 100);
		m_MoveDire = (ove - box).GetSafeNormal() * m_Speed * DeltaTime;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f - %f,%f,%f"), dire.X, dire.Y, dire.Z, box.X, box.X, box.Z);
}

//竜巻の周りを回る処理
void AOffering::AroundTornado(float DeltaTime)
{
	FVector ove = m_pOverlapComp->GetComponentLocation();
	FVector box = GetActorLocation();

	FVector2D rotvec = FVector2D(ove.X - box.X, ove.Y - box.Y);

	UE_LOG(LogTemp, Warning, TEXT("Mukaujoutai"));

	if (rotvec.Length() <= m_Radius)
	{
		m_MoveDire = FVector(rotvec * -1.0f, 0.0f).GetSafeNormal();
		UpdateMove(DeltaTime);

		UE_LOG(LogTemp, Warning, TEXT("Hannkeiijou"));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Kaiten"));

		//DrawDebugLine(GetWorld(), box, box + rotvec.RightVector * 100.0f, FColor::Green, false, 1.0f);

		/*rotvec = rotvec.GetRotated(m_Speed * m_pPlayer->GetRotDire() * DeltaTime);
		if (box.Z > 800.0f)
		{
			m_ZDire = -50.0f;
		}
		else if (box.Z < 100.0f)
		{
			m_ZDire = 50.0f;
		}

		SetActorLocation(FVector(ove.X + rotvec.X, ove.Y + rotvec.Y,box.Z + m_ZDire * DeltaTime));*/

		rotvec = rotvec.GetRotated(((float)m_pPlayer->GetRotDire() == 1) ? -10.0f : 10.0f);
		m_MoveDire = FVector(rotvec.X, rotvec.Y, 0.0f).GetSafeNormal();

		UpdateMove(DeltaTime);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), box.Z);
}

//竜巻から離れた後
void AOffering::LeftTornado(float Deltatime)
{
	//正規化した進行方向
	//m_MoveDire = m_MoveDire.GetSafeNormal();

	if ((m_MoveDire - FVector(0.0f, 0.0f, -1.0f)).Length() >= 1.0f)
	{
		//
		//FVector2D DireRight(m_MoveDire.X, m_MoveDire.Y).GetRotated(90.0f))

		//m_MoveDire = m_MoveDire.RotateAngleAxis(90.0f * Deltatime, m_MoveDire.RotateAngleAxis(90.0f, FVector(0.0f, 0.0f, 1.0f)));
	}

	//SetActorLocation(GetActorLocation() + m_MoveDire * m_Speed * Deltatime);
	if (GetActorLocation().Z <= 0.0f + Cast<UBoxComponent>(m_pCollision)->GetScaledBoxExtent().X)
	{
		m_State = State::Idle;
		//物理挙動は行わない
		m_pCollision->SetSimulatePhysics(false);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), (m_MoveDire - FVector(0.0f, 0.0f, -1.0f)).Length());
}

//移動の更新
void AOffering::UpdateMove(float DeltaTime)
{
	//現在位置
	FVector NowLoc(GetActorLocation());
	//竜巻の位置
	FVector TorLoc(m_pOverlapComp->GetComponentLocation());

	//竜巻に向かうベクトル
	FVector Fornado(TorLoc - NowLoc);
	//竜巻との距離
	float Len = Fornado.Length();

	//のXYのみ
	FVector2D Fornado2D(Fornado.X,Fornado.Y);

	//プレイヤーの速度
	float PlayerSpeed(m_pPlayer->GetSpeed());

	//向かう方向の回転角度
	float RotDeg(0.0f);

	if (Len > 500.0f)
	{
		RotDeg = 0.0f;
	}
	else
	{
		//飛んでいく角度を生成
		RotDeg = 180.0f - Len / 500.0f * 180.0f;
	}

	//竜巻に向かうベクトルを回転方向に合わせて角度変更
	m_MoveDire = Fornado.GetSafeNormal().RotateAngleAxis((PlayerSpeed >= 0.0f) ? RotDeg * -1.0f : RotDeg, FVector(0.0f, 0.0f, 1.0f));

	//近さが一定以下なら

	//位置の更新
	//SetActorLocation(NowLoc + Fornado.GetSafeNormal() * fabs(m_pPlayer->GetSpeed()) * m_Speed * 5.0f * DeltaTime);

	SetActorLocation(NowLoc + m_MoveDire * fabs(m_pPlayer->GetSpeed()) * m_Speed * DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), Len);
	//UE_LOG(LogTemp, Warning, TEXT("TorLoc(%f,%f,%f) - NowLoc(%f,%f,%f)"), TorLoc.X, TorLoc.Y, TorLoc.Z, NowLoc.X,NowLoc.Y,NowLoc.Z);
}
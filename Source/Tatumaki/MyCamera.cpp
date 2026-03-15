// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamera.h"

// Sets default values
AMyCamera::AMyCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//スプリングアームの生成
	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_pSpringArm"));
	if (m_pSpringArm)
	{
		m_pSpringArm->SetupAttachment(RootComponent);

		//カメラのコリジョンテストを行うかを設定
		m_pSpringArm->bDoCollisionTest = false;
		//カメラ追従ラグを使うかを設定
		m_pSpringArm->bEnableCameraLag = true;
		//カメラ追従ラグの速度を設定
		m_pSpringArm->CameraLagSpeed = 10.0f;
		//カメラ回転ラグを使うかを設定
		m_pSpringArm->bEnableCameraRotationLag = true;
		//カメラ回転ラグの速度を設定
		m_pSpringArm->CameraRotationLagSpeed = 10.0f;
	}
	//カメラの生成
	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("m_pCamera"));
	if (m_pCamera && m_pSpringArm)
	{
		m_pCamera->SetupAttachment(m_pSpringArm, USpringArmComponent::SocketName);
	}
}

// Called when the game starts or when spawned
void AMyCamera::BeginPlay()
{
	Super::BeginPlay();

	//ここで入力を有効にする。コントローラー0の入力を使う。
	//Acyorの持つInputComponentに中身を入れているよう
	EnableInput(GetWorld()->GetFirstPlayerController());
	
}

// Called every frame
void AMyCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCamera(DeltaTime);
}

//カメラの更新
void AMyCamera::UpdateCamera(float DeltaTime)
{
	UpdateMove(DeltaTime);
	UpdateRotation(DeltaTime);
}

//移動の更新
void AMyCamera::UpdateMove(float DeltaTime)
{

}

//回転の更新
void AMyCamera::UpdateRotation(float DeltaTime)
{

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
	: m_HitTarget("0")
	, m_pBox(NULL)
	, m_pMesh(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//衝突判定の生成
	m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("m_pBox"));
	if (m_pBox != NULL)
	{
		RootComponent = m_pBox;

		//物理挙動は行わない
		m_pBox->SetSimulatePhysics(false);
		//空間と物理を有効。衝突時の物理挙動は無し
		m_pBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//オブジェクトタイプはワールドダイナミック
		m_pBox->SetCollisionObjectType(ECC_WorldDynamic);
		//コリジョンイベントの有効化
		m_pBox->SetGenerateOverlapEvents(true);
		m_pBox->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
		m_pBox->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

		//UE_LOG(LogTemp, Warning, TEXT("hehe"));
	}

	//メッシュの生成
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pMesh"));
	if (m_pMesh != NULL)
	{
		//ルートにアタッチ
		m_pMesh->SetupAttachment(RootComponent);
		//衝突判定は持たない
		m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), 0.0f);
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherComp->ComponentHasTag(m_HitTarget)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("LapBegin"));
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherComp->ComponentHasTag(m_HitTarget)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("LapEnd"));
}

//消滅
void AItem::DestroyAll()
{
	m_pMesh->DestroyComponent();
	m_pBox->DestroyComponent();
	Destroy();
}
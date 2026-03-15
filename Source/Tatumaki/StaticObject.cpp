// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticObject.h"

// Sets default values
AStaticObject::AStaticObject()
	: m_OverlapTarget("0")
	, m_pCollision(NULL)
	, m_pMesh(NULL)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AStaticObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStaticObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), 0.0f);
}

void AStaticObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}

void AStaticObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

//Á–Å
void AStaticObject::DestroyAll()
{
	m_pMesh->DestroyComponent();
	m_pCollision->DestroyComponent();
	Destroy();
}

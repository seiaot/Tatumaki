// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonBody.h"
#include "Components/SphereComponent.h"

ADragonBody::ADragonBody()
{
	CreateCollisionAndMesh<USphereComponent, UStaticMeshComponent>();

	m_pCollision->SetCollisionProfileName("AllIgnore");
	m_pMesh->SetCollisionProfileName("AllIgnore");
	m_pMesh->Activate(false);
	m_pCollision->Activate(false);
}


void ADragonBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADragonBody::BeginPlay()
{
	Super::BeginPlay();
}

void ADragonBody::SetPlayer(APlayerChara* ppPlayer)
{
	m_pPLayer = ppPlayer;
}
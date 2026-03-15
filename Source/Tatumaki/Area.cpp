// Fill out your copyright notice in the Description page of Project Settings.

#include "Area.h"
#include "Components/BoxComponent.h"

AArea::AArea()
{
	CreateCollisionAndMesh<UBoxComponent, UStaticMeshComponent>();

	if (m_pCollision)
	{
		m_pCollision->SetSimulatePhysics(false);
		m_pCollision->SetCollisionProfileName("MyOverlapAllStatic");
		m_pCollision->SetEnableGravity(false);
	}
}
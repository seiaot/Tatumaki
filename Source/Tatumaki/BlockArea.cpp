// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockArea.h"

ABlockArea::ABlockArea()
{
	m_pCollision->SetCollisionProfileName("MyBlockAllStatic");
}
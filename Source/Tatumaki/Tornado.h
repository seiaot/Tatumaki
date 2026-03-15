// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "Tornado.generated.h"

UCLASS()
class TATUMAKI_API ATornado : public AMyActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATornado();

public:
	//大きさ変更
	void SetSize(FVector _size);
	//回転
	void RotationTornado(float rot);


private:
	//スタティックメッシュ中層
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* m_pMesh_2;

	//スタティックメッシュ外層
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* m_pMesh_3;

private:
	float m_Rot;
};

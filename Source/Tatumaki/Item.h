// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Item.generated.h"

UCLASS()
class TATUMAKI_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//オーバーラップ時
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//!オーバーラップ時
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	//消滅
	void DestroyAll();

protected:
	//衝突時処理を行う対象のタグ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target, meta = (AllowPrivateAccess = "true"));
	FName m_HitTarget;

	//衝突判定
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"));
	UBoxComponent* m_pBox;
	
	//スタティックメッシュ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shape, meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* m_pMesh;
};

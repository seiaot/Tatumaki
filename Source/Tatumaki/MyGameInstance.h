// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

//前方宣言
class APlayerChara;

/**
 * 
 */
UCLASS()
class TATUMAKI_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	//プレイヤーの登録・取得
	void SetPlayer(APlayerChara* _pPlayer);
	APlayerChara* GetPlayer() const;

	//運んだ供物の数の登録・取得
	UFUNCTION(BlueprintCallable)
	void SetDesOffering(int _RiceNum,int _Fruit);

	int GetDefRice() const;
	int GetDefFruit() const;
	
public:
	APlayerChara* pPlayerChara;	//プレイヤー

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Num, meta = (AllowPrivateAccess = "true"));
	int m_RiceNum;	//米俵の数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Num, meta = (AllowPrivateAccess = "true"));
	int m_Fruit;	//果物の数
};

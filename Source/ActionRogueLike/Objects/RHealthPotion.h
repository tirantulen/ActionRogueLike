// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RInteractuableObject.h"
#include "RHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARHealthPotion : public ARInteractuableObject
{
	GENERATED_BODY()

	protected:
	//Functions
	virtual void OnUse(APawn* PawnInstigator) override;
	
};

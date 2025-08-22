// Fill out your copyright notice in the Description page of Project Settings.


#include "RHealthPotion.h"

#include "ActionRogueLike/Interfaces/RAttributesInterface.h"


class URAttributesInterface;

void ARHealthPotion::OnUse(APawn* PawnInstigator)
{
	//Super::OnUse(PawnInstigator);
	if (PawnInstigator->Implements<URAttributesInterface>()) IRAttributesInterface::Execute_ChangeHealthValue(PawnInstigator, 50.0f);
}

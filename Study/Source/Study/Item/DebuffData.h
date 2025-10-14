// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebuffData.generated.h"

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
    None UMETA(DisplayName = "None"),
    Slow UMETA(DisplayName = "Slow"),
    ReverseController UMETA(DisplayName = "Reverse Controller"),
    Blind UMETA(DisplayName = "Blind")
};


//class STUDY_API DebuffData
//{
//public:
//	DebuffData();
//	~DebuffData();
//};

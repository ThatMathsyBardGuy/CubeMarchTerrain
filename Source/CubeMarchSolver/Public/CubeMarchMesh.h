#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "CubeMarchMesh.generated.h"

UCLASS()
class UCubeMarchMesh : public UProceduralMeshComponent
{
	GENERATED_BODY()
public:
	UCubeMarchMesh(const FObjectInitializer& ObjectInitializer);
};
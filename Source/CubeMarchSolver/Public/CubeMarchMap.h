#pragma once

#include "Delegates/Delegate.h"
#include "Math/Vector.h"
#include "Delegates/DelegateCombinations.h"

#include "CubeMarchMap.generated.h"

struct CubeMarchNode {
	FVector Coord;
	float Weight;
};

class UObject;

DECLARE_DELEGATE_RetVal_OneParam(float, FOnGenerateCubeNodeWeight, const FVector&);

//@TODO ETHAN This doesn't feel like a "component", maybe I'm wrong though
UCLASS(BlueprintType)
class UCubeMarchMap : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	//UCubeMarchMap();
	//UCubeMarchMap(const int xsize, const int ysize, const int zsize);
	//~UCubeMarchMap() {};

	//UCubeMarchMap(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable) void SolveMesh();

	UFUNCTION(BlueprintCallable) void InitialiseWeights();

	UFUNCTION(BlueprintCallable) const TArray<FVector>& GetVertices()
	{
		return Vertices;
	}

	UFUNCTION(BlueprintCallable) const TArray<int>& GetTriangles()
	{
		return Triangles;
	}

protected:
	UPROPERTY() int XSize;
	UPROPERTY() int YSize;
	UPROPERTY() int ZSize;

	UPROPERTY() float SurfaceValue;

	FOnGenerateCubeNodeWeight NoiseFunction;

	TArray<CubeMarchNode> Nodes;

	TArray<FVector> Vertices;
	TArray<int> Triangles;	//Hate this name, but that's what ProceduralMeshComponent calls it
};

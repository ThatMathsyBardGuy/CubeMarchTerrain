#pragma once

#include "Delegates/Delegate.h"
#include "Math/Vector.h"
#include "Delegates/DelegateCombinations.h"

struct CubeMarchNode {
	FVector Coord;
	float Weight;
};

DECLARE_DELEGATE_RetVal_OneParam(float, FOnGenerateCubeNodeWeight, FVector&);

//@TODO ETHAN Are both these API Tags needed???
CUBEMARCHSOLVER_API class CubeMarchMap
{
public:
	CUBEMARCHSOLVER_API CubeMarchMap();
	CubeMarchMap(int xsize, int ysize, int zsize);
	~CubeMarchMap() {};

	TArray<FVector> SolveMesh();

	void InitialiseWeights();

protected:
	const int XSize;
	const int YSize;
	const int ZSize;

	float SurfaceValue;

	FOnGenerateCubeNodeWeight NoiseFunction;

	TArray<CubeMarchNode> Nodes;
};

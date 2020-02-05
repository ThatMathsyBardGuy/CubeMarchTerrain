#pragma once

#include <vector>

#include "Mesh.h"

namespace cubemarch {

	struct CubeMarchNode {
		int x;
		int y;
		int z;

		float weight;
	};

	class CubeMarchMap
	{
	public:
		CubeMarchMap();
		CubeMarchMap(int xsize, int ysize, int zsize);
		~CubeMarchMap() {};

		CubeMarchNode* GetNodes() { return m_Nodes; }

		int GetNumOfNodes() { return m_XSize * m_YSize * m_ZSize; }

		int GetXSize() { return m_XSize; }
		int GetYSize() { return m_YSize; }
		int GetZSize() { return m_ZSize; }
		
		bool SetNodeValues(float values[], int size);

		rendering::Mesh* GenerateMesh(float surfacevalue);

	protected:
		

		const int m_XSize;
		const int m_YSize;
		const int m_ZSize;

		CubeMarchNode* m_Nodes;
	};
}

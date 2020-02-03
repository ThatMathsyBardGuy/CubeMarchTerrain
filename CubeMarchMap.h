#pragma once

#include <vector>
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

		bool SetNodeValues(float values[], int size);

	protected:
		const int m_XSize;
		const int m_YSize;
		const int m_ZSize;

		CubeMarchNode* m_Nodes;
	};
}

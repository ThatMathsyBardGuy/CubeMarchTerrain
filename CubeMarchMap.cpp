#include "CubeMarchMap.h"

namespace cubemarch {
	CubeMarchMap::CubeMarchMap() : CubeMarchMap(10, 10, 10) {
		
	}

	CubeMarchMap::CubeMarchMap(int x, int y, int z) : m_XSize(x), m_YSize(y), m_ZSize(z) {
		m_Nodes = new CubeMarchNode[x*y*z];
		for (int xx = 0; xx < x; xx++) {
			for (int yy = 0; yy < y; yy++) {
				for (int zz = 0; zz < z; zz++) {
					m_Nodes[xx + yy * x + zz * x * y] = CubeMarchNode({ xx, yy, zz, 0.0f });
				}
			}
		}
	}

	bool CubeMarchMap::SetNodeValues(float values[], int size) {
		if (size != m_XSize * m_YSize * m_ZSize) return false;
		for (int i = 0; i < size; i++) {
			m_Nodes[i].weight = values[i];
		}
	}
}
#pragma once

#include <vector>

#include "Mesh.h"

#define MAX_TRIANGLES 1000
#define MAX_NODES 100

namespace rendering {
	class ComputeShader;
}

namespace cubemarch {

	struct CubeMarchNode {
		int x;			
		int y;			
		int z;			

		float weight;	
	};

	struct Point {
		float x;
		float y;
		float z;
	};

	struct Triangle {
		Point points[3];
	};

	struct CubeMarchSSBO {
		int XSize;								
		int YSize;								
		int ZSize;								
		float SurfaceValue;						
		CubeMarchNode Nodes[MAX_NODES];			
		int TriIndex;							
		Triangle Tris[MAX_TRIANGLES];		
	};

	class CubeMarchMap {
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

		void GenerateMesh(float surfacevalue, rendering::Mesh& mesh, bool usegpu);

		void GenerateMeshCPU(float surfacevalue, rendering::Mesh& mesh);
		void GenerateMeshGPU(float surfacevalue, rendering::Mesh& mesh);

	protected:
		const int m_XSize;
		const int m_YSize;
		const int m_ZSize;

		CubeMarchNode* m_Nodes;

		rendering::ComputeShader* m_ComputeShader;

	    CubeMarchSSBO m_SSBOData;
	};
}

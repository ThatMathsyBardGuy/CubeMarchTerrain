#include "CubeMarchNodeVisualiser.h"

#include <algorithm>

namespace cubemarch {
	CubeMarchNodeVisualiser::CubeMarchNodeVisualiser(CubeMarchMap* map, float surfacelevel, std::string name) : m_Map(map), rendering::RenderObject(rendering::Mesh::GenerateQuad(), glm::mat4(1.0f), name) {
		SetSurfaceLevel(surfacelevel);
		UpdateNodeMesh();
	}

	void CubeMarchNodeVisualiser::SetSurfaceLevel(float surfacelevel) {
		m_SurfaceLevel = std::min(surfacelevel, 1.0f);
		m_SurfaceLevel = std::max(m_SurfaceLevel, 0.0f);
	}

	void CubeMarchNodeVisualiser::UpdateNodeMesh() {
		
	}

	
}
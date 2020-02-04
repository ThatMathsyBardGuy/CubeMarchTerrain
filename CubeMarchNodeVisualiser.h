#pragma once
#include "RenderObject.h"
#include "CubeMarchMap.h"
namespace cubemarch {
	class CubeMarchNodeVisualiser : public rendering::RenderObject
	{
	public:
		CubeMarchNodeVisualiser(CubeMarchMap* map, float surfacelevel = 0.0f, std::string name = "Unnamed CubeMarch Visualiser");

		void SetSurfaceLevel(float surfacelevel);

		void UpdateNodeMesh();

	//	virtual void Draw();
	protected:

		CubeMarchMap* m_Map;
		float m_SurfaceLevel;
	};
}


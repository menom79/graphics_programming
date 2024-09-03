/**
 * ============================================================================
 *  Name        : Terrain.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB5
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "Terrain.h"


Terrain::Terrain(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material) :
	GeometryNode(geometry, material),
	m_uTexture(0)
{
}


void Terrain::Render(IRenderer& renderer, GLuint program)
{
	if (m_pGeometry)
	{
		// disable the alpha blending
		glDisable(GL_BLEND);

		if (m_uTexture)
		{
			// set the texture for the program (slot 0)
			renderer.SetTexture(program, m_uTexture, 0, "texture01");
		}
	}

	GeometryNode::Render(renderer, program);
}



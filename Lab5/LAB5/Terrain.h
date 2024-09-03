/**
 * ============================================================================
 *  Name        : Terrain.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB5
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#pragma once

#include "../core/include/GeometryNode.h"

class Terrain : public GeometryNode
{
public:
	Terrain(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material);

	/**
	 * Draw
	 * virtual drawing method of the game object
	 * @param pRenderer pointer to renderer
	 */
	void Render(IRenderer& renderer, GLuint program) override;

	inline void SetTexture(GLuint uTexture) { m_uTexture = uTexture; }
	inline GLuint GetTexture() const { return m_uTexture; }

protected:
	GLuint						m_uTexture;
};


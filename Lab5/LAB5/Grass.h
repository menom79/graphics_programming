/**
 * ============================================================================
 *  Name        : Grass.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB5
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/


#pragma once
#include "Terrain.h"

class Grass : public Terrain
{
public:
    Grass(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material);

	/*
	 * Update
	 * update node and its children
	 * @param frametime frame delta time
	 */
	void Update(float frametime) override;

	/**
	 * Draw
	 * virtual drawing method of the game object
	 * @param pRenderer pointer to renderer
	 */
	void Render(IRenderer& renderer, GLuint program) override;

private:
	// TODO: member for the swing animation
};


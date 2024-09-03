/**
 * ============================================================================
 *  Name        : Grass.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB5
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "Grass.h"


Grass::Grass(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material) :
	Terrain(geometry, material)
{
}


void Grass::Update(float frametime)
{
    // TODO: grass swing animation

    Terrain::Update(frametime);
}


void Grass::Render(IRenderer& renderer, GLuint program)
{
	// TODO: set the alpha blending for the grass texture

	Terrain::Render(renderer, program);
}



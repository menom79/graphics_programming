/**
 * ============================================================================
 *  Name        : TankPiece.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : Piece of a tank, LAB2
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#pragma once

#include "../core/include/GeometryNode.h"

class TankPiece : public GeometryNode
{
public:
	TankPiece(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material);

protected:
};


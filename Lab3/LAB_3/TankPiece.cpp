/**
 * ============================================================================
 *  Name        : TankPiece.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : Piece of a tank, LAB2
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "TankPiece.h"


TankPiece::TankPiece(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material) :
	GeometryNode(geometry, material)
{
}



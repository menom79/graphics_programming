/**
 * ============================================================================
 *  Name        : Material.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : simple material
 *  Version     : 1.00
 *	Author      : Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#pragma once

#include "../include/OpenGLRenderer.h"


struct Material
{
	Material();

	void SetToProgram(GLuint program);

	glm::vec4		m_cAmbient;
	glm::vec4		m_cDiffuse;
	glm::vec4		m_cSpecular;
	glm::vec4		m_cEmissive;

	float			m_fSpecularPower;
};


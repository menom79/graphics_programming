/**
 * ============================================================================
 *  Name        : Material.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : simple material
 *  Version     : 1.00
 *	Author      : Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "../include/Material.h"


Material::Material() :
	m_cAmbient(0.1f, 0.1f, 0.1f, 1.0f),
	m_cDiffuse(1.0f, 1.0f, 1.0f, 1.0f),
	m_cSpecular(1.0f, 1.0f, 1.0f, 1.0f),
	m_cEmissive(0.0f, 0.0f, 0.0f, 0.0f),
	m_fSpecularPower(50.0f)
{
}


void Material::SetToProgram(GLuint program)
{
	GLint location = glGetUniformLocation(program, "materialAmbient");
	if (location != -1)
	{
		glUniform4f(location, m_cAmbient.r, m_cAmbient.g, m_cAmbient.b, m_cAmbient.a);
	}

	location = glGetUniformLocation(program, "materialDiffuse");
	if (location != -1)
	{
		glUniform4f(location, m_cDiffuse.r, m_cDiffuse.g, m_cDiffuse.b, m_cDiffuse.a);
	}

	location = glGetUniformLocation(program, "materialSpecular");
	if (location != -1)
	{
		glUniform4f(location, m_cSpecular.r, m_cSpecular.g, m_cSpecular.b, m_cSpecular.a);
	}

	location = glGetUniformLocation(program, "materialEmissive");
	if (location != -1)
	{
		glUniform4f(location, m_cEmissive.r, m_cEmissive.g, m_cEmissive.b, m_cEmissive.a);
	}

	location = glGetUniformLocation(program, "specularPower");
	if (location != -1)
	{
		glUniform1f(location, m_fSpecularPower);
	}
}



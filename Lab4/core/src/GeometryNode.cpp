/**
 * ============================================================================
 *  Name        : GeometryNode.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : Scenegraph node capable of rendering geometry object with 
 *                material.
 *  Version     : 1.00
 *	Author      : Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "../include/GeometryNode.h"
#include "../include/Geometry.h"
#include "../include/Material.h"


GeometryNode::GeometryNode(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material) :
	m_pGeometry(geometry),
	m_pMaterial(material)
{
}

void GeometryNode::Render(IRenderer& renderer, GLuint program)
{
	if (m_pGeometry)
	{
		m_pGeometry->SetAttribs(program);

		// set model matrix to shader uniform
		glm::mat4 worldMatrix = GetWorldMatrix();
		GLint location = glGetUniformLocation(program, "modelMatrix");
		glUniformMatrix4fv(location, 1, GL_FALSE, &worldMatrix[0][0]);

		// set model-view-projection matrix to shader uniform
		glm::mat4 modelViewProjectionMatrix(renderer.GetProjectionMatrix() * renderer.GetViewMatrix() * worldMatrix);
		location = glGetUniformLocation(program, "modelViewProjectionMatrix");
		glUniformMatrix4fv(location, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

		// set the normal matrix
		glm::mat3 normalMatrix(glm::transpose(glm::inverse(worldMatrix)));
		location = glGetUniformLocation(program, "normalMatrix");
		glUniformMatrix3fv(location, 1, GL_FALSE, &normalMatrix[0][0]);

		if (m_pMaterial)
		{
			m_pMaterial->SetToProgram(program);
		}

		m_pGeometry->Draw(renderer);
	}

	Node::Render(renderer, program);
}


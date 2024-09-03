/**
 * ============================================================================
 *  Name        : Node.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : SceneGraph node base class
 *  Version     : 1.00
 *	Author      : Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "../include/Node.h"

Node::Node() :
	m_mModel(1.0f),
	m_pParent(nullptr),
	m_vRotationAxis(0.0f, 0.0f, -1.0f),
	m_fRotationAngle(0.0f),
	m_fRotationSpeed(0.0f),
	m_vVelocity(0.0f, 0.0f, 0.0f),
	m_fRadius(1.0f)
{
}


Node::~Node()
{
}


void Node::AddNode(std::shared_ptr<Node> node)
{
	// link new child parent
	node->m_pParent = this;

	// add to child array
	m_arrNodes.push_back(node);
}


void Node::Update(float frametime)
{
	// update position per velocity
	glm::vec3 pos = GetPos();
	pos += m_vVelocity * frametime;

	// update rotations
	if (fabsf(m_fRotationSpeed) > 0.000001f)
	{
		m_mModel = glm::rotate(glm::mat4(1.0f), m_fRotationAngle, m_vRotationAxis);

		m_fRotationAngle += m_fRotationSpeed * frametime;
		while (m_fRotationAngle > glm::two_pi<float>())
		{
			m_fRotationAngle -= glm::two_pi<float>();
		}
		while (m_fRotationAngle < -glm::two_pi<float>())
		{
			m_fRotationAngle += glm::two_pi<float>();
		}
	}

	// set updated position back to the model matrix
	m_mModel[3][0] = pos.x;
	m_mModel[3][1] = pos.y;
	m_mModel[3][2] = pos.z;

	// update child nodes
	for (auto& node : m_arrNodes)
	{
		node->Update(frametime);
	}
}


void Node::Render(IRenderer& renderer, GLuint program)
{
	for (auto& node : m_arrNodes)
	{
		node->Render(renderer, program);
	}
}


Node* Node::FindNode(const std::string_view name)
{
	if (m_strName == name)
	{
		return this;
	}

	for (const auto& node : m_arrNodes)
	{
		auto ret = node->FindNode(name);
		if (ret) return ret;
	}

	return nullptr;
}


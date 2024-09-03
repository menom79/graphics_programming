/**
 * ============================================================================
 *  Name        : TheApp.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB2
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "TheApp.h"


// constructor, init members
CTheApp::CTheApp() :
	m_uVertexShader(0),
	m_uFragmentShader(0),
	m_uProgram(0),
	m_fAngle(0.0f),
	m_bEnableRotation(false)
{
	// seed the random number generator
	RandSeed();
}


bool CTheApp::OnCreate()
{
	// OnCreate is called by the application when window and graphics initialization is complete
	m_uVertexShader = GetOpenGLRenderer()->CreateVertexShaderFromFile("triangleshader.vs");
	m_uFragmentShader = GetOpenGLRenderer()->CreateFragmentShaderFromFile("triangleshader.fs");
	m_uProgram = GetOpenGLRenderer()->CreateProgram(m_uVertexShader, m_uFragmentShader);
	if (!m_uVertexShader || !m_uFragmentShader || !m_uProgram)
	{
		return false;
	}

		constexpr float hw = 0.55f;
		m_Quad[0] = VERTEX(-hw, hw, 0.0f);
		m_Quad[1] = VERTEX(hw, hw, 0.0f);
		m_Quad[2] = VERTEX(hw, -hw, 0.0f);

	// added color points
		m_Quad[0].setcolor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_Quad[1].setcolor({ 0.0f, 1.0f, 0.0f, 1.0f });
		m_Quad[2].setcolor({ 0.0f, 0.0f, 1.0f, 1.0f });

	// setup our view and projection matrices
		m_mView = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 2.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		m_mProjection = glm::perspective(1.51f, GetAspect(), 0.1f, 500.0f);

		return true;

	return true;
}


void CTheApp::OnDestroy()
{
	// app is about to close, clear all resources
	glDeleteProgram(m_uProgram);
	glDeleteShader(m_uFragmentShader);
	glDeleteShader(m_uVertexShader);

	m_uVertexShader = 0;
	m_uFragmentShader = 0;
	m_uProgram = 0;
}




void CTheApp::OnUpdate(float fFrametime)
{

	/*if (m_bEnableRotation)
	{
		m_pMaterial1->SetToProgram(m_uProgram);
	}
	else
	{
		m_pMaterial->SetToProgram(m_uProgram);
	}
	
	void CTheApp::m_bEnableRotation()
{
	const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_fAngle, glm::vec3(0.0f, 0.0f, -1.0f));
	m_mModel = rotation;
	m_fAngle += fFrametime;		
}*/

	if (m_bEnableRotation)
	{
		const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_fAngle, glm::vec3(0.0f, 0.0f, -1.0f));
		m_mModel = rotation;
		m_fAngle += fFrametime;
	}
	else
	{
		const glm::mat4 rotation = glm::rotate(glm::mat4(0.0f), m_fAngle, glm::vec3(0.0f, 0.0f, 0.0f));
	}

}


void CTheApp::OnDraw(IRenderer& pRenderer)
{
	// clear color, depth and stencil buffers
	pRenderer.Clear(0.2f, 0.2f, 0.2f, 1.0f);

	// setup the rendering program
	glUseProgram(m_uProgram);

	//find the locations of position
	GLint position = glGetAttribLocation(m_uProgram, "position");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, VERTEX::GetStride(), m_Quad);

	//get color
	position = glGetAttribLocation(m_uProgram, "color");
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, VERTEX::GetStride(), (float*)m_Quad + 3);

	//set model-view-projection matrix to shader uniform
	glm::mat4 modelViewProjectionMatrix(m_mProjection * m_mView * m_mModel);
	GLint mvp = glGetUniformLocation(m_uProgram, "mvpMatrix");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

	// draw the quad
	glDrawArrays(GL_TRIANGLES, 0, 3);

}


void CTheApp::OnScreenSizeChanged(uint32_t uWidthPixels, uint32_t uHeightPixels)
{
}


bool CTheApp::OnMouseBegin(int iButtonIndex, const glm::vec2& vPoint)
{
	//Debug("OnMouseBegin " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
}


bool CTheApp::OnMouseDrag(int iButtonIndex, const glm::vec2& vPoint)
{
	//Debug("OnMouseDrag " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
}


bool CTheApp::OnMouseEnd(int iButtonIndex, const glm::vec2& vPoint)
{
	//Debug("OnMouseEnd " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
}

bool CTheApp::OnKeyDown(uint32_t uKeyCode)
{
	if (uKeyCode == KEY_ESC)
	{
		Close();
		return true;
	}
	else if (uKeyCode == KEY_SPACE)
	{
		m_bEnableRotation = !m_bEnableRotation;
	}

	return false;
}
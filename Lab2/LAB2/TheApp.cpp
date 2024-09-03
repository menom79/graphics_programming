/**
 * ============================================================================
 *  Name        : TheApp.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB3
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "TheApp.h"


// constructor, init members
TheApp::TheApp() :
	m_uVertexShader(0),
	m_uFragmentShader(0),
	m_uProgram(0),
	m_bUpsidedown(false)
{
	// seed the random number generator
	RandSeed();
}


bool TheApp::OnCreate()
{
	// OnCreate is called by the application when window and graphics initialization is complete
	auto renderer = GetOpenGLRenderer();
	m_uVertexShader = renderer->CreateVertexShaderFromFile("triangleshader.vs");
	m_uFragmentShader = renderer->CreateFragmentShaderFromFile("triangleshader.fs");
	m_uProgram = renderer->CreateProgram(m_uVertexShader, m_uFragmentShader);
	m_uTexture = GetOpenGLRenderer()->CreateTexture("leaf.png");

	// TODO: load a leaf.png texture (done)

	if (!m_uVertexShader || !m_uFragmentShader || !m_uProgram)
	{
		return false;
	}

	// TODO: add texture mapping coordinates to triangle
	
	// oikea nurkka 1.0f, 1.0f
	m_Triangle[0] = TRIANGLEVERTEX(0.5f, -0.5f, 0.0f, 1.0f, 1.0f);
	//vasen nurkka 0.0f, 0.0f
	m_Triangle[1] = TRIANGLEVERTEX(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);
	//ylänurkka 1.0f, 0.0f
	m_Triangle[2] = TRIANGLEVERTEX( 0.0f,  0.5f, 0.0f, 0.5f, 0.0f);

	return true;
}


void TheApp::OnDestroy()
{
	// app is about to close, clear all resources
	glDeleteProgram(m_uProgram);
	glDeleteShader(m_uFragmentShader);
	glDeleteShader(m_uVertexShader);

	// TODO: delete loaded texture

	m_uTexture = 0;
	m_uVertexShader = 0;
	m_uFragmentShader = 0;
	m_uProgram = 0;
}


void TheApp::OnUpdate(float frametime)
{
}


void TheApp::OnDraw(IRenderer& renderer)
{
	// clear color, depth and stencil buffers
	renderer.Clear(0.2f, 0.2f, 0.2f, 1.0f);

	// setup the rendering program
	glUseProgram(m_uProgram);

	// get the vertex attribute locations
	GLint position = glGetAttribLocation(m_uProgram, "position");

	// set the vertex position
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, TRIANGLEVERTEX::GetStride(), m_Triangle);

	// TODO: set the texture coordinate attribute to the program

	GLint uv = glGetAttribLocation(m_uProgram, "uv");
	glEnableVertexAttribArray(uv);
	glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, TRIANGLEVERTEX::GetStride(), (float*)m_Triangle + 3);

	GLint location = glGetUniformLocation(m_uProgram, "texture01");
	glUniform1i(location, 0);

	// set the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	GLint mvp = glGetUniformLocation(m_uProgram, "modelMatrix");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, &model[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (m_bUpsidedown)
	{
		//oikea nurkka 1.0f, 1.0f
		m_Triangle[0] = TRIANGLEVERTEX(0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
		//vasen nurkka 0.0f, 1.0f
		m_Triangle[1] = TRIANGLEVERTEX(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f);
		//ylänurkka 1.0f, 0.0f
		m_Triangle[2] = TRIANGLEVERTEX(0.0f, 0.5f, 0.0f, 0.5f, 1.0f);
	}
	else
	{
		//oikea nurkka 1.0f, 1.0f tu=x kirdinaatti ja tv=y koodinaatti
		m_Triangle[0] = TRIANGLEVERTEX(0.5f, -0.5f, 0.0f, 1.0f, 1.0f);
		//vasen nurkka 0.0f, 1.0f
		m_Triangle[1] = TRIANGLEVERTEX(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);
		//ylänurkka 1.0f, 0.0f
		m_Triangle[2] = TRIANGLEVERTEX(0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	}
}


void TheApp::OnScreenSizeChanged(uint32_t widthPixels, uint32_t heightPixels)
{
}


bool TheApp::OnKeyDown(uint32_t keyCode)
{
	// TODO: modify texture coordinates when user presses space
	if (keyCode == KEY_ESC)
	{
		Close();
		return true;
	}
	else if (keyCode == KEY_SPACE)
	{
		m_bUpsidedown = !m_bUpsidedown;
	}

	return false;
}


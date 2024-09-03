/**
 * ============================================================================
 *  Name        : TheApp.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB5
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#include "TheApp.h"


// constructor, init members
TheApp::TheApp() :
	m_uVertexShader(0),
	m_uFragmentShader(0),
	m_uProgram(0)
{
	// seed the random number generator
	RandSeed();
}


bool TheApp::OnCreate()
{
	// OnCreate is called by the application when window and graphics initialization is complete
	auto renderer = GetOpenGLRenderer();
	m_uVertexShader = renderer->CreateVertexShaderFromFile("phongshader.vs");
	m_uFragmentShader = renderer->CreateFragmentShaderFromFile("phongshader.fs");
	m_uProgram = renderer->CreateProgram(m_uVertexShader, m_uFragmentShader);
	if (!m_uVertexShader || !m_uFragmentShader || !m_uProgram)
	{
		return false;
	}

	// TODO: load the textures
	m_arrTextures.push_back(renderer->CreateTexture("grass.png"));
	m_arrTextures.push_back(renderer->CreateTexture("terrain.jpg"));
	for (const auto texture : m_arrTextures)
	{
		if (texture == 0) return false;
	}

	// setup our view and projection matrices
	m_mView = glm::lookAt(
		glm::vec3(0.0f, 3.0f, 30.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	m_mProjection = glm::perspective(0.7f, GetAspect(), 0.1f, 500.0f);

	// TODO: generate terrain & grass geometry
	m_pQuad[0] = std::make_shared<Geometry>();
	m_pQuad[0]->GenQuad(glm::vec2(300.0f, 300.0f));
	m_pQuad[1] = std::make_shared<Geometry>();
	m_pQuad[1]->GenQuad(glm::vec2(10.0f, 10.0f));

	// TODO: material
	m_pMaterial = std::make_shared<Material>();

	// build the scenegraph
	m_pSceneRoot = std::make_unique<Node>();
	
	// TODO: use quad as a terrain plane
	auto terrain = std::make_shared<Terrain>(m_pQuad[0], m_pMaterial);
	glm::mat4 m = glm::rotate(glm::mat4(1.0f), -glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	terrain->SetMatrix(m);
	terrain->SetTexture(m_arrTextures[1]);
	m_pSceneRoot->AddNode(terrain);

	// TODO: add grass
	auto grass = std::make_shared<Grass>(m_pQuad[1], m_pMaterial);
	grass->SetPos(0.0f, 20.0f * 0.25f, 0.0f);
	grass->SetTexture(m_arrTextures[0]);
	m_pSceneRoot->AddNode(grass);


	return true;
}


void TheApp::OnDestroy()
{
	// app is about to close, clear all resources
	m_pSceneRoot = nullptr;

	glDeleteProgram(m_uProgram);
	glDeleteShader(m_uFragmentShader);
	glDeleteShader(m_uVertexShader);

	m_uVertexShader = 0;
	m_uFragmentShader = 0;
	m_uProgram = 0;
}


void TheApp::OnUpdate(float frametime)
{
	// update scenegraph
	if (m_pSceneRoot)
	{
		m_pSceneRoot->Update(frametime);
	}
}


void TheApp::OnDraw(IRenderer& renderer)
{
	// clear color, depth and stencil buffers
	renderer.Clear(0.6f, 0.6f, 1.0f, 1.0f);

	// set view and projection into the renderer
	GetRenderer()->SetViewMatrix(m_mView);
	GetRenderer()->SetProjectionMatrix(m_mProjection);

	// setup the rendering program
	glUseProgram(m_uProgram);

	// TODO: set material uniforms to program

	// setup the light position (above scene)
	const glm::vec3 campos(-renderer.GetViewMatrix()[3]);
	const glm::vec3 lightpos(0.0f, 10.0f, campos.z);
	GLint location = glGetUniformLocation(m_uProgram, "lightPosition");
	glUniform3f(location, lightpos.x, lightpos.y, lightpos.z);

	// setup the camera position uniform
	location = glGetUniformLocation(m_uProgram, "cameraPosition");
	glUniform3f(location, campos.x, campos.y, campos.z);

	// draw the scenegraph
	if (m_pSceneRoot)
	{
		m_pSceneRoot->Render(renderer, m_uProgram);
	}
}


void TheApp::OnScreenSizeChanged(uint32_t widthPixels, uint32_t heightPixels)
{
	m_mProjection = glm::perspective(0.7f, GetAspect(), 0.1f, 500.0f);
}


bool TheApp::OnKeyDown(uint32_t keyCode)
{
	if (keyCode == KEY_ESC)
	{
		Close();
		return true;
	}

	return false;
}


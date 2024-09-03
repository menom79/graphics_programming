/**
 * ============================================================================
 *  Name        : TheApp.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB4
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
	m_uVertexShader = GetOpenGLRenderer()->CreateVertexShaderFromFile("phongshader.vs");
	m_uFragmentShader = GetOpenGLRenderer()->CreateFragmentShaderFromFile("phongshader.fs");
	m_uProgram = GetOpenGLRenderer()->CreateProgram(m_uVertexShader, m_uFragmentShader);
	if (!m_uVertexShader || !m_uFragmentShader || !m_uProgram)
	{
		return false;
	}

	// TODO: load the textures
	m_arrTexture.push_back(renderer->CreateTexture("box.png"));
	m_arrTexture.push_back(renderer->CreateTexture("box_specular.png"));
	for (const auto texture : m_arrTexture)
	{
		if (texture == 0) return false;
	}

	// setup our view and projection matrices
	m_mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 12.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	m_mProjection = glm::perspective(0.7f, GetAspect(), 0.1f, 500.0f);

	// TODO: generate box geometry
	m_pCube = std::make_shared<Geometry>();
	m_pCube->GenCube(glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// TODO: use material
	m_pMaterial = std::make_shared<Material>();

	// build the scenegraph
	m_pSceneRoot = std::make_unique<Node>();
	
	// TODO: create box object and add to scenegraph
	m_pSceneRoot = std::make_unique<Node>();

	//spawn cube
	auto cube = std::make_shared<GeometryNode>(m_pCube, nullptr);
	cube->SetName("cube");
	cube->SetPos(0.0f, 0.0f, 0.0f);
	m_pSceneRoot->AddNode(cube);

	for (auto& node : m_pSceneRoot->GetChildren())
	{
		cube->SetRotationSpeed(glm::linearRand(-1.0f, 1.0f));
		cube->SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		cube->SetMaterial(m_pMaterial);

		const glm::vec3 axis(glm::linearRand(-1.0f, 1.0f),
			glm::linearRand(-1.0f, 1.0f),
			glm::linearRand(-1.0f, 1.0f));
		cube->SetRotationAxis(axis);
	}

	return true;
}


void TheApp::OnDestroy()
{
	// app is about to close, clear all resources
	m_pSceneRoot = nullptr;

	glDeleteProgram(m_uProgram);
	glDeleteShader(m_uFragmentShader);
	glDeleteShader(m_uVertexShader);

	// TODO: delete loaded textures

	m_uVertexShader = 0;
	m_uFragmentShader = 0;
	m_uProgram = 0;
}


void TheApp::OnUpdate(float frametime)
{
	// TODO: rotate box around a bit to see the specular effect

	// update scenegraph
	if (m_pSceneRoot)
	{
		m_pSceneRoot->Update(frametime);
	}
}


void TheApp::OnDraw(IRenderer& renderer)
{
	// clear color, depth and stencil buffers
	renderer.Clear(0.2f, 0.2f, 0.2f, 1.0f);

	glUseProgram(m_uProgram);

	// set view and projection into the renderer
	GetRenderer()->SetViewMatrix(m_mView);
	GetRenderer()->SetProjectionMatrix(m_mProjection);

	// setup the rendering program
	glUseProgram(m_uProgram);

	glDisable(GL_BLEND);

	// TODO: set the textures to slot 0 and slot 1
	
	if (m_pSceneRoot)
	{
		auto cube = static_cast<GeometryNode*>(m_pSceneRoot->FindNode("cube"));
		renderer.SetTexture(m_uProgram, m_arrTexture[0], 0, "texture01");
		SetTextureParams();
		renderer.SetTexture(m_uProgram, m_arrTexture[1], 1, "texture02");
		SetTextureParams();
		cube->Render(renderer, m_uProgram);
	}

	// TODO: set material uniforms to program

	// setup the light position (to camera position)
	const glm::vec3 campos(-renderer.GetViewMatrix()[3]);
	GLint location = glGetUniformLocation(m_uProgram, "lightPosition");
	glUniform3f(location, campos.x, campos.y, campos.z);

	// setup the camera position uniform
	location = glGetUniformLocation(m_uProgram, "cameraPosition");
	glUniform3f(location, campos.x, campos.y, campos.z);

	// draw the scenegraph
	if (m_pSceneRoot)
	{
		m_pSceneRoot->Render(renderer, m_uProgram);
	}
}

void TheApp::SetTextureParams()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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


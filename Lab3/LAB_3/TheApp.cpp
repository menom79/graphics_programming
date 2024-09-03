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
TheApp::TheApp() :
	m_uVertexShader(0),
	m_uFragmentShader(0),
	m_uProgram(0),
	m_uTexture(0),
	m_fTurntank(0.0f)
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
	m_uTexture = renderer->CreateTexture("white.png");
	if (!m_uVertexShader || !m_uFragmentShader || !m_uProgram || !m_uTexture)
	{
		return false;
	}

	// setup our view and projection matrices
	m_mView = glm::lookAt(
		glm::vec3(0.0f, 7.0f, 25.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	m_mProjection = glm::perspective(0.7f, GetAspect(), 0.1f, 500.0f);

	// build the scenegraph
	m_pSceneRoot = std::make_unique<Node>();

	// material
	m_pMaterialTank = std::make_shared<Material>();
	m_pMaterialTank->m_cAmbient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pMaterialTank->m_cDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterialTank->m_cSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterialTank->m_cEmissive = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_pMaterialTank->m_fSpecularPower = 25.0f;

	// part1 add node part2
	m_pTankbase = std::make_shared<Geometry>();
	m_pTankbase->GenCube(glm::vec3(5.0f, 3.0f, 5.0f));

	auto part1 = std::make_shared<TankPiece>(m_pTankbase, m_pMaterialTank);
	m_pSceneRoot->AddNode(part1);

	m_pTanktower = std::make_shared<Geometry>();
	m_pTanktower->GenCube(glm::vec3(3.0f, 2.0f, 3.0f));

	auto part2 = std::make_shared<TankPiece>(m_pTanktower, m_pMaterialTank);
	part2->SetPos({0.0f, 2.5f, 0.5f});
	part1->AddNode(part2);

	m_pTankpipe = std::make_shared<Geometry>();
	m_pTankpipe->GenCube(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, 2.5f));

	auto part3 = std::make_shared<TankPiece>(m_pTankpipe, m_pMaterialTank);
	part3->SetPos({ 0.0f, 0.0f, 0.5f });
	part2->AddNode(part3);

	//adding velocity
	//const glm::vec3 velocity(
	//	glm::linearRand(0.0f, 10.0f),
	//	glm::linearRand(0.0f, 0.0f),
	//	glm::linearRand(0.0f, 0.0f));
	//part1->SetVelocity(velocity);

	return true;
}


void TheApp::OnDestroy()
{
	// app is about to close, clear all resources
	m_pSceneRoot = nullptr;

	glDeleteTextures(1, &m_uTexture);
	glDeleteProgram(m_uProgram);
	glDeleteShader(m_uFragmentShader);
	glDeleteShader(m_uVertexShader);

	m_uTexture = 0;
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

	auto part1 = m_pSceneRoot->GetChildren()[0];
	auto part2 = part1->GetChildren()[0];
	auto part3 = part2->GetChildren()[0];

	part1->SetRotationAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	part2->SetRotationAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	//part1->SetVelocity((0.0f, 1.0f), (0.0f, 0.0f), (0.0f, 0.0f))
	// part1->SetRotationSpeed(1.0f);

	if (IsKeyDown(KEY_LEFT))
	{
		part1->SetRotationSpeed(1.0f);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		part1->SetRotationSpeed(-1.0f);
	}
	else
	{
		part1->SetRotationSpeed(0.0f);
	}

	if (IsKeyDown('A'))
	{
		part2->SetRotationSpeed(1.0f);
	}
	else if (IsKeyDown('D'))
	{
		part2->SetRotationSpeed(-1.0f);
	}
	else
	{
		part2->SetRotationSpeed(0.0f);
	}

	if (IsKeyDown(KEY_UP))
	{
		const glm::vec3 direction = part1->GetWorldMatrix()[2];
		const glm::vec3 velocity(
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f));
		part1->SetVelocity(direction * 5.0f);
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		const glm::vec3 direction = part1->GetWorldMatrix()[2];
		const glm::vec3 velocity(
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f));
		part1->SetVelocity(-direction * 5.0f);
	}
	else
	{
		const glm::vec3 velocity(
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f),
			glm::linearRand(0.0f, 0.0f));
		part1->SetVelocity(velocity);
	}

	if (IsKeyDown('W'))
	{
		part3->SetRotationAxis(glm::vec3(1.0f, 0.0f, 0.0f));
		part3->SetRotationSpeed(-1.0f);
	}
	else if (IsKeyDown('S'))
	{
		part3->SetRotationAxis(glm::vec3(1.0f, 0.0f, 0.0f));
		part3->SetRotationSpeed(1.0f);
	}
	else
	{
		part3->SetRotationSpeed(0.0f);
	}

	if (part3->GetRotationAngle() > 0.3f)
	{
		part3->SetRotationSpeed(0.0f);
		part3->SetRotationAngle(0.3f);
	}
	else if (part3->GetRotationAngle() < -0.4f)
	{
		part3->SetRotationSpeed(0.0f);
		part3->SetRotationAngle(-0.4f);
	}
	// set velocity

	// turning
	//if (m_bTankTurning)
	//{
	//	const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_fTurntank, glm::vec3(0.0f, 1.0f, 0.0f));
	//	m_mModel = rotation;
	//	m_fTurntank += frametime;
	//}
	//else
	//{
	//	const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_fTurntank, glm::vec3(0.0f, 0.0f, 0.0f));
	//}
}


void TheApp::OnDraw(IRenderer& renderer)
{
	// clear color, depth and stencil buffers
	renderer.Clear(0.2f, 0.2f, 0.2f, 1.0f);

	// set view and projection into the renderer
	GetRenderer()->SetViewMatrix(m_mView);
	GetRenderer()->SetProjectionMatrix(m_mProjection);

	// setup the rendering of our quad
	glUseProgram(m_uProgram);

	// set the texture for the quad (slot 0)
	renderer.SetTexture(m_uProgram, m_uTexture, 0, "texture01");

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


void TheApp::OnScreenSizeChanged(uint32_t widthPixels, uint32_t heightPixels)
{
	m_mProjection = glm::perspective(0.7f, GetAspect(), 0.1f, 500.0f);
}


bool TheApp::OnMouseBegin(int32_t buttonIndex, const glm::vec2& point)
{
	//Debug("OnMouseBegin " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
}


bool TheApp::OnMouseDrag(int32_t buttonIndex, const glm::vec2& point)
{
	//Debug("OnMouseDrag " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
}


bool TheApp::OnMouseEnd(int32_t buttonIndex, const glm::vec2& point)
{
	//Debug("OnMouseEnd " + std::to_string(iButtonIndex) + ": " + std::to_string((int)vPoint.x) + "x" + std::to_string((int)vPoint.y) + "\r\n");
	return true;
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


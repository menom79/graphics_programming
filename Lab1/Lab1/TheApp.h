/**
 * ============================================================================
 *  Name        : TheApp.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : LAB1
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#pragma once

#include "../core/include/IApplication.h"
#include "../core/include/OpenGLRenderer.h"


struct VERTEX
{
	VERTEX() :
		x(0.0f), y(0.0f), z(0.0f)
	{
	}
	VERTEX(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z)
	{
	}

	void setcolor(const glm::vec4& color)
	{
		r = color.r;
		b = color.b;
		g = color.g;
		a = color.a;
	}

	static constexpr int32_t GetStride() { return 28; }

	float x, y, z;
	float r, g, b, a;
};

class CTheApp : public IApplication
{
public:
	CTheApp();

	/**
	 * OnCreate
	 * app initializer, called by abstraction layer when engine initialization is complete
	 * @return true if successful, false otherwise.
	 */
	bool OnCreate() override;

	/**
	 * OnDestroy
	 * app destroyer, called by the abstraction layer when app is about to get destoyed
	 */
	void OnDestroy() override;

	/**
	 * OnUpdate
	 * app update loop
	 * @param fFrametime time since previous update, in seconds
	 */
	void OnUpdate(float fFrametime) override;

	/**
	 * OnDraw
	 * app drawing method
	 * @param pRenderer pointer to renderer object
	 */
	void OnDraw(IRenderer& pRenderer) override;

protected:
	/**
	 * OnScreenSizeChanged
	 * event when screen size changes
	 * @param uWidthPixels, uHeightPixels new pixel size of the screen
	 */
	void OnScreenSizeChanged(uint32_t uWidthPixels, uint32_t uHeightPixels) override;

	/**
	 * OnMouseBegin
	 * event when mouse button is pressed down
	 * @param iButtonIndex index of the mouse button (0 based)
	 * @param vPoint event coordinate in pixels
	 * @return true if event was handled by the receiver
	 */
	bool OnMouseBegin(int iButtonIndex, const glm::vec2& vPoint) override;

	/**
	 * OnMouseDrag
	 * event when mouse is dragged
	 * @param iButtonIndex index of the mouse button (0 based)
	 * @param vPoint event coordinate in pixels
	 * @return true if event was handled by the receiver
	 */
	bool OnMouseDrag(int iButtonIndex, const glm::vec2& vPoint) override;

	/**
	 * OnMouseEnd
	 * event when mouse button is lifted up
	 * @param iButtonIndex index of the mouse button (0 based)
	 * @param vPoint event coordinate in pixels
	 * @return true if event was handled by the receiver
	 */
	bool OnMouseEnd(int iButtonIndex, const glm::vec2& vPoint) override;

	/**
	 * OnKeyDown
	 * key down event
	 * @param uKeyCode key code
	 * @return true if event was handled by the receiver
	 */
	bool OnKeyDown(uint32_t uKeyCode) override;

private:
	/**
	 * GetOpenGLRenderer
	 * helper method to access the openGL renderer layer
	 * @return pointer to OpenGL renderer
	 */
	OpenGLRenderer* GetOpenGLRenderer() { return static_cast<OpenGLRenderer*>(GetRenderer()); }

private:
	// app data

	//vertices for one (unindexed) quad
	VERTEX			m_Quad[3];

	GLuint			m_uVertexShader;
	GLuint			m_uFragmentShader;
	GLuint			m_uProgram;

	// matrix for our quad model
	glm::mat4		m_mModel;

	//camera view matrix
	glm::mat4		m_mView;

	//camera projection matrix
	glm::mat4		m_mProjection;

	// x-position, and angle to rotate the quad and for camera z-movement
	float			m_fTriangleRotation;
	float			m_fAngle;

	//added
	bool			m_bEnableRotation;
};


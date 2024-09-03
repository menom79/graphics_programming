/**
 * ============================================================================
 *  Name        : OpenGLRenderer.h
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : concrete OpenGL renderer layer
 *  Version     : 1.00
 *	Author      : Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/

#pragma once

#include "IRenderer.h"
#include "IApplication.h"


#include <GL/gl.h>
#if defined (_WINDOWS)
#include "./GL/glext.h"
#endif
#include "./GL/myGL.h"


class OpenGLRenderer : public IRenderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	/**
	 * Create (from IRenderer)
	 * @return true if succesful, or false to cancel app startup
	 */
	bool Create() override;

	/**
	 * Flip (from IRenderer)
	 * transfer graphics to screen
	 */
	void Flip() override;

	/**
	 * Clear
	 * clear the color buffer, depth buffer and stencil
	 */
	void Clear(float r, float g, float b, float a, float depth = 1.0f, int32_t stencil = 0) override;

	/**
	 * SetViewport
	 * set viewport area of the screen
	 * @param area, x, y, width, height of the viewport area
	 */
	void SetViewport(const glm::ivec4& area) override;

	/**
	 * SetTexture
	 * @param program
	 * @param texture handle
	 * @param slot index of the texture slot
	 * @param uniformName name of the uniform in shader
	 * @return true if uniform is found and set
	 */
	bool SetTexture(uint32_t program, uint32_t texture, int32_t slot, const std::string_view& uniformName) override;

	/**
	 * CreateTexture
	 * create opengl texture handle from image file
	 * @param filename file to load
	 * @return opengl texture handle, or 0 if failed
	 */
	GLuint CreateTexture(const std::string& filename);

	/**
	 * CreateVertexShader
	 * create opengl vertex shader from text
	 * @param vertexShader shader source code
	 * @return opengl shader handle, or 0 if failed
	 */
	GLuint CreateVertexShader(const char* vertexShader);

	/**
	 * CreateVertexShaderFromFile
	 * create opengl vertex shader from text file
	 * @param filename text file to load
	 * @return opengl shader handle, or 0 if failed
	 */
	GLuint CreateVertexShaderFromFile(const std::string_view& filename);

	/**
	 * CreateFragmentShader
	 * create opengl fragment shader from text
	 * @param fragmentShader shader source code
	 * @return opengl shader handle, or 0 if failed
	 */
	GLuint CreateFragmentShader(const char* fragmentShader);

	/**
	 * CreateFragmentShaderFromFile
	 * create opengl fragment shader from text file
	 * @param filename text file to load
	 * @return opengl shader handle, or 0 if failed
	 */
	GLuint CreateFragmentShaderFromFile(const std::string_view& filename);

	/**
	 * CreateProgram
	 * Link opengl program from vertex and fragment shader
	 * @param vertexShader
	 * @param fragmentShader
	 * @return opengl program handle, or 0 if failed
	 */
	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);

	/**
	 * PrintShaderError/PrintProgramError
	 * helpers to print detailed information of shader and program errors
	 * @param shader
	 * @param program
	 */
	void PrintShaderError(GLuint shader);
	void PrintProgramError(GLuint program);

	/**
	 * InitFunctions
	 * static helper to get OpenGL function pointers after context has been created
	 */
	static bool InitFunctions();

private:
	bool SetDefaultSettings();

#if defined (_WINDOWS)
	HDC				m_Context;
	HGLRC			m_hRC;
#endif

#if defined (_LINUX)
	void*			m_Context;
#endif
};


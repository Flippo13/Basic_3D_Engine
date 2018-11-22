#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

using namespace std;

class ShaderUtil
{
public:
	/**
	* Create a program from a vertex and fragment shader source path.
	*
	* @param pVertexShaderPath the path to the vertex shader source path
	* @param pFragmentShaderPath the path to the vertex shader source path
	*/
	static GLuint createProgam(const string& pVertexShaderPath, const string& pFragmentShaderPath);

private:

	/**
	* Load a shader from a file.
	*
	* @param pShaderPath   the path to load the shader from
	* @param pShaderType the type of shader to load
	*/
	static GLuint _loadShader(const string& pShaderPath, GLenum pShaderType);

	/**
	* Compile a list of shaders into a program.
	*
	* @param pShaders list of shaders to link
	*/
	static GLuint _compileAndLinkProgram(const std::vector<GLuint> &pShaders);
};

#endif // SHADERUTIL_H

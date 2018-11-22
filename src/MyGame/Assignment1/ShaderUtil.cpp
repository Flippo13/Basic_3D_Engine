#include "ShaderUtil.h"
#include <fstream>
#include <sstream>

GLuint ShaderUtil::createProgam(const string& pVertexShaderPath, const string& pFragmentShaderPath)
{
	GLuint vertexShader = _loadShader(pVertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = _loadShader(pFragmentShaderPath, GL_FRAGMENT_SHADER);

	if (vertexShader == 0 || fragmentShader == 0) {
		cout << "One or more shaders failed, exiting..." << endl;
		return 0;
	}

	std::vector<GLuint> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);

	GLuint program = _compileAndLinkProgram(shaders);

	//after the program has been compiled and linked we can release the individual shaders
	for (size_t i = 0; i < shaders.size(); i++) {
		glDeleteShader(shaders[i]);
	}

	return program;
}


GLuint ShaderUtil::_loadShader(const string& pShaderPath, GLenum pShaderType) {
	cout << "-----------------------------------" << endl;
	cout << "Loading file " << pShaderPath << ":" << endl << endl;

	//open the source path
	ifstream sourceFile(pShaderPath.c_str());
	if (!sourceFile) {
		cout << "Could not read shader file <" << pShaderPath << ">";
		cout << "-----------------------------------" << endl;
		return 0;
	}

	//read the whole file into a stream
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	sourceFile.close();

	//dump source on the output stream so we can see it
	string source = buffer.str();
	cout << source;
	cout << "-----------------------------------" << endl;

	//create a shader and test successful creation
	cout << "Creating shader object..." << endl;
	GLuint shaderHandle = glCreateShader(pShaderType);
	cout << "Shader creation successful? " << (shaderHandle != 0 ? "Yes" : "No") << endl;
	if (shaderHandle == 0) return 0;

	//load sourcePointer (which is one string) into shaderHandle, and since its null terminated we can
	//pass in NULL for the length array
	cout << "Loading source into shader..." << endl;
	char const * sourcePointer = source.c_str();
	glShaderSource(shaderHandle, 1, &sourcePointer, NULL);

	//compile and check compilation status
	cout << "Compiling shader..." << endl;
	glCompileShader(shaderHandle);
	GLint compileStatus = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		cout << "Shader compilation failed:" << endl;

		GLint logLength = 0;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			GLchar* errorLog = new GLchar[logLength];
			glGetShaderInfoLog(shaderHandle, logLength, NULL, errorLog);
			cout << errorLog << endl;
			delete[] errorLog;
		}
		else {
			cout << "No info available." << endl;
		}
		return 0;
	}

	cout << "Shader compilation successful." << endl << endl;
	return shaderHandle;
}

/**
* Take the given list of shaders and link them into a new program
*/
GLuint ShaderUtil::_compileAndLinkProgram(const std::vector<GLuint> &pShaders) {
	cout << "Creating new program..." << endl;
	GLuint program = glCreateProgram();
	cout << "Program id:" << program << endl;
	for (size_t i = 0; i < pShaders.size(); i++) {
		cout << "   Attaching shader " << pShaders[i] << endl;
		glAttachShader(program, pShaders[i]);
	}
	cout << "Linking program..." << endl;
	glLinkProgram(program);

	int linkStatus = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		cout << "Linking failed... " << endl;

		int linkLogSize = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &linkLogSize);

		GLchar* linkLog = new GLchar[linkLogSize];
		glGetProgramInfoLog(program, linkLogSize, NULL, linkLog);
		cout << linkLog << endl;
		delete[] linkLog;
		return 0;

	}
	else {
		cout << "Link successful." << endl;
	}

	cout << endl;

	//detach the shaders again (we have a binary linked program now)
	for (size_t i = 0; i < pShaders.size(); i++) {
		glDetachShader(program, pShaders[i]);
	}

	return program;
}


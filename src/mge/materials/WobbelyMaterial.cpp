#include "glm.hpp"

#include "WobbelyMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* WobbelyMaterial::_shader = NULL;

GLint WobbelyMaterial::_uOffset = 0;
GLint WobbelyMaterial::_uTime = 0; 
GLint WobbelyMaterial::_uPosition = 0; 

GLint WobbelyMaterial::_aVertex = 0;
GLint WobbelyMaterial::_uMVPMatrix = 0;
GLint WobbelyMaterial::_uDiffuseTexture = 0;

GLint WobbelyMaterial::_aNormal = 0;
GLint WobbelyMaterial::_aUV = 0;
/*
*/

WobbelyMaterial::WobbelyMaterial(Texture* pDiffuseTexture):_diffuseTexture(pDiffuseTexture)
{
	_lazyInitializeShader(); 
}


WobbelyMaterial::~WobbelyMaterial()
{
}

//-------- Here we will put in all the info the shader needs to go Wobble --------------//
void WobbelyMaterial::_lazyInitializeShader()
{

	/*
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobbely.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "wobbely.fs");
		_shader->finalize();


		//_aVertex = _shader->getAttribLocation("vertex"); 
		_uOffset = _shader->getAttribLocation("offset");
	}
	*/

	if (!_shader) // is shader is NULL, then will make one
		_shader = new ShaderProgram(); //now that we have an shader, we can start adding the info in it 
	_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobbely.vs");//here we say which file we need to read from/write to for the vertex/fragmant shader
	_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "wobbely.fs");
	_shader->finalize(); 

	_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
	_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
	_uOffset = _shader->getUniformLocation("offset");
	_uPosition = _shader->getUniformLocation("position"); 
	_uTime = _shader->getUniformLocation("timer"); 

	_aVertex = _shader->getAttribLocation("vertex");
	_aNormal = _shader->getAttribLocation("normal");
	_aUV = _shader->getAttribLocation("uv");
}


void WobbelyMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

void WobbelyMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	_shader->use();
	
	/*
	//set the material color
	glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);
	*/


	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	//now inform mesh of where to stream its data
	float xOffset =  cos(clock() / 1000.0f);
	float yOffset = 0.5f * sin(clock() / 1000.0f);
	glm::vec3 position = pWorld->getWorldPosition();
	
	glUniform4f(_uPosition, position.x,position.y,position.z,1.0f);

	float time = clock() / 1000.0f;
	glUniform1f(_uTime, time); 
	//pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix  * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	glUniform2f(_uOffset, xOffset, yOffset);

	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}


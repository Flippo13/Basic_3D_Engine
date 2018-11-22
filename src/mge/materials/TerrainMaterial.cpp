#include "TerrainMaterial.h"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uHeightMapTexture = 0;
GLint TerrainMaterial::_uSplatMap = 0; 
GLint TerrainMaterial::_uDiffuseTexture = 0;
GLint TerrainMaterial::_uDiffuseTexture2 = 0; 
GLint TerrainMaterial::_uDiffuseTexture3 = 0; 
GLint TerrainMaterial::_uDiffuseTexture4 = 0; 

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;



TerrainMaterial::TerrainMaterial(Texture * pHeightMapTexture, Texture * pSplatMapTexture, Texture * pDiffuseTexture, Texture * pDiffuseTexture2, Texture * pDiffuseTexture3, Texture * pDiffuseTexture4) :
	_heightMapTexture(pHeightMapTexture), _splatMapTexture(pSplatMapTexture), _diffuseTexture(pDiffuseTexture), _diffuseTexture2(pDiffuseTexture2), _diffuseTexture3(pDiffuseTexture3), _diffuseTexture4(pDiffuseTexture4)
{
	_lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial()
{
}

void TerrainMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uHeightMapTexture = _shader->getUniformLocation("heightMapTexture");
		_uSplatMap = _shader->getUniformLocation("splatMapTexture"); 
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uDiffuseTexture2 = _shader->getUniformLocation("diffuseTexture2");
		_uDiffuseTexture3 = _shader->getUniformLocation("diffuseTexture3");
		_uDiffuseTexture4 = _shader->getUniformLocation("diffuseTexture4"); 


		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TerrainMaterial::render(World * pWorld, Mesh * pMesh, const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	if (!_diffuseTexture || !_heightMapTexture || !_splatMapTexture || !_diffuseTexture2 || !_diffuseTexture3 || !_diffuseTexture4) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _heightMapTexture->getId());
	//tell the shader the texture slot for the heightmap texture is slot 0
	glUniform1i(_uHeightMapTexture, 0);

	//setup splatmaptexture slot 1
	glActiveTexture(GL_TEXTURE1);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _splatMapTexture->getId()); 
	//tell the shader the texture slot for the diffuse texture is slot 1 
	glUniform1i(_uSplatMap, 1); 

	//setup texture slot 2
	glActiveTexture(GL_TEXTURE2);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 3 
	glUniform1i(_uDiffuseTexture, 2);


	//setup texture slot 3
	glActiveTexture(GL_TEXTURE3);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture2->getId());
	//tell the shader the texture slot for the diffuse texture is slot 3 
	glUniform1i(_uDiffuseTexture2, 3);


	glActiveTexture(GL_TEXTURE4);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture3->getId());
	//tell the shader the texture slot for the diffuse texture is slot 4 
	glUniform1i(_uDiffuseTexture3, 4);


	glActiveTexture(GL_TEXTURE5);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture4->getId());
	//tell the shader the texture slot for the diffuse texture is slot 5 
	glUniform1i(_uDiffuseTexture4, 5);

	//pass in the time for animation
	glUniform1f(_shader->getUniformLocation("time"), glm::float1(std::clock()));


	//pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

void TerrainMaterial::setDiffuseTexture(Texture * pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;

}

void TerrainMaterial::setHeightMap(Texture * pHeightMap)
{
}

void TerrainMaterial::setSplatMap(Texture * pSlatMap)
{
}


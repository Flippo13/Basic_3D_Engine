#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;
#pragma once

class TerrainMaterial : public AbstractMaterial
{
public :
	TerrainMaterial( Texture* pHeightMapTexture, Texture* pSplatMapTexture ,Texture* pDiffuseTexture, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4);
	virtual ~TerrainMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);
	void setHeightMap(Texture* pHeightMap); 
	void setSplatMap(Texture* pSlatMap); 

private:

	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//in this example we cache all identifiers for uniforms & attributes
	static GLint _uMVPMatrix;
	static GLint _uSplatMap; 
	static GLint _uHeightMapTexture; 
	static GLint _uDiffuseTexture;
	static GLint _uDiffuseTexture2; 
	static GLint _uDiffuseTexture3; 
	static GLint _uDiffuseTexture4; 

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _heightMapTexture; 
	Texture* _splatMapTexture; 
	Texture* _diffuseTexture;
	Texture* _diffuseTexture2; 
	Texture* _diffuseTexture3; 
	Texture* _diffuseTexture4; 
};

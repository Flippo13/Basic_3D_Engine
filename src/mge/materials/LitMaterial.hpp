#include "mge/materials/AbstractMaterial.hpp"
#include "glm.hpp"
#include "GL/glew.h"

class ShaderProgram;


#pragma once
class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(glm::vec3 pColor, glm::vec3 pAmbient);
	~LitMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;


	//in rgb values
	void setDiffuseColor(glm::vec3 pDiffuseColor);
	void setAmbientColor(glm::vec3 pAmbientColor);

private:
	//all the static properties are shared between instances of ColorMaterial
	//note that they are all PRIVATE, we do not expose this static info to the outside world
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//this one is unique per instance of color material
	glm::vec3 _diffuseColor;
	glm::vec3 _ambientColor;
};


#include "mge/materials/LitMaterial.hpp"

#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/world.hpp"

ShaderProgram* LitMaterial::_shader = NULL;


LitMaterial::LitMaterial(glm::vec3 pColor, glm::vec3 pAmbient) :_diffuseColor(pColor), _ambientColor(pAmbient)
{
	_lazyInitializeShader();
}

LitMaterial::~LitMaterial()
{
}

void LitMaterial::render(World * pWorld, Mesh * pMesh, const glm::mat4 & pModelMatrix, const glm::mat4 & pViewMatrix, const glm::mat4 & pProjectionMatrix)
{
	_shader->use();
	Light* currentLight = pWorld->getLightAt(0);

	//set the material color
	glUniform3fv(_shader->getUniformLocation("light.lightColor"), 1, glm::value_ptr(currentLight->getLightColor()));
	glUniform1i(_shader->getUniformLocation("light.lightType"), (int)currentLight->getLightType());
	glUniform3fv(_shader->getUniformLocation("light.lightDirection"), 1, glm::value_ptr(currentLight->getTransform()[2])); //forward vector of the light

	glUniform3fv(_shader->getUniformLocation("light.lightPosition"), 1, glm::value_ptr(currentLight->getLocalPosition())); //might need to be changed to world pos
	glUniform1f(_shader->getUniformLocation("light.ambientContribution"), 0.2f);
	//glUniform3fv(_shader->getUniformLocation("light.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	//glUniform3fv(_shader->getUniformLocation("light.ambient"), 1, glm::value_ptr(glm::vec3(0.2f,0.2f,0.2f)));

	glUniform3fv(_shader->getUniformLocation("light.diffuse"), 1, glm::value_ptr(currentLight->getLightDiffuseColor()));
	glUniform3fv(_shader->getUniformLocation("light.ambient"), 1, glm::value_ptr(currentLight->getLightAmbientColor()));

	glUniform3fv(_shader->getUniformLocation("material.diffuseColor"), 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(_shader->getUniformLocation("material.ambientColor"), 1, glm::value_ptr(_ambientColor));

	glUniform1f(_shader->getUniformLocation("light.constant"), 1.0f);
	glUniform1f(_shader->getUniformLocation("light.linear"), 0.09f);
	glUniform1f(_shader->getUniformLocation("light.quadratic"), 0.032f);


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
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor)
{
	_diffuseColor = pDiffuseColor;
}

void LitMaterial::setAmbientColor(glm::vec3 pAmbientColor)
{
	_ambientColor = pAmbientColor;
}

void LitMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "lit.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "lit.fs");
		_shader->finalize();
	}
}

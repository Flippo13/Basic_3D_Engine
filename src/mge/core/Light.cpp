#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/ColorMaterial.hpp"

Light::Light(LightType pLightType, glm::vec3 pLightColor,glm::vec3 pLightDiffuseColor, glm::vec3 pLightAmbientColor,const std::string & pName, const glm::vec3 & pPosition, float pIntensity ) : GameObject(pName, pPosition)
, _lightType(pLightType), _intensity(pIntensity), _lightColor(pLightColor), _ambient(pLightAmbientColor), _diffuse(pLightDiffuseColor)
{
	//light object has the same color as the color it will transmit
	AbstractMaterial* lightMaterial = new ColorMaterial(pLightColor);
	setMaterial(lightMaterial); 
}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::setLightType(LightType pLightType)
{
	_lightType = pLightType;
}

LightType Light::getLightType()
{
	return _lightType;
}

float Light::getInstensity()
{
	return _intensity;
}

glm::vec3 Light::getLightColor()
{
	return _lightColor;
}

glm::vec3 Light::getLightDiffuseColor()
{
	return _diffuse;
}

glm::vec3 Light::getLightAmbientColor()
{
	return _ambient;
}



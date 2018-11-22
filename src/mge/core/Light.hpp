#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
enum LightType {DIRECTIONAL, POINT};

class Light : public GameObject
{
	public:
		Light(LightType pLightType, glm::vec3 pLightColor, glm::vec3 pLightDiffuseColor, glm::vec3 pLightAmbientColor,const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(2.0f, 10.0f, 5.0f), float pIntensity = 0.1f );
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;
		
		void setLightType(LightType pLightType);

		LightType getLightType();

		float getInstensity();

		glm::vec3 getLightColor();

		glm::vec3 getLightDiffuseColor();

		glm::vec3 getLightAmbientColor();

private:
		LightType _lightType; 
		glm::vec3 _lightColor; 
		float _intensity; 
		glm::vec3 _ambient; 
		glm::vec3 _diffuse; 

};

#endif // LIGHT_HPP

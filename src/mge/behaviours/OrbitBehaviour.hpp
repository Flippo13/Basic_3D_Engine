#ifndef ORBITBEHAVIOUR_HPP
#define ORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class OrbitBehaviour : public AbstractBehaviour
{
	public:
		OrbitBehaviour(float pDistance, float pMinTilt, float pMaxTilt, float pRotSpeed, GameObject* target);
		virtual ~OrbitBehaviour();
		virtual void update(float pStep);

	private:


		float _distance; 
		float _minTilt; 
		float _maxTilt; 
		float _rotSpeed; 
		float _rotX; 
		float _rotY; 
		GameObject* _target;

		sf::Vector2i _currentMousePos; 
		sf::Vector2i _lastMousePos; 
		sf::Vector2f _mouseDelta; 
		sf::Vector2f _rotateCameraValue; 
		
		//glm::mat4 orbit(GameObject* target);
};

#endif
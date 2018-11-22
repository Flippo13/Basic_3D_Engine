#include <iostream>
#include "OrbitBehaviour.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

OrbitBehaviour::OrbitBehaviour(float pDistance, float pMinTilt, float pMaxTilt, float pRotSpeed, GameObject * pTarget)
	: AbstractBehaviour(), _distance(pDistance), _minTilt(pMinTilt), _maxTilt(pMaxTilt), _rotSpeed(pRotSpeed), _target(pTarget), 
	_mouseDelta(sf::Vector2f()), _lastMousePos(sf::Vector2f()), _currentMousePos(sf::Vector2f()), _rotX(float()), _rotY(float())
{
}


OrbitBehaviour::~OrbitBehaviour()
{
}



void OrbitBehaviour::update(float pStep)
{
	
		_owner->setTransform(
			glm::inverse(
			glm::lookAt(_owner->getWorldPosition(), _target->getWorldPosition(), glm::vec3(0, 1, 0))
			));
	
		glm::mat4 targetTrans;
		glm::vec3 targetPos = _target->getWorldPosition(); 

		targetTrans = glm::translate(targetPos); 
		targetTrans = glm::rotate(targetTrans, _rotX, glm::vec3(0,1,0)); 
		targetTrans = glm::rotate(targetTrans, _rotY, glm::vec3(1, 0, 0));
		targetTrans = glm::translate(targetTrans, glm::vec3(0, 0, _distance)); 
		_owner->setTransform(targetTrans); 


	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		
		_lastMousePos = _currentMousePos; 
		
		_mouseDelta = (sf::Vector2f)(_lastMousePos - sf::Mouse::getPosition());
		
		_rotX = (_mouseDelta.x * _rotSpeed) /100.0f; 
		_rotY = glm::clamp(_mouseDelta.y + _rotSpeed,_minTilt,_maxTilt) / 100.0f;

	}
	else
	{
		_currentMousePos = sf::Mouse::getPosition();
	}

}

/*
glm::mat4 OrbitBehaviour::orbit(GameObject* pTarget)
{
}
*/


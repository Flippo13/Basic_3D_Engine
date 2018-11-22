#include <iostream>
#include <string>

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbelyMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.h"

#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "MyGame/MyGameDemo.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MyGameDemo::MyGameDemo():AbstractGame (),_hud(0)
{
}
void MyGameDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}


//build the game _world
void MyGameDemo::_initializeScene()
{
	
	
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane_8192.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");
	Mesh* suzannaMeshS = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");
	Mesh* cubeMeshS = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj"); 
	Mesh* sphereTest1 = Mesh::load(config::MGE_MODEL_PATH + "sphere1.obj");
	Mesh* sphereTest2 = Mesh::load(config::MGE_MODEL_PATH + "sphere2.obj");
	Mesh* sphereTest3 = Mesh::load(config::MGE_MODEL_PATH + "sphere3.obj");
	Mesh* sphereTest4 = Mesh::load(config::MGE_MODEL_PATH + "sphere4.obj");
	//MATERIALS

    //create some materials to display the cube, the plane and the light
	AbstractMaterial* wobbleMaterial = new WobbelyMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
	AbstractMaterial* litMaterial = new LitMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f));
	AbstractMaterial* litRedMaterial = new LitMaterial(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	AbstractMaterial* planeLitMaterial = new LitMaterial(glm::vec3(0.5f, 1.0f, 0.31f),glm::vec3(0.5f, 0.1f, 0.31f));

    AbstractMaterial* runicStoneMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"runicfloor.png"));
	AbstractMaterial* colorMaterial = new ColorMaterial(glm::vec3(1, 0.3f, 0.5f));
	AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH+"bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	AbstractMaterial* terrainMaterial = new TerrainMaterial(Texture::load(config::MGE_TEXTURE_PATH + "heightmap.png"),Texture::load(config::MGE_TEXTURE_PATH+ "splatmap.png"), Texture::load(config::MGE_TEXTURE_PATH + "water.jpg"), Texture::load(config::MGE_TEXTURE_PATH+ "diffuse1.jpg"), Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"), Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"));
   
	//SCENE SETUP
  
	//add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,0,20));
    camera->rotate(glm::radians(-45.0f), glm::vec3(1,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

	//Not rendering at all, it has no vn values
	GameObject* sphere1 = new GameObject("spheretest1", glm::vec3(-8, 0, 0));
	sphere1->scale(glm::vec3(2.5, 2.5, 2.5));
	sphere1->setMesh(sphereTest1);
	sphere1->setMaterial(brickMaterial);
	//sphere1->setBehaviour(new KeysBehaviour());
	//_world->add(sphere1);
	
	//This one seems to be correct. only the uvs are a bit weird
	GameObject* sphere2 = new GameObject("spheretest2", glm::vec3(0, 0, 0));
	sphere2->scale(glm::vec3(2.5, 2.5, 2.5));
	sphere2->setMesh(sphereTest2);
	sphere2->setMaterial(runicStoneMaterial);
	//sphere2->setBehaviour(new RotatingBehaviour());
	//_world->add(sphere2);

	//The f value only takes 2 vertices
	GameObject* sphere3 = new GameObject("spheretest3", glm::vec3(8, 0, 0));
	sphere3->scale(glm::vec3(2.5, 2.5, 2.5));
	sphere3->setMesh(sphereTest3);
	sphere3->setMaterial(runicStoneMaterial);
	//sphere3->setBehaviour(new RotatingBehaviour());
	//_world->add(sphere3);

	//This one takes to many Vertices to create the f values with
	GameObject* sphere4 = new GameObject("spheretest4", glm::vec3(16, 0, 0));
	sphere4->scale(glm::vec3(2.5, 2.5, 2.5));
	sphere4->setMesh(sphereTest4);
	sphere4->setMaterial(runicStoneMaterial);
	//sphere4->setBehaviour(new RotatingBehaviour());
	//_world->add(sphere4);

    //add the floor
    GameObject* plane = new GameObject ("plane", glm::vec3(0,-2,0));
    plane->scale(glm::vec3(10,10,10));
    plane->setMesh(planeMeshDefault);
    //plane->setMaterial(planeLitMaterial);
	plane->setMaterial(terrainMaterial);
    _world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
    sphere->scale(glm::vec3(2.5,2.5,2.5));
    sphere->setMesh (sphereMeshS);
    sphere->setMaterial(litMaterial);
    sphere->setBehaviour (new RotatingBehaviour());
    //_world->add(sphere);

	GameObject* suzanna = new GameObject("suzanna", glm::vec3(8, 0, 6));
	suzanna->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	suzanna->scale(glm::vec3(2.5, 2.5, 2.5));
	suzanna->setMesh(suzannaMeshS);
	suzanna->setMaterial(litRedMaterial);
	//_world->add(suzanna);

	GameObject* box = new GameObject("cube", glm::vec3(-8, 0, 0));
	box->scale(glm::vec3(2.5, 2.5, 2.5)); 
	box->setMesh(cubeMeshF);
	box->setMaterial(litMaterial);
	//_world->add(box); 

    //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
    //It's here as a place holder to get you started.
    //Note how the texture material is able to detect the number of lights in the scene
    //even though it doesn't implement any lighting yet!

	Light* light = new Light(
		LightType::POINT, //Light Type
		glm::vec3(240.0f / 255.0f, 240.0f / 255.0f, 188.0f / 255.0f), //light Color
		glm::vec3(240.0f / 255.0f, 240.0f / 255.0f, 188.0f / 255.0f), //light diffuse color
		glm::vec3(0.2f, 0.2f, 0.2f), //light ambient color
		"light", //name
		glm::vec3(2,4,5)); // position
		
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    //light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);
	

	//set the camera behaviour after all the gameobjects are added to the world
	camera->setBehaviour(new OrbitBehaviour(40,-110,0,10,sphere));
	

}


void MyGameDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MyGameDemo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MyGameDemo::~MyGameDemo()
{
	//dtor
}

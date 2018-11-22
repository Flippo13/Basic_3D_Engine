#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ShaderUtil.h"
#include <mge/config.hpp>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "MyGame/MyGameDemo.hpp"


int main()
{
	std::cout << "Starting Game" << std::endl;

	AbstractGame* game = new MyGameDemo();
	game->initialize(); 
	game->run(); 
	return 0; 
}

 
/*
int main()
{
	sf::Window window(
		sf::VideoMode(800, 600),
		"OpenGL Window",
		sf::Style::Default,
		sf::ContextSettings(
			24,
			0,
			0,
			3,
			3
		)
	);
	window.setVerticalSyncEnabled(true); 

	GLenum glewResult = glewInit(); 
	if (glewResult != GLEW_OK) {
		std::cout << "Could not initialize GLEW" << std::endl; 
		return -1; 
	}

	GLuint programID = ShaderUtil::createProgam(config::MYGAME_SHADER_PATH + "vertexshader.vs", config::MYGAME_SHADER_PATH + "fragmentshader.fs");

	const GLfloat vertices[] = {
		//1 triangles, 3 vertices per triangle, 4 floats per vertex
		0.5f ,  -0.5f, 0,
		0.5f ,  0.5f , 0,
		-0.5f,  -0.5f, 0,
		-0.5f,   0.5f, 0,
		0.5f ,  0.5f , 0,
		-0.5f,  -0.5f, 0
	};

	const GLfloat colors[] = {
		1,0,0,
		0,1,0,
		0,0,1,
		1,0,0,
		0,1,0,
		0,0,1
	};

	const GLfloat uvs[]{
		1,1,
		1,0,
		0,1,
		0,0,
		1,0,
		0,1
	};

	//this will handle the buffer
	GLuint vertexBufferId; 
	//we need to bind the buffer to the GL_ARRAY_BUFFER
	//this will create a new array buffer for the vertex positiondata
	glGenBuffers(1, &vertexBufferId); 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); 
	//put all of our vertices data into the array buffer endpoint
	//vertexBufferId is not mentioned here because ARRAY_BUFFER is set as the one to take in the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	//now we will do the same for the colors
	GLuint colorBufferId; 
	glGenBuffers(1, &colorBufferId); 
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glClearColor(0, 0, 0, 1); 

	//run the program
	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT); 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(programID); 

		GLint squareCountIndex = glGetUniformLocation(programID, "squareCount");
		glUniform1i(squareCountIndex, 10);

		GLfloat mousePos[] = { sf::Mouse::getPosition(window).x , window.getSize().y - sf::Mouse::getPosition(window).y };
		GLint mousePosIndex = glGetUniformLocation(programID, "mousePos");
		glUniform2fv(mousePosIndex, 1, mousePos); 
		
		GLint color1Index = glGetUniformLocation(programID, "color1");
		glUniform3f(color1Index, 0, 1, 0);

		GLint color2Index = glGetUniformLocation(programID, "color2");
		glUniform3f(color2Index, 1, 1, 0);

		//tell the GPU to use this program
		GLint vertexIndex =  glGetAttribLocation(programID, "vertex"); 
		GLint uvIndex = glGetAttribLocation(programID, "uv");

		GLint offsetIndex = glGetUniformLocation(programID, "offset");
		float xOffset = 0.5f * cos(clock() / 1000.0f); 
		float yOffset = 0.5f * sin(clock() / 1000.0f);
		glUniform2f(offsetIndex, xOffset, yOffset); 

		//we need to make sure the data is put in the shader for this index
		glEnableVertexAttribArray(vertexIndex);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		//in which format should OpenGL expect this data?
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
		//do the same for the uv
		glEnableVertexAttribArray(uvIndex);
		glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
		glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(vertexIndex);
		glDisableVertexAttribArray(uvIndex);

		//and last we display everything we did
		window.display(); 

		sf::Event event; 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close(); 
			if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height); 
		}
	}

	return 0; 
}
 
  */

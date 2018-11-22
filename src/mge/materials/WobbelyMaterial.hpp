#ifndef WOBBELYMATERIAL_HPP
#define WOBBELYMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram; 
class Texture; 

class WobbelyMaterial : public AbstractMaterial
{
	public:
		WobbelyMaterial(Texture* pDiffuseTexture);
		virtual ~WobbelyMaterial();
	
		virtual void render(World* pWold, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override; 

		void setDiffuseTexture(Texture* pDiffuseTexture);

	private: 
		static ShaderProgram* _shader; 
		static void _lazyInitializeShader(); 
		
		
		static GLint _uOffset; 
		static GLint _aVertex;
		
		
		static GLint _uMVPMatrix;
		static GLint _uDiffuseTexture;
		static GLint _uTime; 
		static GLint _uPosition; 

		static GLint _aNormal;
		static GLint _aUV;
		
		Texture* _diffuseTexture;

	
		WobbelyMaterial(const WobbelyMaterial&); 
		WobbelyMaterial& operator=(const WobbelyMaterial&);
		
};

#endif
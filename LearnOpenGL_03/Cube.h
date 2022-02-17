#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "TextureLoadUtil.h"
#include "TexturePoolSinglton.h"
#include "ConstValues.h"
#include "PhysicsObject.h"
#include "Camera.h"

class Cube : public GameObject , public PhysicsObject
{
public:
	Mesh* mesh;
	Material* material;
	const int GROUP_LEN = 11;
	const std::string DIFF_PATH = TEXTURE_DEFAULT_DIFFUSE_PATH;
	const std::string SPE_PATH = TEXTURE_DEFAULT_SPECULAR_PATH;


	Cube(std::string _name, Shader* _shader, Camera* _camera,std::vector<Texture> textureVec) :GameObject(_name, _shader), PhysicsObject(_camera)
	{
		
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN,this->indices,textureVec);
	}

	Cube(std::string _name,Shader* _shader,Camera* _camera) :GameObject(_name,_shader),PhysicsObject(_camera)
	{
		
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(DIFF_PATH,TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, Camera* _camera,const std::string _texture_diffuse_path) :GameObject(_name, _shader), PhysicsObject(_camera)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(SPE_PATH, TEXTURE_SPECULAR));
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices,textureVec, this->material);
	}

	Cube(std::string _name, Shader* _shader, Camera* _camera, const std::string _texture_diffuse_path, const std::string _texture_specular_path) :GameObject(_name, _shader), PhysicsObject(_camera)
	{
		this->material = new Material(_name, _shader);
		std::vector<Texture> textureVec;
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_diffuse_path, TEXTURE_DIFFUSE));
		textureVec.push_back(TexturePoolSinglton::Instance()->CheckAndLoadTexture(_texture_specular_path, TEXTURE_SPECULAR));
		/*for (unsigned int i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i] = vertices[i] * 1000;
		}*/
		this->mesh = new Mesh(_name, _shader, this->vertices, GROUP_LEN, this->indices, textureVec, this->material);
	}

	~Cube()
	{
		if (this->mesh!=nullptr) 
		{
			delete this->mesh;
			this->mesh = nullptr;
		}

		if (this->material != nullptr) 
		{
			delete this->material;
			this->material = nullptr;
		}
	}

	void Draw() 
	{
		GameObject::Draw();
		PhysicsObject::UpdateBefore();
		this->mesh->Draw();
		
	}
private:
	std::vector<float> vertices = 
	{
	 // |       position    |         normal     |      color    |   uv
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
												  
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
												 
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
												  
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
												  
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
												 
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f, 0.0f,  1.0f
		
	};
	std::vector<unsigned int> indices=
	{
		
	};
	
};


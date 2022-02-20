#pragma once
#include "GameScriptAdapter.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "Cube.h"
#include "Model.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "SkyBox.h"

class MyTestScript:public GameScriptAdapter
{


	//ע��ʹ��ָ����ʽ��������
	//
public:

	//����ʹ�ÿղι��캯�������ű��������������ȼ���ߣ������ڳ����������͵�ǰ����������ɺ�
	MyTestScript() 
	{
		this->name = "MyTestScript";
	}

	Cube* cube;
	Model* model;

	//�ڴ˺����г�ʼ��shader��ʹ��GameHelper���뵽��ǰ������
	//ע�ⴴ��GameObject�������ֶ�������뽫�Զ�ע��
	virtual void Init() 
	{
		/*scene->input->RegisterInputModeGroup(SetInputMode);
		scene->input->RegisterCursorPosCallBack(mouse_callback);
		scene->input->RegisterToUpdate(processInput);
	*/
		Shader* skyShader = new Shader(SHADER_SKYBOX_FILE_VERTEX, SHADER_SKYBOX_FILE_FRAGMENT, SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
		GameHelper::PushShaderToCurrentScene(skyShader);
		std::cout << "Init()" << endl;
	};

	//�����ڴ˺����г�ʼ��GameObject

	virtual  void Awake() 
	{

		std::cout << "Awake()" << endl;
		//manager build something 
		
		Light* lightDirectional = new LightDirectional("lightDirectional", glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),glm::vec3(1.0f,1.0f,1.0f));
		Light* lightPoint0 = new LightPoint("lightP0", glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = new LightPoint("lightP1", glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		
		Light* lightSpot = new LightSpot("lightSpot", glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));


		std::string modelPath = GameHelper::GetTargetPath() + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = GameHelper::GetTargetPath() + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		cube = new Cube("cube1", "awesomeface.png");
		model = new Model("model1", modelPath);
		SkyBox* skybox = new SkyBox("skybox", GameHelper::FindShader(SKYBOX_SHADER_DEFAULT_NAME), texturePath);
	
		GameScript* s = GameHelper::GetGameScript("MyTestScript");
		MyTestScript* o = (MyTestScript*)s;
		//o->cube->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
		o->cube->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
	};

	//�ű�����ʱ����
	virtual void OnEnable() 
	{
		std::cout << "OnEnable()" << endl;
	};

	//���º���
	virtual void Update() 
	{
		//glm::vec3 a = model->GetAngles() + glm::vec3(0.0f, 0.0f, 0.5f);
		//model->SetAngles(a);
		model->Rotate(glm::vec3(0, 0.5f, 0));
		cube->Rotate( glm::vec3(0.5f, 0.5f, 0));
		//cube->SetPosition(glm::vec3(0.01f, 0.01f, 0)+ cube->GetPosition());
		cube->Translate(glm::vec3(0.01f, 0.01f, 0));
	};

	//���ű��������·���
	virtual void OnDisable() 
	{
		std::cout << "OnDisable()" << endl;
	};

	//���ű�������ʱ��������ͨ�������ڳ���ر�ǰ��֮������������������ж���
	virtual void OnDestroy() 
	{
		std::cout << "OnDestroy()" << endl;
	};



};


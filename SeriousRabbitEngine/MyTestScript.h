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
#include "InputBase.h"


//��ΪGlFw��һЩԭ�򣬵�ǰֻ�ܽ�Input�Ĵ���д������

#pragma region Input Declare


double lastX;
double lastY;
bool isFirstMouse = true;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//camera->ClearSpeed();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		GameHelper::GetMainCameraFromCurrentScene()->MovInZAxias(20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		GameHelper::GetMainCameraFromCurrentScene()->MovInZAxias(-20.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		GameHelper::GetMainCameraFromCurrentScene()->MovInXAxias(-15.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		GameHelper::GetMainCameraFromCurrentScene()->MovInXAxias(15.0f);
	}

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (isFirstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}

	double deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;
	double test = 1.44;
	GameHelper::GetMainCameraFromCurrentScene()->ProcessMouseMovement(deltaX, deltaY);
}




#pragma endregion




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

	//�ڴ˺����г�ʼ��shader��ʹ��GameHelper::PushShaderToCurrentScene���뵽��ǰ������
	//ע�ⴴ��GameObject�������ֶ�������뽫�Զ�ע�ᣬ��shader��Ҫ
	//�����������дһЩOpenGL���룬�⽫�����ӿڴ�����ִ��
	virtual void Init() 
	{
		//����������
		//ע�����ָ���ƶ��¼�
		glfwSetCursorPosCallback(GameHelper::GetWindowFromCurrentScene(), mouse_callback);
		//��������ģʽΪ����ʾ���ָ��
		glfwSetInputMode(GameHelper::GetWindowFromCurrentScene(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		

		//������պ�shader �����볡����
		Shader* skyShader = new Shader(SHADER_SKYBOX_FILE_VERTEX, SHADER_SKYBOX_FILE_FRAGMENT, SKYBOX_SHADER_DEFAULT_NAME, Shader::SKYBOX_SHADER);
		GameHelper::PushShaderToCurrentScene(skyShader);
		std::cout << "Init()" << endl;
	};

	//�����ڴ˺����г�ʼ��GameObject
	virtual  void Awake() 
	{

		std::cout << "Awake()" << endl;

		//����ֱ��ƹ�
		Light* lightDirectional = new LightDirectional("lightDirectional", glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),glm::vec3(1.0f,1.0f,1.0f));
		//������ƹ�
		Light* lightPoint0 = new LightPoint("lightP0", glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = new LightPoint("lightP1", glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		////�����۹�ƹ�
		Light* lightSpot = new LightSpot("lightSpot", glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));

		//GameHelper::GetTargetPath() ��ȡ��ǰ��ĿĿ¼·��������������е�Ŀ¼·��
		std::string modelPath = GameHelper::GetTargetPath() + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = GameHelper::GetTargetPath() + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		//����һ��������
		cube = new Cube("cube1", "awesomeface.png");
		//����һ��ģ��
		model = new Model("model1", modelPath);
		//GameHelper::FindShader �������ƻ�ȡshader
		//������պ�
		SkyBox* skybox = new SkyBox("skybox", GameHelper::FindShaderFromCurrentScene(SKYBOX_SHADER_DEFAULT_NAME), texturePath);
		//���ڸ���ʱ����������� ���ͷ��ڴ棬������Ϸ�����б����Ƴ�
		//cube->Destroy();
		//���ڸ���ʱ���ô����� �������ͷ��ڴ�
		//cube->Disable();
		//���ݽű�����ȡ�ű�
		GameScript* s = GameHelper::GetGameScriptFromCurrentScene("MyTestScript");
		MyTestScript* o = (MyTestScript*)s;
		//��������ű�
		//o->Disable();
		//����scale ����Ҫ����update��
		//o->cube->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

		//���Ŵ�����  ����Ҫ����update��
		//o->cube->Scale(glm::vec3(2.0f, 2.0f, 2.0f));

		//�������ô�����
		//cube->Enable();

	};

	//�ű�����ʱ����
	virtual void OnEnable() 
	{
		std::cout << "OnEnable()" << endl;
		
	};

	//���º���
	virtual void Update() 
	{
		//����������
		processInput(GameHelper::GetWindowFromCurrentScene());

		//����position
		//glm::vec3 a = model->GetAngles() + glm::vec3(0.0f, 0.0f, 0.5f);
		//����angles
		//model->SetAngles(a);
		
		//��ת������
		model->Rotate(glm::vec3(0, 0.5f, 0));
		cube->Rotate( glm::vec3(0.5f, 0.5f, 0));
		cube->SetPosition(glm::vec3(0.01f, 0.01f, 0)+ cube->GetPosition());
		//�ƶ�������
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


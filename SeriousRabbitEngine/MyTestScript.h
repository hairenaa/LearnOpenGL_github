﻿#pragma once
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


//因为GlFw的一些原因，当前只能将Input的代码写在类外

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


	//注意使用指针形式创建对象
	//
public:

	//可以使用空参构造函数来给脚本命名，他的优先级最高，发生在场景加载器和当前场景构造完成后
	//:GameScriptAdapter(true) 参数为ture表示将自动将脚本注册到当前场景，否则不进行任何操作
	MyTestScript() :GameScriptAdapter(true)
	{
		this->name = "MyTestScript";
		//:GameScriptAdapter(true)使用false参数，并创建一个新场景，将此脚本加入到场景中，最后将场景从当前默认default场景到新场景
		/*GameHelper::GetSceneLoader()->NewSceneInstance("DefaultScene")->PushScript(this);
		GameHelper::GetSceneLoader()->ChangeSceneNext();*/
	}

	Cube* cube;
	Model* model;

	
	//注意创建GameObject对象是手动无需加入将自动注册
	//在这里你可以写一些OpenGL代码，这将会在视口创建后执行
	virtual void Init() 
	{
		//场景的输入
		//注册鼠标指针移动事件
		glfwSetCursorPosCallback(GameHelper::GetWindowFromCurrentScene(), mouse_callback);
		//设置输入模式为不显示鼠标指针
		glfwSetInputMode(GameHelper::GetWindowFromCurrentScene(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		std::cout << "Init()" << endl;
	};

	//建议在此函数中初始化GameObject
	virtual  void Awake() 
	{

		std::cout << "Awake()" << endl;

		//Light类最后一个参数color时一个三维分量，每一维的数值都与光的强度有关
		//创建直射灯光
		Light* lightDirectional = new LightDirectional("lightDirectional", glm::vec3(9.2f, 3.0f, 40.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),glm::vec3(1.0f,1.2f,1.0f));
		//创建点灯光
		Light* lightPoint0 = new LightPoint("lightP0", glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(1.0f, 0.0f, 0.0f));
		Light* lightPoint1 = new LightPoint("lightP1", glm::vec3(0.0f, 3.0f, 0.0f),
			glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(0.0f, 1.0f, 0.0f));
		//创建聚光灯光
		Light* lightSpot = new LightSpot("lightSpot", glm::vec3(0, 0, 4.0f),
			glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0), glm::vec3(0.0f, 1.0f, 1.0f));

		std::string rootDir = WinApiUtil::GetProjectRootPath();
		std::string modelPath = rootDir + "\\model\\Crysis\\nanosuit.obj";
		std::string texturePath = rootDir + "\\texture\\skybox\\default";
		std::cout << "modelPath is :" << modelPath << endl;
		std::cout << "texturePath is :" << texturePath << endl;

		//创建一个立方体
		cube = new Cube("cube1", "awesomeface.png");
		//创建一个模型
		model = new Model("model1", modelPath);
		//GameHelper::FindShader 根据名称获取shader
		//创建天空盒
		SkyBox* skybox = new SkyBox("skybox", texturePath);
		//会在更新时销毁这个物体 会释放内存，并在游戏物体列表中移除
		//cube->Destroy();
		//会在更新时禁用此物体 但不会释放内存
		//cube->Disable();
		//根据脚本名获取脚本
		GameScript* s = GameHelper::GetGameScriptFromCurrentScene("MyTestScript");
		MyTestScript* o = (MyTestScript*)s;
		//禁用这个脚本
		//o->Disable();
		//设置scale ：不要放在update中
		//o->cube->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

		//缩放此物体  ：不要放在update中
		//o->cube->Scale(glm::vec3(2.0f, 2.0f, 2.0f));

		//重新启用此物体
		//cube->Enable();

	};

	//脚本启用时发生
	virtual void OnEnable() 
	{
		std::cout << "OnEnable()" << endl;
		
	};

	//更新函数
	virtual void Update() 
	{
		//处理按键输入
		processInput(GameHelper::GetWindowFromCurrentScene());

		//设置position
		//glm::vec3 a = model->GetAngles() + glm::vec3(0.0f, 0.0f, 0.5f);
		//设置angles
		//model->SetAngles(a);
		
		//旋转此物体
		model->Rotate(glm::vec3(0, 0.5f, 0));
		cube->Rotate( glm::vec3(0.5f, 0.5f, 0));
		cube->SetPosition(glm::vec3(0.01f, 0.01f, 0)+ cube->GetPosition());
		//移动此物体
		cube->Translate(glm::vec3(0.01f, 0.01f, 0));
	};

	//当脚本被禁用时发生
	virtual void OnDisable() 
	{
		std::cout << "OnDisable()" << endl;
	};

	//当脚本被销毁时发生，这通常发生在程序关闭前，之后将由引擎管理销毁所有对象
	virtual void OnDestroy() 
	{
		std::cout << "OnDestroy()" << endl;
	};


};


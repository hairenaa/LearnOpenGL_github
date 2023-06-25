#include "SceneLoader.h"


SceneLoader* SceneLoader::instance = nullptr;

SceneLoader*  SceneLoader::Instance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		throw new exception("no instance of SceneLoader!!");
	}
}

SceneLoader::SceneLoader(GLFWwindow* window, unsigned int width, unsigned int height)
{
	this->window = window;
	this->Height = height;
	this->Width = width;
	
	NewSceneInstance(SCENE_DEFAULT_NAME);
	instance = this;
}
SceneLoader::~SceneLoader()
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* scene = scenes[i];
		scene->Delete<Scene>(scene);
	}
}

Scene* SceneLoader::NewSceneInstance(std::string _name)
{
	Scene* scene = new Scene(this->window, _name, this->Width, this->Height);
	scenes.push_back(scene);
	return scene;
}

Scene* SceneLoader::LoadSceneInstance(std::string _name)
{
	//�޸�
	/*
	���������������ڸ���ģ�飬��ζ����Ҫһ����������������߿��ٿ������������Ҫ��������������Ĺ��ܣ�����������ʱ�����������Ϊ������������壬����������ƶ�������UI����������ת���Ų��ʵ�UI��������Ҫ����صı��泡����UI���������Խ��˳������л�ΪJSON�ļ��������UI����Ӧ����JSON�ķ�ʽ���浽settings.json�С����⣬ÿ������������ʱ��sceneloader��Ҫ�ڳ�ʼ��ʱ����settings����ָʾ�ĳ����ļ����������´���һ��������
	ע�����Բο�learnOpenGL�Ľ̳̣�����ض�����ʵս�½ڡ�
	����shader��
	https://www.zhihu.com/question/61140114#:~:text=It%27s%20very%20simple.%20You%20just%20use%20glUseProgram,%28program_id%29%20switch%20between%20shaders%20during%20the%20run-time%20step.
	����c++���л���
	https://www.zhihu.com/question/266845585 
	��������Ч����
	https://learnopengl-cn.github.io/06%20In%20Practice/2D-Game/06%20Particles/
	���ڹ���������
	https://learnopengl-cn.github.io/08%20Guest%20Articles/2020/01%20Skeletal%20Animation/
	learnOpenGL������
	https://learnopengl-cn.github.io/
	���������޴����Ŀ����С�����������
	*/

	std::string fileName = ConfValues::Instance()->GetConfigValue(CONF_SCENE_CURRENT_FILE_NAME_KEY);
	std::string loadPath = WinApiUtil::GetProjectRootPath() + "//" + fileName;
	//Serialization::Deserialize(loadPath) �����л�Ϊscene����
	//Scene* scene= ;
	return nullptr;
}


Scene* SceneLoader::GetCurrentScene()
{
	if (scenes.empty())
	{
		throw new exception("no scene in this window!!");
	}
	if (this->Index >= 0 && this->Index < scenes.size())
	{
		return this->scenes[this->Index];
	}
	return this->scenes[0];


}
void SceneLoader::ChangeSceneNext()
{

	if (this->Index < this->scenes.size() - 1)
	{
		this->Index++;
	}

}

void SceneLoader::ChangeSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			this->Index = i;
			break;
		}
	}
}

Scene* SceneLoader::GetSceneByName(std::string _name)
{
	for (unsigned int i = 0; i < scenes.size(); i++)
	{
		Scene* sce = scenes[i];
		if (sce->name == _name)
		{
			return sce;
		}
	}
}



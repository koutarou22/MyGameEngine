#include "TestScene.h"
#include "Engine//Input.h"

TestScene::TestScene(GameObject* parent):GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	/*if (Input::IsKeyDown)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_������);
	}*/
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
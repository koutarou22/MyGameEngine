#include "TestScene.h"
#include "Engine//Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent):GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	if (Input::IsKey(DIK_P))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

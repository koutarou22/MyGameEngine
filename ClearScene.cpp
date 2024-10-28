#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/Texture.h";
#include "Engine/SceneManager.h"
#include "Enemy.h"

ClearScene::ClearScene(GameObject* parent) :GameObject(parent, "ClearScene")
{
}

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
	Instantiate<Enemy>(this);
	if (Input::IsKey(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
}

void ClearScene::Release()
{
}

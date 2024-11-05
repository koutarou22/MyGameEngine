#include "GameOverScene.h"
#include "Engine/Input.h"
#include "Engine/Texture.h";
#include "Engine/SceneManager.h"
#include "Enemy.h"

GameOverScene::GameOverScene(GameObject* parent) :GameObject(parent, "GameOverScene")
{
}

void GameOverScene::Initialize()
{
	pSprite = new Sprite;
	pSprite->Load("Assets/GameOver.png");
}

void GameOverScene::Update()
{
	if (Input::IsKey(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOverScene::Draw()
{
	pSprite->Draw(transform_);
}

void GameOverScene::Release()
{
	pSprite->Release();
}

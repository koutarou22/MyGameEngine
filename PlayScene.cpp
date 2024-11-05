#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
	count = 4000;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	if (FindObject("Enemy") == nullptr)
	{
		count--;
 		if(count <= 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_CLEAR);
		}
	}
	if (FindObject("Player") == nullptr)
	{
		count--;
		if (count <= 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		}
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

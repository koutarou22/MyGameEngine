#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/Texture.h";
#include "Engine/SceneManager.h"


TitleScene::TitleScene(GameObject* parent) :GameObject(parent, "TitleScene"), hImage_(-1)
{
}

void TitleScene::Initialize()
{
	pSprite = new Sprite;
	pSprite->Load("Assets/Title.png");
}

void TitleScene::Update()
{
	if (Input::IsKey(DIK_P))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	pSprite->Draw(transform_);
}

void TitleScene::Release()
{
	pSprite->Release();
}

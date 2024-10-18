#include "SceneManager.h"
#include "../TestScene.h"
#include "../PlayScene.h"
#include "Direct3D.h"
#include "../Model.h"

SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;//一番最初に選択されるSceneえ
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		
		for (auto itr : childList_)
		{
			itr->ReleaseSub();
			SAFE_DELETE(itr);
			childList_.clear();
		}
		Model::Release();
		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;

		}
		//無事シーンを生成できたら、カレントシーンを更新
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
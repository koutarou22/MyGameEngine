#include "SceneManager.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "Direct3D.h"
#include "../Model.h"
#include "../TitleScene.h"
#include "../ClearScene.h"
#include "../GameOverScene.h"

SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;//一番最初に選択されるScene
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		
		auto Scene = childList_.begin();
		(*Scene)->ReleaseSub();
		SAFE_DELETE(*Scene);
		childList_.clear();

		Model::Release();
		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
		case SCENE_ID_GAMEOVER:Instantiate<GameOverScene>(this); break;
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
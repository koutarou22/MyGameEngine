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
	currentSceneID_ = SCENE_ID_TITLE;//��ԍŏ��ɑI�������Scene
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		
		auto Scene = childList_.begin();
		(*Scene)->ReleaseSub();
		SAFE_DELETE(*Scene);
		childList_.clear();

		Model::Release();
		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
		case SCENE_ID_GAMEOVER:Instantiate<GameOverScene>(this); break;
		}
		//�����V�[���𐶐��ł�����A�J�����g�V�[�����X�V
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
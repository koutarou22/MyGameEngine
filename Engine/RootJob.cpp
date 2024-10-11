#include "RootJob.h"
#include "SceneManager.h"

RootJob::RootJob()
	:GameObject(nullptr, "RootObject")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	////PlaySceneƒNƒ‰ƒX‚à‚¨‚»‚ç‚­GameObject‚ðŒp³
	//PlayScene* pPlayScene;
	//pPlayScene = new PlayScene(this);
	//pPlayScene->Initialize();
	//childList_.push_back(pPlayScene);
	Instantiate<SceneManager>(this);
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
	
}

void RootJob::Release()
{
}

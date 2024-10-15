#include "ChildOden.h"
#include"Model.h"

ChildOden::ChildOden(GameObject* parent)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	Model::Load("Assets/Oden3.fbx");
	//pFbx = new FBX;
	/*pFbx->Load("Assets/Oden3.fbx");*/
	transform_.scale_.x = 2.2;
	transform_.scale_.y = 2.2;
	transform_.scale_.z = 2.2;
	/*transform_.position_.x = 1.0;
	transform_.position_.y = 1.0;*/
	transform_.position_.z = -1.0;
}

void ChildOden::Update()
{
	transform_.rotate_.y += 1.0f;
	transform_.position_.y += 0.01f;

	if (transform_.position_.y > 5.0f)
	{
		KillMe();
	}
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
	Model::Release();
	/*pFbx->Release();*/
}

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
	transform_.scale_.x = 1.2;
	transform_.scale_.y = 1.2;
	transform_.scale_.z = 1.2;
	/*transform_.position_.x = 1.0;
	transform_.position_.y = 1.0;*/
	transform_.position_.z = -1.0;
}

void ChildOden::Update()
{
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
	/*pFbx->Release();*/
}

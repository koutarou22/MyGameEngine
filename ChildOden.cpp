#include "ChildOden.h"


ChildOden::ChildOden(GameObject* parent)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	pFbx = new FBX;
	pFbx->Load("Assets/Oden3.fbx");
	transform_.scale_.x = 1.2;
	transform_.scale_.y = 1.2;
	transform_.scale_.z = 1.2;
	transform_.position_.x = 1.0;
	transform_.position_.y = 1.0;
}

void ChildOden::Update()
{
}

void ChildOden::Draw()
{
	pFbx->Draw(transform_);
}

void ChildOden::Release()
{
	pFbx->Release();
}

#include "ChildOden.h"
#include"Model.h"
#include"Enemy.h"
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

	Enemy* pEnemy = (Enemy*)FindObject("Enemy");
	float r1 = 0.1;
	float r2 = 0.5;

	XMFLOAT3 P1 = pEnemy->GetPosition();
	XMFLOAT3 P2 = transform_.position_;

	XMVECTOR Dist = XMVector3Length(XMVectorSet(P1.x, P1.y, P1.z, 1) - XMVectorSet(P2.x, P2.y, P2.z, 1));
	float d = XMVectorGetX(Dist);

	if (d <= r1 + r2)
	{
		KillMe();
	}

	if (transform_.position_.y > 3.8f)
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
	//Model::Release();
	/*pFbx->Release();*/
}

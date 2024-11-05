#include "Bullet.h"
#include"Model.h"
#include"Enemy.h"
#include"SphereCollider.h"
#include "Player.h"
Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel(-1)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel = Model::Load("Assets/Oden3.fbx");
	//pFbx = new FBX;
	/*pFbx->Load("Assets/Oden3.fbx");*/
	/*transform_.position_.x = 1.0;
	transform_.position_.y = 1.0;*/
	transform_.position_.z = -1.0;
	transform_.rotate_.z  = 180.0f;
	SphereCollider* col = new SphereCollider(0.5f);
	this->AddCollider(col);
}

void Bullet::Update()
{
	
	transform_.rotate_.y += 1.0f;
	transform_.position_.y -= 0.01f;

	//float r1 = 0.1;
	//float r2 = 0.5;

	//XMFLOAT3 P1 = pEnemy->GetPosition();
	//XMFLOAT3 P2 = transform_.position_;

	//XMVECTOR Dist = XMVector3Length(XMVectorSet(P1.x, P1.y, P1.z, 1) - XMVectorSet(P2.x, P2.y, P2.z, 1));
	//float d = XMVectorGetX(Dist);

	//if (d <= r1 + r2)
	//{
	//	KillMe();
	//}

	/*if (transform_.position_.y < 3.8f)
	{
		KillMe();
	}*/
}

void Bullet::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Bullet::Release()
{
	//Model::Release();
	/*pFbx->Release();*/
}

void Bullet::OnCollision(GameObject* pTarget)
{
	Player* pPlayer = (Player*)FindObject("Player");
	if (pPlayer && pTarget == pPlayer)
	{
		pPlayer->KillMe();
		KillMe();
	}
}

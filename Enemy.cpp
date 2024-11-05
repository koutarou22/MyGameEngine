#include "Enemy.h"
#include "ChildOden.h"
#include "Model.h"
#include "Engine/Input.h"
#include "SphereCollider.h"
#include "Bullet.h"


Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy")/*, pFbx(nullptr)*/, hModel(-1)
{
	count = 2000;
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
    hModel = Model::Load("Assets/red.fbx");
	assert(hModel != -1);
	transform_.position_.y = 1.9;
	transform_.scale_.x = 0.7;
	transform_.scale_.y = 0.7;
	transform_.scale_.z = 0.7;
	SphereCollider* col = new SphereCollider(0.5f);
	this->AddCollider(col);
}

void Enemy::Update()
{
	static int dt;
	dt++;
	float ntime = dt / (80.f*10.0f) - 1.0;
	static float sn = sin(ntime);
	transform_.position_.x = 4.0 * sin(ntime);

    if (count > 0)
    {
        count--;
        if (count == 0)
        {
            GameObject* e= Instantiate<Bullet>(this);
            e->SetPosition(transform_.position_);
            e->SetScale(1.0, 1.0, 1.0);

            count = 2000;
        }
    }
}

void Enemy::Draw()
{
    Model::SetTransform(hModel, transform_);
    Model::Draw(hModel);
}

void Enemy::Release()
{
	
}

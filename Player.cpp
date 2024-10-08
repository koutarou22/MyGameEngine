#include "Player.h"
#include "ChildOden.h"

Player::Player(GameObject* parent)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx = new FBX;
	pFbx->Load("Assets/oden3.fbx");
	this->transform_.scale_.x = 3.0;
	this->transform_.scale_.y = 3.0;
	this->transform_.scale_.z = 3.0;
	Instantiate<ChildOden>(this);

	
}

void Player::Update()
{
	transform_.rotate_.y += 1;
	if (transform_.rotate_.y > 60 * 10)
	{
		KillMe();
	}
}

void Player::Draw()
{
	pFbx->Draw(transform_);
}

void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}
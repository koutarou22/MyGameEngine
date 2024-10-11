#include "Player.h"
#include"ChildOden.h"
#include "Engine/Input.h"
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx(nullptr)
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
	//transform_.rotate_.y += 1.0f;
	if (Input::IsKey(DIK_A)) {
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKey(DIK_SPACE)) {
		Instantiate<ChildOden>(this);
	}
}

void Player::Draw()
{
	pFbx->Draw(transform_);
}

void Player::Release()
{
	pFbx->Release();
}
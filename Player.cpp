#include "Player.h"
#include"ChildOden.h"
#include "Engine/Input.h"
#include"Model.h"
Player::Player(GameObject* parent)
	:GameObject(parent, "Player")/*, pFbx(nullptr)*/,hModel(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel = Model::Load("Assets/oden3.fbx");

	/*pFbx = new FBX;
	pFbx->Load("Assets/oden3.fbx");*/
	this->transform_.scale_.x = 3.0;
	this->transform_.scale_.y = 3.0;
	this->transform_.scale_.z = 3.0;
	/*Instantiate<ChildOden>(this);*/
}

void Player::Update()
{
	transform_.rotate_.y += 0.01f;
	if (Input::IsKey(DIK_A)) {
		transform_.position_.x -= 0.001f;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.position_.x += 0.001f;
	}
	if (Input::IsKey(DIK_SPACE)) 
	{
		GameObject * p = Instantiate<ChildOden>(this);
		p->SetPosition(transform_.position_);
		p->SetScale(2.2, 2.2, 2.2);
	}
}

void Player::Draw()
{
	/*pFbx->Draw(transform_);*/
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	/*pFbx->Release();*/
}
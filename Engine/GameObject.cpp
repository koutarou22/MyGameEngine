#include "GameObject.h"
#include "Direct3D.h"
#include "../SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name), isDead_(false),pCollider_(nullptr)
{
	if (parent != nullptr) {
		this->transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::Release()
{
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr : childList_)
	{
		itr->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr!= childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_)
	{
		itr->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(string objName)//������������
{
	GameObject* rootJob = GetRootJob();
	GameObject* res = rootJob->FindChildObject(objName);
	return(res);
}

GameObject* GameObject::GetRootJob()
{
	if(pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(string objName)
{
	if (this->objectName_ == objName)
	{
		return this;
	}
	else
	{
		for (auto itr : childList_)
		{
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr)
			{
				return obj;
			}
			
		}
		return nullptr;
	}
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)//��Έ�̔���
{
	if (this->pCollider_ == nullptr || pTarget->pCollider_ == nullptr || this == pTarget)
		return;
	XMVECTOR me = XMLoadFloat3(&(transform_.position_));
	XMVECTOR ta = XMLoadFloat3(&(pTarget->transform_.position_));
	//�����ƃ^�[�Q�b�g�̃R���C�_�[���m�̓����蔻���`��
	//this->position��pTarget->position�̋��� < this->pCollider.radius_+pTarget->pCollider.radius_
	float dist = XMVectorGetX(XMVector2Length(me - ta));
	float rDist = this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius();
	if(dist <= rDist)
	{
		//onCollisiong
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//�����ƃ^�[�Q�b�g�̓����蔻��
	//�����ƃ^�[�Q�b�g�̎q�I�u�W�F�N�g�S���̓����蔻��i�ċA�j
}

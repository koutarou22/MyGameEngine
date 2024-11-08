#pragma once
#include <string>
#include<list>
#include"Transform.h"
#include <string>

class SphereCollider;
using std::string;
class GameObject
{
	bool isDead_;
protected:
	std::list<GameObject*>childList_;//オブジェクトの名前
	Transform             transform_;
	GameObject*	            pParent_;
	std::string          objectName_;
	SphereCollider*       pCollider_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	void SetPosition(XMFLOAT3 position)
	{
		transform_.position_ = position;
	}
	void SetPosition(float x, float y, float z)
	{
		SetPosition(XMFLOAT3(x, y, z));
	}

	void KillMe();

	void SetScale(float sx, float sy, float sz)
	{
		transform_.scale_ = { sx,sy,sz };
	}
	void SetRotateX(float xrotate) { transform_.rotate_.x = xrotate; }
	void SetRotateY(float yrotate) { transform_.rotate_.y = yrotate; };
	void SetRotateZ(float zrotate) { transform_.rotate_.z = zrotate; };

	GameObject* FindObject(string objName);
	GameObject* GetRootJob();
	GameObject* FindChildObject(string objName);

	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);//他の判定を参照
	void RoundRobin(GameObject* pTarget);
	virtual void OnCollision(GameObject* pTarget) {};//空を呼ぶのもコストがかかる

	//template <typename T>//クラスならclassとかく　ほぼ同じ
	template <class T> //tポインタ型　仮引数のクラスに合わせた引数
	T* Instantiate(GameObject* pParent)
	{
		T* pTmp = new T(pParent);
		if (pTmp != nullptr)
		{
			pTmp->Initialize();
			childList_.push_back(pTmp);
		}
		return pTmp;
	}
};


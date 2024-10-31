#pragma once
#include "Engine//GameObject.h"
#include "Engine/Fbx.h"
class Bullet :
    public GameObject
{
    /* FBX* pFbx;*/
    int hModel;
public:
    //�R���X�g���N�^
    Bullet(GameObject* parent);

    //�f�X�g���N�^
    ~Bullet();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void OnCollision(GameObject* pTarget) override;

    XMFLOAT3 GetPosition() { return(transform_.position_); }
};


#pragma once
#include "Engine//GameObject.h"
#include "Engine/Fbx.h"
class ChildOden :
    public GameObject
{
   /* FBX* pFbx;*/
    int hModel;
public:
    //�R���X�g���N�^
    ChildOden (GameObject* parent);

    //�f�X�g���N�^
    ~ChildOden ();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


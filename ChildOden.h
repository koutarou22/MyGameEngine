#pragma once
#include "Engine//GameObject.h"
class ChildOden :
    public GameObject
{
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


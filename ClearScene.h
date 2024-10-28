#pragma once
#include "Engine//GameObject.h"
class ClearScene :
    public GameObject
{
public:
    ClearScene(GameObject* parent);
    ~ClearScene();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


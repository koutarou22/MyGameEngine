#pragma once
#include "Engine//GameObject.h"
class PlayScene :
    public GameObject
{
    int count;
public:
    PlayScene(GameObject* parent);
    ~PlayScene();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


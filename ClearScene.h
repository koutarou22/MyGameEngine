#pragma once
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
class ClearScene :
    public GameObject
{
    Sprite* pSprite;
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


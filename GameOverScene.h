#pragma once
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
class GameOverScene :
    public GameObject
{
    Sprite* pSprite;
public:
    GameOverScene(GameObject* parent);
    ~GameOverScene();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


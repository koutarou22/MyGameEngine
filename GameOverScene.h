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

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};


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

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};


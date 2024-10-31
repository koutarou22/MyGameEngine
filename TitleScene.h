#pragma once
#include "Engine//GameObject.h"
#include "Engine/Sprite.h"

class TitleScene : public GameObject
{
    int hImage_;
    Sprite* pSprite;
public:
    TitleScene(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

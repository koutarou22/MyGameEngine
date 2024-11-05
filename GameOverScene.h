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

    //‰Šú‰»
    void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;
};


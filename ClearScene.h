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

    //‰Šú‰»
    void Initialize() override;

    //XV
    void Update() override;

    //•`‰æ
    void Draw() override;

    //ŠJ•ú
    void Release() override;
};


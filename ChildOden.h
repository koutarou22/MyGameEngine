#pragma once
#include "Engine//GameObject.h"
#include "Engine/Fbx.h"
class ChildOden :
    public GameObject
{
    FBX* pFbx;
public:
    //コンストラクタ
    ChildOden (GameObject* parent);

    //デストラクタ
    ~ChildOden ();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};


#pragma once
#include "Engine//GameObject.h"
#include "Engine/Fbx.h"
class ChildOden :
    public GameObject
{
   /* FBX* pFbx;*/
    int hModel;
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

    void OnCollision(GameObject* pTarget) override;

    XMFLOAT3 GetPosition() { return(transform_.position_); }
};


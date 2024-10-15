#pragma once
#include"Engine//GameObject.h"
#include"Engine//Fbx.h"
class FBX;
class Player :
    public GameObject
{
	//FBX* pFbx;
    int hModel;
public:

	//コンストラクタ
	Player(GameObject* parent);
    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};


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

	//�R���X�g���N�^
	Player(GameObject* parent);
    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};


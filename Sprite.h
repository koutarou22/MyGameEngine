#pragma once
#include <vector>
#include"vector"
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"



using namespace DirectX;
using std::vector;


struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Sprite
{
	uint64_t vertexNum_;//頂点数
	vector<VERTEX> vertices_;
	uint64_t indexNum_;//頂点数
	vector<int> indices_;
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;//テクスチャへのポインタ

public:
	Sprite();//コンストラクタ
	~Sprite();//デストラクタ
    HRESULT Load(std::string fileName);//初期化用
	void Draw(Transform & transform);//描画関数
	void Release();//解放処理
private:
	void InitVertexDate();
	HRESULT CreateVertexDate();

	void InitIndexDate();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffr();

	HRESULT LoadTexture(std::string fileName);

	void PassDateToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBuffrToPipeline();

};




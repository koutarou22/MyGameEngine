#include "Quad.h"
#include "Camera.h"
using namespace Direct3D;

HRESULT hr;
Quad::Quad()
{
}

Quad::~Quad()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

HRESULT Quad::Initialize()
{
	// 頂点情報 
	XMVECTOR vertices[] =
	{

		//四角錐
		XMVectorSet(-2.0f,  0.0f, 1.0f, 0.0f),	//左上
		XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f),    //天辺
		XMVectorSet(2.0f,  0.0f, 1.0f, 0.0f),	//右上
		XMVectorSet(1.0f, 0.0f, -2.0f, 0.0f),	//右下
		XMVectorSet(-1.0f, 0.0f, -2.0f, 0.0f),	//左下

		////五角形(ホームベース型)
		//XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),//左上
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	//上
		//XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	//右上
		//XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),	//右下
		//XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f),	//左下
	
		//四角形
		//XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),//左上
		//XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	//右上
		//XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	//右下
		//XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),//左下	
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗",L"Error", MB_OK);
		return hr;
	}

	////インデックス情報 四角形
	//int index[] = { 0,2,3, 0,1,2 };
	////インデックス情報　五角形
	//int index[] = { 0,1,2, 0,2,3, 0,3,4 };
	//インデックス情報　六角形
	/*int index[] = { 0,1,2, 0,2,3, 0,3,4, 0,4,5 };*/

	//インデックス情報　四角錐
	//int index[] = { 0,1,2, 0,2,3, 1,2,4, 2,3,4, 0,1,4};
	int index[] = {4,1,3, 4,0,3, 0,1,4, 0,1,2, 0,2,3, 2,1,3};
	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"インデックスバッファの作成に失敗", L"Error", MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗", L"Error", MB_OK);
		return hr;
	}
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	////コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4/*4分のπ　45度*/, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列　05 22   2 14 55カクニン

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix* Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	//頂点バッファ
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(18, 0, 0);//三角化した時の頂点の数
}

void Quad::Release()
{
}
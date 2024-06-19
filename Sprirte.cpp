#include "Sprite.h"
#include "Camera.h"
using namespace Direct3D;

HRESULT hr;
Sprite::Sprite()
	:pTexture_(nullptr), pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),vertexNum_(0),indexNum_(0)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize()
{

	HRESULT hr;
	// 頂点情報
	//VERTEX vertices[] =
	//{
	//	{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{ 1.0f, -1.0f, -1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},

	//

	//};

	////インデックス情報
	//int index[] = {
	// 0,  1,  2,     3,  2,  1,
	// 4,  5,  6,     7,  6,  5,
	// 8,  9, 10,    11, 10,  9,
	//12, 13, 14,    15, 14, 13,
	//16, 18, 17,    19, 17, 18,
	//20, 21, 22,    23, 22, 21, };

	//// 頂点データ用バッファの設定
	//D3D11_BUFFER_DESC bd_vertex;
	//bd_vertex.ByteWidth = sizeof(vertices);
	//bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	//bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd_vertex.CPUAccessFlags = 0;
	//bd_vertex.MiscFlags = 0;
	//bd_vertex.StructureByteStride = 0;
	//D3D11_SUBRESOURCE_DATA data_vertex;
	//data_vertex.pSysMem = vertices;
	//hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	///*hr = E_FAIL;*/
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, L"頂点バッファの作成に失敗", L"Error", MB_OK);
	//	return hr;
	//}


	//D3D11_BUFFER_DESC   bd;
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(index);
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;

	//D3D11_SUBRESOURCE_DATA InitData;
	//InitData.pSysMem = index;
	//InitData.SysMemPitch = 0;
	//InitData.SysMemSlicePitch = 0;
	//hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);

	///*hr = E_FAIL;*/
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, L"インデックスバッファの作成に失敗", L"Error", MB_OK);
	//	return hr;
	//}

	////コンスタントバッファ作成
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;

	//// コンスタントバッファの作成
	//hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	///*hr = E_FAIL;*/
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, L"コンスタントバッファの作成に失敗", L"Error", MB_OK);
	//	return hr;
	//}

	//pTexture_ = new Texture;
	//pTexture_->Load("Assets\\Dies.jpg");

	//頂点情報
	InitVertexDate();
	if(FAILED(CreateVertexDate()))
	{
		return E_FAIL;
	}

	InitIndexDate();
	if (FAILED(CreateIndexBuffer()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateConstantBuffr()))
	{
		return E_FAIL;
	}

	if (FAILED(LoadTexture()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	////コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4/*4分のπ　45度*/, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列　05 22   2 14 55カクニン

	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(36, 0, 0);//三角化した時の頂点の数
}

void Sprite::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

void Sprite::InitVertexDate()
{
	vertices_ =
	{
		{{ -1.0f,  1.0f, 0.0f,0.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) },
		{{  1.0f,  1.0f, 0.0f ,0.0f},  XMVectorSet(1.0, 0.0, 0.0, 0.0) },
		{{ 1.0f, -1.0f, 0.0f ,0.0f},  XMVectorSet(1.0, 1.0, 0.0, 0.0) },
		{{  -1.0f, -1.0f, 0.0f ,0.0f},  XMVectorSet(0.0, 1.0, 0.0, 0.0)},
	};
	vertexNum_ = vertices_.size();

}

HRESULT Sprite::CreateVertexDate()
{
	return E_NOTIMPL;
}

void Sprite::InitIndexDate()
{
	

}

HRESULT Sprite::CreateIndexBuffer()
{
	//// 頂点データ用バッファの設定
   D3D11_BUFFER_DESC bd_vertex;
   bd_vertex.ByteWidth = sizeof(VERTEX)* vertexNum_;
   bd_vertex.Usage = D3D11_USAGE_DEFAULT;
   bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   bd_vertex.CPUAccessFlags = 0;
   bd_vertex.MiscFlags = 0;
   bd_vertex.StructureByteStride = 0;
   D3D11_SUBRESOURCE_DATA data_vertex;
   data_vertex.pSysMem = vertices_.date();//配列のアドレスをゲットして代入
   hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
/*hr = E_FAIL;*/
   if (FAILED(hr))
   {
	MessageBox(NULL, L"頂点バッファの作成に失敗", L"Error", MB_OK);
	return hr;
   }

   return S_OK;

}

HRESULT Sprite::CreateConstantBuffr()
{
	return E_NOTIMPL;
}

HRESULT Sprite::LoadTexture()
{
	return E_NOTIMPL;
}

void Sprite::PassDateToCB(DirectX::XMMATRIX& worldMatrix)
{
}

void Sprite::SetBuffrToPipeline()
{
}

#include "Sprite.h"
#include "Camera.h"
#include<filesystem>
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

HRESULT Sprite::Load(std::string fileName)
{
	InitVertexDate();
	if (FAILED(CreateVertexDate()))
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

	if (FAILED(LoadTexture(fileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Sprite::Draw(Transform& transform)
{
	transform.Calclation();
	PassDateToCB(transform.GetWorldMatrix());
	SetBuffrToPipeline();
	Direct3D::pContext->DrawIndexed(6, 0, 0);//三角化した時の頂点の数
}

void Sprite::Release()//OK
{
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
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_.data();
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗", L"Error", MB_OK);
		return hr;
	}
}

void Sprite::InitIndexDate()
{
	indices_ = { 0,2,3,0,1,2 };
	indexNum_ = indices_.size();

}

HRESULT Sprite::CreateIndexBuffer()
{
	HRESULT hr;

	D3D11_BUFFER_DESC  bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitDate;
	InitDate.pSysMem = indices_.data();
	InitDate.SysMemPitch = 0;
	InitDate.SysMemSlicePitch = 0;


	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitDate, &pIndexBuffer_);

	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"インデックスバッファの作成に失敗", L"Error", MB_OK);
		return hr;
	}
	return S_OK;

}

HRESULT Sprite::CreateConstantBuffr()
{
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	HRESULT hr;
	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	/*hr = E_FAIL;*/
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗", L"Error", MB_OK);
		return hr;
	}
}

HRESULT Sprite::LoadTexture(std::string filename)
{

	namespace fs = std::filesystem;
	pTexture_ = new Texture;
	assert(fs::is_regular_file(filename));

	HRESULT hr;
	hr = pTexture_->Load(filename);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャの作成に失敗", L"Error", MB_OK);
		return hr;
	}
	return S_OK;
}

void Sprite::PassDateToCB(DirectX::XMMATRIX& worldMatrix)
{
	CONSTANT_BUFFER cb;
	/*cb.matW = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());*/
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);

	
}

void Sprite::SetBuffrToPipeline()
{
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

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);


	
}

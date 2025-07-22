#include "Dice.h"
#include "Texture.h"
#include "Camera.h"
#include <DirectXMath.h>

using namespace DirectX;

Dice::Dice()
	: Quad()
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	VERTEX vertices[] =
	{
		//{{position}, {uv}}
		{{ -1.0f,  1.0f, -1.0f, 0.0f}, {0.0f,   0.0f}, {0.0f, 0.0f, -1.0f, 0.0f}},// 四角形の頂点（左上）
		{{  1.0f,  1.0f, -1.0f, 0.0f}, {0.25f,  0.0f}, {0.0f, 0.0f, -1.0f, 0.0f} },// 四角形の頂点（右上）
		{{  1.0f, -1.0f, -1.0f, 0.0f}, {0.25f,  0.5f}, {0.0f, 0.0f, -1.0f, 0.0f} },// 四角形の頂点（右下）
		{{ -1.0f, -1.0f, -1.0f, 0.0f}, {0.0f,   0.5f}, {0.0f, 0.0f, -1.0f, 0.0f}},	// 四角形の頂点（左下）	
		//{{position}, {uv}}
		{{ -1.0f,  1.0f, +1.0f, 0.0f}, {0.25f,  0.5f}, {0.0f, 0.0f, 1.0f, 0.0f}},// 四角形の頂点（左上）
		{{  1.0f,  1.0f, +1.0f, 0.0f}, {0.5f,  0.5f},  {0.0f, 0.0f, 1.0f, 0.0f}},// 四角形の頂点（右上）
		{{  1.0f, -1.0f, +1.0f, 0.0f}, {0.5f,  1.0f},  {0.0f, 0.0f, 1.0f, 0.0f}},// 四角形の頂点（右下）
		{{ -1.0f, -1.0f, +1.0f, 0.0f}, {0.25f,  1.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},// 四角形の頂点（左下）	

		// 右面
		{{1.0f, 1.0f, -1.0f, 0.0f}, { 0.0f,  1.0f }, {1.0f, 0.0f, 0.0f, 0.0f}},
		{{1.0f, 1.0f, +1.0f, 0.0f}, { 0.0f,  0.5f }, {1.0f, 0.0f, 0.0f, 0.0f}},
		{{1.0f, -1.0f, 1.0f, 0.0f},	{ 0.25f,  0.5f}, {1.0f, 0.0f, 0.0f, 0.0f}},
		{{1.0f, -1.0f,-1.0f, 0.0f}, { 0.25f,  1.0f}, {1.0f, 0.0f, 0.0f, 0.0f}},

		// 左面
		{{-1.0f, 1.0f, -1.0f, 0.0f}, { 0.5f,  0.0f }, {-1.0f, 0.0f, 0.0f, 0.0f}},
		{{-1.0f, 1.0f, +1.0f, 0.0f}, { 0.25f,  0.0f }, {-1.0f, 0.0f, 0.0f, 0.0f}},
		{{-1.0f, -1.0f, 1.0f, 0.0f}, { 0.25f,  0.5f}, {-1.0f, 0.0f, 0.0f, 0.0f}},
		{{-1.0f, -1.0f,-1.0f, 0.0f}, { 0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f, 0.0f}},

		// 上面
		{{-1.0f, 1.0f, 1.0f, 0.0f}, {0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
		{{ 1.0f, 1.0f, 1.0f, 0.0f}, {0.75f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
		{{ 1.0f, 1.0f,-1.0f, 0.0f}, {0.75f, 0.5f}, {0.0f, 1.0f, 0.0f, 0.0f}},
		{{-1.0f, 1.0f,-1.0f, 0.0f}, {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 0.0f}},

		// 底面
		{{-1.0f, -1.0f, 1.0f, 0.0f}, {0.75f, 0.0f}, {0.0f, -1.0f, 0.0f, 0.0f}},
		{{ 1.0f, -1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f, 0.0f}},
		{{ 1.0f, -1.0f,-1.0f, 0.0f}, {1.0f, 0.5f}, {0.0f, -1.0f, 0.0f, 0.0f}},
		{{-1.0f, -1.0f,-1.0f, 0.0f}, {0.75f, 0.5f}, {0.0f, -1.0f, 0.0f, 0.0f}},
	};

	int index[] = {
		 0, 1, 2, 0, 2, 3, // 前面
		 4, 6, 5, 4, 7, 6, // 後面
		 8, 9 ,10, 8,10,11, //右側
		12,14,13,12,15,14,//左側
		16,17,18,16,18,19,//上側
		20,22,21,20,23,22 //下側
	};


	HRESULT hr;
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
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

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
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
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
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture();
	pTexture_->Load("Assets\\dice.png");//画像を表示

	return S_OK;



}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixInverse(nullptr, worldMatrix);	//法線変換用の行列
	cb.matWorld = XMMatrixTranspose(worldMatrix);


	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

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

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);



	Direct3D::pContext->DrawIndexed(36, 0, 0);

}

void Dice::Release()
{
}
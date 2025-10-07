#include "Quad.h"
#include "Camera.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <cassert>
#include "Direct3D.h"
#include <windows.h>



Quad::Quad() : pVertexBuffer_(nullptr)
, pIndexBuffer_(nullptr)
, pConstantBuffer_(nullptr), pTexture_(nullptr), pRasterState_(nullptr)
{
	
}

Quad::~Quad()
{
}

HRESULT Quad::Initialize()
{
	// 頂点情報

	VERTEX vertices[] =
	{
		//{{position}, {uv}}
		 { XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) }, // 左上
		 { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) }, // 右上
		 { XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) }, // 右下
		 { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }  // 左下
	
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
	HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}
	//assert(SUCCEEDED(result));

	//インデックス情報
	int indices[] = 
	{
		// 前面 (+Z)
		0,2,3, 0,1,2
	
	};


	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(indices);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = indices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);


	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT result;
	result = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	assert(SUCCEEDED(result));
	// ラスタライザーステートの設定
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(rasterDesc));
	rasterDesc.FillMode = D3D11_FILL_SOLID; // 通常の描画（ワイヤーフレームはD3D11_FILL_WIREFRAME）
	rasterDesc.CullMode = D3D11_CULL_NONE;  // ここを D3D11_CULL_NONE に設定することでカリングを無効にする
	// もし背面カリングを再度有効にするなら D3D11_CULL_BACK
	// もし前面カリングを有効にするなら D3D11_CULL_FRONT
	rasterDesc.FrontCounterClockwise = TRUE; // 反時計回りの面を表と見なす（デフォルト）
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = TRUE;
	rasterDesc.ScissorEnable = FALSE;
	rasterDesc.MultisampleEnable = FALSE;
	rasterDesc.AntialiasedLineEnable = FALSE;

	ID3D11RasterizerState* pRasterState = nullptr;
	HRESULT hh = Direct3D::pDevice->CreateRasterizerState(&rasterDesc, &pRasterState);
	if (FAILED(hh))
	{
		// エラー処理
		MessageBox(nullptr, L"ラスタライザーステートの作成に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}

	 /*
	 作成したラスタライザーステートをデバイスコンテキストにセット
	 */
	Direct3D::pContext->RSSetState(pRasterState);

	pRasterState->Release();
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");//画像を表示
	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	
	
	
	CONSTANT_BUFFER cb;

	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	

	
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);


	
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

	

	Direct3D::pContext->DrawIndexed(6, 0, 0);
}

void Quad::Release()
{

	pTexture_->Release();
	SAFE_DELETE(pTexture_);


	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pRasterState_);
	
	/*pVertexBuffer_->Release();
	pIndexBuffer_->Release();
	pConstantBuffer_->Release();*/
}

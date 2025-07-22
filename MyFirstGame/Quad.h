#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"


using namespace DirectX;

//コンスタントバッファー

struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP;
	//DirectX::XMMATRIX matUV;
	DirectX::XMMATRIX matNormal;
	DirectX::XMMATRIX matWorld;

};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{

protected:

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;
	ID3D11RasterizerState* pRasterState_;

public:
	Quad();
	virtual ~Quad();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	void Release();
};
#include "Dice.h"
#include <string>
#include <DirectXMath.h>
#include "Camera.h"

using namespace DirectX;

//7/15�^��40:00����m�F�ˊ���

Dice::Dice()
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	if (FAILED(Quad::Initialize())) return E_FAIL;

	// ���_�f�[�^
	VERTEX vertices[] =
	{
		// �O��
		{{ -1.0f,  1.0f, -1.0f, 0.0f}, {0.0f,  0.0f}, { 0.0f,  0.0f, -1.0f, 0.0f }},
		{{  1.0f,  1.0f, -1.0f, 0.0f}, {0.25f, 0.0f}, { 0.0f,  0.0f, -1.0f, 0.0f }},
		{{  1.0f, -1.0f, -1.0f, 0.0f}, {0.25f, 0.5f}, { 0.0f,  0.0f, -1.0f, 0.0f }},
		{{ -1.0f, -1.0f, -1.0f, 0.0f}, {0.0f, 0.5f}, { 0.0f,  0.0f, 0.0f, -1.0f }},

		// �w��
		{{ -1.0f,  1.0f,  1.0f, 0.0f}, {0.25f, 0.5f}},
		{{  1.0f,  1.0f,  1.0f, 0.0f}, {0.5f, 0.5f}},
		{{  1.0f, -1.0f,  1.0f, 0.0f}, {0.5f, 1.0f}},
		{{ -1.0f, -1.0f,  1.0f, 0.0f}, {0.25f, 1.0f}},

		// �E��
		{{ 1.0f,  1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
		{{ 1.0f,  1.0f,  1.0f, 0.0f}, {0.0f, 0.5f}},
		{{ 1.0f, -1.0f,  1.0f, 0.0f}, {0.25f, 0.5f}},
		{{ 1.0f, -1.0f, -1.0f, 0.0f}, {0.25f, 1.0f}},

		// ����
		{{ -1.0f,  1.0f, -1.0f, 0.0f}, {0.5f, 0.0f}},
		{{ -1.0f,  1.0f,  1.0f, 0.0f}, {0.25f, 0.5f}},
		{{ -1.0f, -1.0f,  1.0f, 0.0f}, {0.25f, 0.5f}},
		{{ -1.0f, -1.0f, -1.0f, 0.0f}, {0.5f, 0.5f}},

		// ���
		{{ -1.0f, 1.0f,  1.0f, 0.0f}, {0.5f, 0.0f}},
		{{  1.0f, 1.0f,  1.0f, 0.0f}, {0.75f, 0.0f}},
		{{  1.0f, 1.0f, -1.0f, 0.0f}, {0.75f, 0.5f}},
		{{ -1.0f, 1.0f, -1.0f, 0.0f}, {0.5f, 0.5f}},

		// ���
		{{ -1.0f, -1.0f,  1.0f, 0.0f}, {0.75f, 0.0f}},
		{{  1.0f, -1.0f,  1.0f, 0.0f}, {0.0f, 0.0f}},
		{{  1.0f, -1.0f, -1.0f, 0.0f}, {1.0f, 0.5f}},
		{{ -1.0f, -1.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
	};

	int index[] = 
	{
		 0, 1, 2,  0, 2, 3,    // �O��
		 4, 6, 5,  4, 7, 6,    // �w��
		 8, 9,10,  8,10,11,    // �E��
		12,14,13, 12,15,14,    // ����
		16,17,18, 16,18,19,    // ���
		20,22,21, 20,23,22     // ���
	};

	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices;

	HRESULT vhr = Direct3D::pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &pVertexBuffer_);
	if (FAILED(vhr)) return E_FAIL;

	// �C���f�b�N�X�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData = {};
	InitData.pSysMem = index;
	if (FAILED(Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_))) return E_FAIL;

	// �R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb = {};
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_))) return E_FAIL;

	// ���X�^���C�U�[�X�e�[�g
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = TRUE;
	rasterDesc.DepthClipEnable = TRUE;

	ID3D11RasterizerState* pRasterState = nullptr;
	if (FAILED(Direct3D::pDevice->CreateRasterizerState(&rasterDesc, &pRasterState))) return E_FAIL;

	Direct3D::pContext->RSSetState(pRasterState);
	pRasterState->Release();

	// �e�N�X�`���ǂݍ��݁i6�ʂɓ����摜�j
	pTexture_ = new Texture;
	pTexture_->Load(L"Assets\\dice.png");//�摜��\��

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	//QuadData data[] = {
	//	QuadData({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),
	//	QuadData({ 1.0f, 1.0f, 1.0f }, { 45.0f, 45.0f, 45.0f }, { 1.0f, 1.0f }),
	//	QuadData({ -1.0f, -1.0f, -1.0f }, { -45.0f, -45.0f, -45.0f }, { 1.0f, 1.0f })
	//};
	//for (const auto& d : data)
	//{
	//	XMMATRIX mat = XMMatrixTranslation(d.position.x, d.position.y, d.position.z) *
	//		XMMatrixRotationRollPitchYaw(XMConvertToRadians(d.rotate.x), XMConvertToRadians(d.rotate.y), XMConvertToRadians(d.rotate.z)) *
	//		worldMatrix;
	//	Quad::Draw(mat);
	//}

	CONSTANT_BUFFER cb;
	
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal= XMMatrixInverse(nullptr, worldMatrix);
	cb.matWVP = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);//GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));//�f�[�^�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();

	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);



	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();

	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);



	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ


	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p



	Direct3D::pContext->DrawIndexed(36, 0, 0);

}

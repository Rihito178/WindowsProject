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
	// ���_���

	VERTEX vertices[] =
	{
		//{{position}, {uv}}
		 { XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) }, // ����
		 { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) }, // �E��
		 { XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) }, // �E��
		 { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) }  // ����
	
	};


	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
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
		MessageBox(nullptr, L"���_�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}
	//assert(SUCCEEDED(result));

	//�C���f�b�N�X���
	int indices[] = 
	{
		// �O�� (+Z)
		0,2,3, 0,1,2
	
	};


	// �C���f�b�N�X�o�b�t�@�𐶐�����
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


	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT result;
	result = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	assert(SUCCEEDED(result));
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(rasterDesc));
	rasterDesc.FillMode = D3D11_FILL_SOLID; // �ʏ�̕`��i���C���[�t���[����D3D11_FILL_WIREFRAME�j
	rasterDesc.CullMode = D3D11_CULL_NONE;  // ������ D3D11_CULL_NONE �ɐݒ肷�邱�ƂŃJ�����O�𖳌��ɂ���
	// �����w�ʃJ�����O���ēx�L���ɂ���Ȃ� D3D11_CULL_BACK
	// �����O�ʃJ�����O��L���ɂ���Ȃ� D3D11_CULL_FRONT
	rasterDesc.FrontCounterClockwise = TRUE; // �����v���̖ʂ�\�ƌ��Ȃ��i�f�t�H���g�j
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
		// �G���[����
		MessageBox(nullptr, L"���X�^���C�U�[�X�e�[�g�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}

	 /*
	 �쐬�������X�^���C�U�[�X�e�[�g���f�o�C�X�R���e�L�X�g�ɃZ�b�g
	 */
	Direct3D::pContext->RSSetState(pRasterState);

	pRasterState->Release();
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");//�摜��\��
	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	
	
	
	CONSTANT_BUFFER cb;

	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	

	
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

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

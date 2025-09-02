#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>
#include "Texture.h"



#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Fbx
{
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(FbxNode* pNode);

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	int materialCount_;	//�}�e���A���̌�
	MATERIAL* materialList_;
	XMVECTOR uv;


};
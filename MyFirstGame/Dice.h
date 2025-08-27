#pragma once
#include "Quad.h"
class Dice :public Quad
{
private:
	struct QuadData
	{
		QuadData(
			const DirectX::XMFLOAT3& _position,
			const DirectX::XMFLOAT3& _rotate,
			const DirectX::XMFLOAT2& _uv) :
			position{ _position },
			rotate{ _rotate },
			uv{ _uv }
		{
		}
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT2 uv;
	};
public:
	Dice();
	~Dice();
	HRESULT Initialize()override;
	void Draw(XMMATRIX& worldMatrix) override;
};
	


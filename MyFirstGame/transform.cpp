#include "transform.h"

Transform::Transform()
{
    XMFLOAT3 a;

    a.x = 10.0f;

    a.y = 20.0f;

    a.z = 30.0f;


}

Transform::~Transform()
{

}

void Transform::Calculation()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	//��]�s��
	matRotate_ = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(rotate_.x),
		XMConvertToRadians(rotate_.y),
		XMConvertToRadians(rotate_.z));
	//�g��s��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}



XMMATRIX Transform::GetWorldMatrix()
{
	return matScale_ * matRotate_ * matTranslate_;

}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);

}

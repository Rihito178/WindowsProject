#include "Camera.h"

//�ϐ�
XMVECTOR position_;	//�J�����̈ʒu�i���_�j
XMVECTOR target_;	//����ʒu�i�œ_�j
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(10, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	//�v���W�F�N�V�����s��
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)450 / (FLOAT)360, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	static float angle = 0.0f;
	angle += 0.0005f; // ���t���[����������]�i���x�͒����j
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

	// ��]�s��iY����]�j
	XMMATRIX rotY = XMMatrixRotationY(angle);

	// �����ʒu�x�N�g���i���ΓI�ȃJ�����̈ʒu�j
	XMVECTOR basePosition = XMVectorSet(10, 3, -10, 0);

	// ��]��K�p�����J�����ʒu
	position_ = XMVector3Transform(basePosition, rotY);

	// �r���[�s��̍X�V
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return  viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}

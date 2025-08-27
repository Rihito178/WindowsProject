#include "Camera.h"

//変数
XMVECTOR position_;	//カメラの位置（視点）
XMVECTOR target_;	//見る位置（焦点）
XMMATRIX viewMatrix_;	//ビュー行列
XMMATRIX projMatrix_;	//プロジェクション行列

//初期化
void Camera::Initialize()
{
	position_ = XMVectorSet(10, 3, -10, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 0, 0);	//カメラの焦点
	//プロジェクション行列
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)450 / (FLOAT)360, 0.1f, 100.0f);
}

//更新
void Camera::Update()
{
	static float angle = 0.0f;
	angle += 0.0005f; // 毎フレーム少しずつ回転（速度は調整可）
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

	// 回転行列（Y軸回転）
	XMMATRIX rotY = XMMatrixRotationY(angle);

	// 初期位置ベクトル（相対的なカメラの位置）
	XMVECTOR basePosition = XMVectorSet(10, 3, -10, 0);

	// 回転を適用したカメラ位置
	position_ = XMVector3Transform(basePosition, rotY);

	// ビュー行列の更新
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return  viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}

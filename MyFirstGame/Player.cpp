#include "Player.h"
#include "Engine/Fbx.h"//•¡”Žg—p‚·‚éê‡



Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), fbx(nullptr)
{

}

Player::~Player()
{


}

void Player::Initialize()
{
	fbx = new Fbx();

	fbx->Load("Assets/FBX/Oden.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;



}

void Player::Update()
{
	transform_.rotate_.y += 0.1f;


}

void Player::Draw()
{
	if (fbx)
	{
		fbx->Draw(transform_);

	}


}

void Player::Release()
{


}

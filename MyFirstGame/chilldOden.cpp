#include "chilldOden.h"
#include "Engine/fbx.h"


chilldOden::chilldOden(GameObject* parent)
{
	pfbx = new Fbx;

	pfbx->Load("Oden.fbx");
	transform_.scale_.x = 0.3f;
	transform_.scale_.y = 0.3f;
	transform_.scale_.z = 0.3f;
	transform_.position_.y = -1.0f;

}

chilldOden::~chilldOden()
{
}

void chilldOden::Initialize()
{
}

void chilldOden::Update()
{
}

void chilldOden::Draw()
{
}

void chilldOden::Release()
{
}

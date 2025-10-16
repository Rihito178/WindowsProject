#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent), objectName_(name)
{
	if(parent !=nullptr)
	{
		pParent_->childList.push_back(this);

	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	this->Draw();
	for (auto child : childList)
	{
		//child->Draw();
		child->DrawSub();
	}
}

void GameObject::UpdateSub()
{
	this->Update();
	for (auto child : childList)
	{
		child->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	this->Release();//Ž©•ª‚ð‰ð•ú
	for (auto child : childList)
	{
		child->ReleaseSub();
	}
}


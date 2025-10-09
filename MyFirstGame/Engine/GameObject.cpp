#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	this->Draw();
	for (auto child : childList_)
	{
		//child->Draw();
		child->DrawSub();
	}
}
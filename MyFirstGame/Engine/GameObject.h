#pragma once

#include
#include 
#include 

class GameObject
{
	 childList_;
		transform_;
		pParent_;
		objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	 void Initialize() ;
	 void Update() ;
	 void Draw() ;
	 void Release() ;
};



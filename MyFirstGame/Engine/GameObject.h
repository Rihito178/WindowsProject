#pragma once

#include <list>
#include <string>
#include "transform.h"

//êeéqä÷åW
//êßå‰Ç™äyÇ…Ç»ÇÈ
using std::string;
using std::list;

class GameObject
{
	list<GameObject *>childList_;
	Transform transform_;
	GameObject*	pParent_;
	string objectName_;

public:

	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	 virtual void Initialize() =0;
	 virtual void Update() =0;
	 virtual void Draw() =0;
	 virtual void Release()=0 ;
};



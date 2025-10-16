#pragma once

#include <list>
#include <string>
#include "transform.h"

//�e�q�֌W
//���䂪�y�ɂȂ�
using std::string;
using std::list;

class GameObject
{



public:

	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	 virtual void Initialize() =0;
	 virtual void Update() =0;
	 virtual void Draw() =0;
	 virtual void Release()=0;

	 void DrawSub();//�q�N���X�̕`��
	 void UpdateSub();//�q�N���X�̍X�V
	 void ReleaseSub();//�q�N���X�̉��

	 template<typename T>
	 
	 void Instantiate(GameObject* parent)
	 {
		 T* obj = new T(parent);
		 obj->Initialize();
		 childList.push_back(obj);

	 }

protected:
	list<GameObject*>childList;
	Transform transform_;
	GameObject* pParent_;
	string objectName_;
};



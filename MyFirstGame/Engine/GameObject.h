#pragma once

#include <list>
#include <string>
#include "transform.h"

//親子関係
//制御が楽になる
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

	 void DrawSub();//子クラスの描画
	 void UpdateSub();//子クラスの更新
	 void ReleaseSub();//子クラスの解放

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



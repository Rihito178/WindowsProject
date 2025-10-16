#pragma once
#include "Engine/GameObject.h"

class Fbx;

class chilldOden :
    public GameObject
{
public:
	chilldOden(GameObject* parent);
	~chilldOden();
	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Release() override;

private:
	Fbx* pfbx;

};


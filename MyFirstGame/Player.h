#pragma once
#include "Engine\\GameObject.h"


class Fbx;//�|�C���^�݂̂̎��͑O���錾

class Player :
    public GameObject
{
public:
	Fbx* fbx;
	Player(GameObject* parent);
	~Player();
	//�������z�֐�
	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Release() override;
};


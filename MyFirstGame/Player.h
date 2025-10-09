#pragma once
#include "Engine\\GameObject.h"


class Fbx;//ポインタのみの時は前方宣言

class Player :
    public GameObject
{
public:
	Fbx* fbx;
	Player(GameObject* parent);
	~Player();
	//純粋仮想関数
	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Release() override;
};


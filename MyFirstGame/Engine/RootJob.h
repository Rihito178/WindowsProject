#pragma once
#include "GameObject.h"
#include "..\\PlayScene.h"

class RootJob
	:GameObject
{
	
public:

	RootJob(RootJob* parent);
	~RootJob();


	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Release() override;
};
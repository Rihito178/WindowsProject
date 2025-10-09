#include "RootJob.h"
#include "..\\PlayScene.h"

RootJob::RootJob(RootJob* parent)
	:GameObject(parent, "RootJob")
{

}

RootJob::~RootJob()
{

}

void RootJob::Initialize()
{

	PlayScene* playScene;//�|�C���^�ϐ��̐錾
	playScene = new PlayScene(this);//�q���̐���
	playScene->Initialize();//������
	childList_.push_back(playScene);//�q���ɒǉ�



}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}

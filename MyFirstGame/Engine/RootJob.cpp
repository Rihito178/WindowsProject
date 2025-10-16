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

	Instantiate<PlayScene>(this);//�e���v���[�g�֐��Ő���


	PlayScene* playScene;//�|�C���^�ϐ��̐錾
	playScene = new PlayScene(this);//�q���̐���
	playScene->Initialize();//������
	childList.push_back(playScene);//�q���ɒǉ�
	


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

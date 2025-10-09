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

	PlayScene* playScene;//ポインタ変数の宣言
	playScene = new PlayScene(this);//子供の生成
	playScene->Initialize();//初期化
	childList_.push_back(playScene);//子供に追加



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

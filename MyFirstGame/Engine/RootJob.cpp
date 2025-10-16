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

	Instantiate<PlayScene>(this);//テンプレート関数で生成


	PlayScene* playScene;//ポインタ変数の宣言
	playScene = new PlayScene(this);//子供の生成
	playScene->Initialize();//初期化
	childList.push_back(playScene);//子供に追加
	


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

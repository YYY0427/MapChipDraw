#include "SceneManager.h"
#include <cassert>
#include "SceneTest.h"
#include "Pad.h"

SceneManager::SceneManager()
{
	pScene_ = nullptr;
}
SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	pScene_ = new SceneTest;
	pScene_->Init();
}

void SceneManager::End()
{
	assert(pScene_);
	if (!pScene_)	return;

	pScene_->End();
	delete pScene_;
}

void SceneManager::Update()
{
	assert(pScene_);
	if (!pScene_)	return;

	Pad::update();
	SceneBase* pScene = pScene_->Update();
	if (pScene != pScene_)
	{
		// 前のシーンの終了処理
		pScene_->End();
		delete pScene_;

		pScene_ = pScene;
		pScene_->Init();
	}
}

void SceneManager::Draw()
{
	assert(pScene_);
	if (!pScene_)	return;

	pScene_->Draw();
}
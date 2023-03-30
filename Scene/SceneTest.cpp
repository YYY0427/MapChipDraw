#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"

namespace
{
}

void SceneTest::Init()
{
	map_.Load();
}

void SceneTest::End()
{
	map_.Unoload();
}

SceneBase* SceneTest::Update()
{
	map_.Update();
	return this;
}

void SceneTest::Draw()
{
	map_.Draw();

	DrawString(0, 0, "test", GetColor(255, 255, 255));
}


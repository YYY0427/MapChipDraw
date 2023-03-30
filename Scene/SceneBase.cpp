#include "SceneBase.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// フェード速度
	constexpr int fade_speed = 8;
}

SceneBase::SceneBase()
{
	// 初期設定はフェードアウト状態
	fadeColor_ = GetColor(0, 0, 0);
	fadeBright_ = 255;
	fadeSpeed_ = -fade_speed;
}

void SceneBase::UpdateFade()
{
	fadeBright_ += fadeSpeed_;
	if (fadeBright_ >= 255)
	{
		fadeBright_ = 255;
		if (fadeSpeed_ > 0)
		{
			fadeSpeed_ = 0;
		}
	}
	if (fadeBright_ <= 0)
	{
		fadeBright_ = 0;
		if (fadeSpeed_ < 0)
		{
			fadeSpeed_ = 0;
		}
	}
}

void SceneBase::DrawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeBright_);
	DrawBox(0, 0, Game::screen_width, Game::screen_height, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::IsFadingIn() const
{
	if (fadeSpeed_ < 0)	return true;
	return false;
}

bool SceneBase::IsFadingOut() const
{
	if (fadeSpeed_ > 0)	return true;
	return false;
}

void SceneBase::StartFadeOut()
{
	fadeSpeed_ = fade_speed;
}
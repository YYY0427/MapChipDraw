#pragma once

#include "SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	SceneBase* pScene_;
};
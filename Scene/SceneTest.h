#pragma once
#include "SceneBase.h"

#include "Map.h"

class SceneTest : public SceneBase
{
public:
	SceneTest() 
	{
	}
	virtual ~SceneTest() {}


	virtual void Init() override;
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;

private:
	Map map_;
};
#pragma once

#include <CotEngine.h>
#include "MapEditor.h" //To use all of function and value

using namespace Cot;

Component(BlockSelfComponent)
{
	COT_COMPONENT(BlockSelfComponent);
private:
	MapEditor* lpMapEditor;
	SpriteRenderer* _renderer;
	Vec3 tempVec3; //Save position
	RECT selfArea; //Area of blockself

public:
	BlockSelfComponent* Init(MapEditor* lpScene);
	void Update(Time& time) override;
};
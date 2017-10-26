#pragma once

#include <CotEngine.h>
#include "HeadValue.h"

using namespace Cot;

class MapEditor;
Component(TileGrass2Component)
{
	COT_COMPONENT(TileGrass2Component);
private:
	MapEditor* lpMapEditor;

	int myPos; //Save position
	RECT rtTileArea; //Area of entity
	bool isCarry; //Check item click and drag

public:
	TileGrass2Component* Init(MapEditor* lpScene);

	void Update(Time& time) override;
};
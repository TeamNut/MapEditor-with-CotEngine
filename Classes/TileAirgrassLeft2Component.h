#pragma once

#include <CotEngine.h>
#include "MapEditor.h" //To use all of function and value
#include "HeadValue.h"

using namespace Cot;

class MapEditor;
Component(TileAirgrassLeft2Component)
{
	COT_COMPONENT(TileAirgrassLeft2Component);
private:
	MapEditor* lpMapEditor;

	int myPos; //Save position
	RECT rtTileArea; //Area of entity
	bool isCarry; //Check item click and drag

public:
	TileAirgrassLeft2Component* Init(MapEditor* lpScene);

	void Update(Time& time) override;
};
#pragma once

#include <CotEngine.h>
#include <fstream>
#include "HeadValue.h"
#include "tinyxml2\tinyxml2.h"

using namespace Cot;

class MapEditor;
Component(SaveComponent)
{
	COT_COMPONENT(SaveComponent);
private:
	MapEditor* lpMapEditor;

	void Save();
	void Load();

public:
	SaveComponent* Init(MapEditor* lpScene);

	void Update(Time& time) override;
};
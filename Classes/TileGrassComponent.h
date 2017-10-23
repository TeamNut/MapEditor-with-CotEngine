#pragma once

#include <CotEngine.h>
#include "MapEditor.h" //To use all of function and value
#include "HeadValue.h"

using namespace Cot;

Component(TileGrassComponent)
{
	COT_COMPONENT(TileGrassComponent);
private:
	std::string _str;
	float _count;

	int myPos; //Save position
	RECT rtTileArea; //Area of entity
	bool isCarry; //Check item click and drag

public:
	TileGrassComponent* Init(const string& str);

	void OnEnable() override;
	void Reset() override;
	void Awake() override;
	void Start() override;
	void Update(Time& time) override;
	void OnDisable() override;
	void OnDestroy() override;
};
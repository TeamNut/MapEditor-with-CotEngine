#pragma once

#include <CotEngine.h>
#include "HeadValue.h"
#include "ItemViewComponent.h"
#include "TileGrassComponent.h"
#include "TileGrass2Component.h"
#include "TileGrass3Component.h"
#include "TileAirgrassComponent.h"
#include "TileAirgrass2Component.h"
#include "TileAirgrass3Component.h"
#include "TileAirgrassLeftComponent.h"
#include "TileAirgrassLeft2Component.h"
#include "TileAirgrassLeft3Component.h"
#include "TileAirgrassRightComponent.h"
#include "TileAirgrassRight2Component.h"
#include "TileAirgrassRight3Component.h"
#include "BlockSelfComponent.h"
#include "SaveComponent.h"
//include component

class MapEditor
	: public Cot::Scene
{
private:
	SpriteRenderer* TileRenderer = nullptr;

	Cot::Entity* TileForShow;
	Cot::Entity* obItemView;
	Cot::Entity* gridLine[40] = { 0, };
	Cot::Entity* TempEntity; //Use only for Entity address save
	Cot::Entity* tempSolution;
	Cot::Entity* obTileGrass1;
	Cot::Entity* obTileGrass2;
	Cot::Entity* obTileGrass3;
	Cot::Entity* obTileAirgrass1;
	Cot::Entity* obTileAirgrass2;
	Cot::Entity* obTileAirgrass3;

	const char* lastTile; //Save last used tile's name
	//About grid
	int revisedX;
	int revisedY;
	int gapX;
	int gapY;
	//About root position
	int nowX;
	int nowY;
	//
	int tempSolutionPos;
	bool tempSolutionState;
	bool fastPlace;

public:
	Cot::Entity* root;
	Cot::Entity* TileSpace[MAX_OBJECT];
	Cot::Entity* ReadyTile(Cot::Entity*, const char*);
	void Update(Cot::Time& time) override;
	void GridPlacing();
	void PlaceTile(const char*);
	void DeleteTile(Cot::Entity*);
	void ShowTile(const char*);
	void HideTile(const char*);
	bool IsAreaClick(RECT &rt, MouseButton);
	bool IsAreaStay(RECT &rt, MouseButton);
	bool IsOverlap();
	bool Init() override;
};

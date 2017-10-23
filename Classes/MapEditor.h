#pragma once

#include <CotEngine.h>
#include "HeadValue.h"
#include "ItemViewComponent.h"
#include "TileGrassComponent.h"
#include "TileGrass2Component.h"
#include "TileGrass3Component.h"
#include "BlockSelfComponent.h"
#include "SaveComponent.h"
//include component

class MapEditor
	: public Cot::Scene
{
private:
	static Cot::Entity* Tile_for_Show;
	Cot::Entity* ob_ItemView;
	Cot::Entity* root;
	Cot::Entity* gridLine[40] = { 0, };
	Cot::Entity* TempEntity; //Use only for Entity address save
	Cot::Entity* tempSolution;
	Cot::Entity* ob_Tile_Grass1;
	Cot::Entity* ob_Tile_Grass2;
	Cot::Entity* ob_Tile_Grass3;

			
	static const char* lastTile; //Save last used tile's name
	//About grid
	static int revisedX;
	static int revisedY;
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
	static Cot::Entity* Tile_Space[MAX_OBJECT];
	static bool IsAreaClick(RECT &rt);
	static void PlaceTile(const char*);
	static void DeleteTile(Cot::Entity*);
	static void ShowTile(const char*);
	static void HideTile(const char*);
	static bool IsOverlap();
	bool Init() override;
	void Update(Cot::Time& time) override;
	void GridPlacing();
};

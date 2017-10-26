#include "TileGrass2Component.h"
#include "MapEditor.h"
//Initialize to use exterior something

#define THIS_TILE "tile_grass_02.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileGrass2Component* TileGrass2Component::Init(MapEditor* lpScene)
{
	puts("Enable grass2");

	lpMapEditor = lpScene;

	CreateKeyListener();
	CreateMouseListener();

	return this;
}

void TileGrass2Component::Update(Time& time)
{
	//Position Control
	if (GetKeyListener()->IsKeyStay(KeyCode::Comma) && myPos > 50) myPos--;
	if (myPos <= 50) myPos = 50;
	if (GetKeyListener()->IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos + GAP_OF_BLOCK, RESOLUTION_Y - 85));

	//Setting tile area
	Vec3 tempVec3 = GetOwner()->GetLocalPosition();
	rtTileArea = { (int)tempVec3.x - RADIUS_BLOCK, (int)tempVec3.y - RADIUS_BLOCK, (int)tempVec3.x + RADIUS_BLOCK, (int)tempVec3.y + RADIUS_BLOCK };

	//Item drag and drop
	if (lpMapEditor->IsAreaClick(rtTileArea, MouseButton::LButton, GetMouseListener()))
	{
		isCarry = true;
	}
	if (isCarry == true)
	{
		lpMapEditor->ShowTile(THIS_TILE);

		if (GetMouseListener()->IsMouseUp(MouseButton::LButton))
		{
			lpMapEditor->HideTile(THIS_TILE);
			lpMapEditor->PlaceTile(THIS_TILE);
			isCarry = false;
		}
	}
}

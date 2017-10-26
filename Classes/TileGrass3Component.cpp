#include "TileGrass3Component.h"
#include "MapEditor.h"

#define THIS_TILE "tile_grass_03.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileGrass3Component* TileGrass3Component::Init(MapEditor* lpScene)
{
	puts("Enable grass3");
	
	lpMapEditor = lpScene;

	CreateKeyListener();
	CreateMouseListener();

	return this;
}

void TileGrass3Component::Update(Time& time)
{
	//Position Control
	if (GetKeyListener()->IsKeyStay(KeyCode::Comma) && myPos > 50) myPos--;
	if (myPos <= 50) myPos = 50;
	if (GetKeyListener()->IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos + GAP_OF_BLOCK * 2, RESOLUTION_Y - 85));

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

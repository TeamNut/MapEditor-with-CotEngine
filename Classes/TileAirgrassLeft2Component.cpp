#include "TileAirgrassLeft2Component.h"
#include "MapEditor.h"
#define THIS_TILE "tile_airgrass_left_02.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileAirgrassLeft2Component* TileAirgrassLeft2Component::Init(MapEditor* lpScene)
{
	lpMapEditor = lpScene;
	myPos = 50;

	return this;
}

void TileAirgrassLeft2Component::Update(Time& time)
{
	//Position Control
	if (IsKeyStay(KeyCode::Comma)) myPos--;
	if (IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos + GAP_OF_BLOCK * 7, RESOLUTION_Y - 85));

	//Setting tile area
	Vec3 tempVec3 = GetOwner()->GetLocalPosition();
	rtTileArea = { (int)tempVec3.x - RADIUS_BLOCK, (int)tempVec3.y - RADIUS_BLOCK, (int)tempVec3.x + RADIUS_BLOCK, (int)tempVec3.y + RADIUS_BLOCK };

	//Item drag and drop
	if (lpMapEditor->IsAreaClick(rtTileArea, MouseButton::LButton))
	{
		isCarry = true;
	}
	if (isCarry == true)
	{
		lpMapEditor->ShowTile(THIS_TILE);

		if (IsMouseUp(MouseButton::LButton))
		{
			lpMapEditor->HideTile(THIS_TILE);
			lpMapEditor->PlaceTile(THIS_TILE);
			isCarry = false;
		}
	}
}
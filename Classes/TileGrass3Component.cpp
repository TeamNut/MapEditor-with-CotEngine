#include "TileGrass3Component.h"
//Initialize to use exterior something

#define THIS_TILE "tile_grass_03.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileGrass3Component* TileGrass3Component::Init(const string& str)
{
	_str = str;

	puts("Enable grass3");

	return this;
}

void TileGrass3Component::OnEnable()
{

}

void TileGrass3Component::Reset()
{

}

void TileGrass3Component::Awake()
{

}

void TileGrass3Component::Start()
{

}

void TileGrass3Component::Update(Time& time)
{
	//Position Control
	if (IsKeyStay(KeyCode::Comma) && myPos > 50) myPos--;
	if (myPos <= 50) myPos = 50;
	if (IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos + GAP_OF_BLOCK * 2, RESOLUTION_Y - 85));

	//Setting tile area
	Vec3 tempVec3 = GetOwner()->GetLocalPosition();
	rtTileArea = { (int)tempVec3.x - RADIUS_BLOCK, (int)tempVec3.y - RADIUS_BLOCK, (int)tempVec3.x + RADIUS_BLOCK, (int)tempVec3.y + RADIUS_BLOCK };

	//Item drag and drop
	if (MapEditor::IsAreaClick(rtTileArea) == true)
	{
		isCarry = true;
	}
	if (isCarry == true)
	{
		MapEditor::ShowTile(THIS_TILE);

		if (IsMouseUp(MouseButton::LButton))
		{
			MapEditor::HideTile(THIS_TILE);
			MapEditor::PlaceTile(THIS_TILE);
			isCarry = false;
		}
	}
}

void TileGrass3Component::OnDisable()
{
	//printf("OnDiable\n");
}

void TileGrass3Component::OnDestroy()
{
	//printf("OnDestroy\n");
}

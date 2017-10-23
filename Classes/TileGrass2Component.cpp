#include "TileGrass2Component.h"
//Initialize to use exterior something

#define THIS_TILE "tile_grass_02.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileGrass2Component* TileGrass2Component::Init(const string& str)
{
	_str = str;

	puts("Enable grass2");

	return this;
}

void TileGrass2Component::OnEnable()
{

}

void TileGrass2Component::Reset()
{

}

void TileGrass2Component::Awake()
{

}

void TileGrass2Component::Start()
{

}

void TileGrass2Component::Update(Time& time)
{
	//Position Control
	if (IsKeyStay(KeyCode::Comma) && myPos > 50) myPos--;
	if (myPos <= 50) myPos = 50;
	if (IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos + GAP_OF_BLOCK, RESOLUTION_Y - 85));

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

void TileGrass2Component::OnDisable()
{
	//printf("OnDiable\n");
}

void TileGrass2Component::OnDestroy()
{
	//printf("OnDestroy\n");
}

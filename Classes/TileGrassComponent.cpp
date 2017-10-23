#include "TileGrassComponent.h"
//Initialize to use exterior something

#define THIS_TILE "tile_grass_01.png"
#define RADIUS_BLOCK 25 //Area of half of block

TileGrassComponent* TileGrassComponent::Init(const string& str)
{
	_str = str;

	puts("Enable grass1");

	return this;
}

void TileGrassComponent::OnEnable()
{

}

void TileGrassComponent::Reset()
{

}

void TileGrassComponent::Awake()
{

}

void TileGrassComponent::Start()
{

}

void TileGrassComponent::Update(Time& time)
{
	//Position Control
	if (IsKeyStay(KeyCode::Comma) && myPos > 50) myPos--;
	if (myPos <= 50) myPos = 50;
	if (IsKeyStay(KeyCode::Period)) myPos++;
	GetOwner()->SetLocalPosition(Vec3(myPos, RESOLUTION_Y - 85));
	
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

void TileGrassComponent::OnDisable()
{
	//printf("OnDiable\n");
}

void TileGrassComponent::OnDestroy()
{
	//printf("OnDestroy\n");
}

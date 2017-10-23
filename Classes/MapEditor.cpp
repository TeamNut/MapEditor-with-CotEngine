#include "MapEditor.h"
//Initialize to use exterior something
Cot::Entity* MapEditor::Tile_Space[] = { 0, };
Cot::Entity* MapEditor::Tile_for_Show = 0;
int MapEditor::revisedX = 0;
int MapEditor::revisedY = 0;
const char* MapEditor::lastTile = "";

#pragma warning(disable : 4996)
#define TILE_GAP 50
#define TILE_GRASS_01 "tile_grass_01.png"
#define TILE_GRASS_02 "tile_grass_02.png"
#define TILE_GRASS_03 "tile_grass_03.png"

using namespace Cot;

bool MapEditor::Init()
{
	graphics->SetClearColor(Color(1.0f, 1.0f, 1.0f));
	//Value initialize
	gapX = DEFAULT_GAP_X;
	gapY = DEFAULT_GAP_Y;
	//Grid placing
	GridPlacing();
	
	//Root object for all of tile
	root = new Entity("root");
	root->SetPosition(Vec3(nowX, nowY));
	this->AddEntity(root);

	//Item view background
	ob_ItemView = new Entity("ItemViewBackground");
	//ob_ItemView->AddComponent<ItemViewComponent>();
	ob_ItemView->SetPosition(Vec3(RESOLUTION_X / 2, RESOLUTION_Y - 85));
	SpriteRenderer *RenderItemView = ob_ItemView->AddComponent<SpriteRenderer>()->Init("itemView.png");
	RenderItemView->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
	RenderItemView->SetDepth(0);
	this->AddEntity(ob_ItemView);

	//ItemView
	//Grass tile
	ob_Tile_Grass1 = new Entity("GRASS1");
	ob_Tile_Grass1->AddComponent<TileGrassComponent>()->Init("GRASS1");
	SpriteRenderer *RenderTileGrass = ob_Tile_Grass1->AddComponent<SpriteRenderer>()->Init(TILE_GRASS_01);
	RenderTileGrass->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	RenderTileGrass->SetDepth(5);
	ob_Tile_Grass1->SetLocalScale(Vec3(0.4f, 0.4f));
	this->AddEntity(ob_Tile_Grass1);
	//Grass tile 2
	ob_Tile_Grass2 = new Entity("GRASS2");
	ob_Tile_Grass2->AddComponent<TileGrass2Component>()->Init("GRASS2");
	SpriteRenderer *RenderTileGrass2 = ob_Tile_Grass2->AddComponent<SpriteRenderer>()->Init(TILE_GRASS_02);
	RenderTileGrass2->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	RenderTileGrass2->SetDepth(5);
	ob_Tile_Grass2->SetLocalScale(Vec3(0.4f, 0.4f));
	this->AddEntity(ob_Tile_Grass2);
	//Grass tile 3
	ob_Tile_Grass3 = new Entity("GRASS3");
	ob_Tile_Grass3->AddComponent<TileGrass3Component>()->Init("GRASS3");
	SpriteRenderer *RenderTileGrass3 = ob_Tile_Grass3->AddComponent<SpriteRenderer>()->Init(TILE_GRASS_03);
	RenderTileGrass3->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	RenderTileGrass3->SetDepth(5);
	ob_Tile_Grass3->SetLocalScale(Vec3(0.4f, 0.4f));
	this->AddEntity(ob_Tile_Grass3);

	//Pool of a demo tile
	Tile_for_Show = new Entity("TEMPORARY");
	Tile_for_Show->AddComponent<SpriteRenderer>()->Init("");
	Tile_for_Show->SetLocalPosition(Vec3(-200, -200));
	this->AddEntity(Tile_for_Show);

	//Pool of in-game tile
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		char cntStr[10] = { 0, };
		itoa(i, cntStr, 10);

		Tile_Space[i] = new Entity(cntStr);
		Tile_Space[i]->AddComponent<SpriteRenderer>()->Init("");
		Tile_Space[i]->AddComponent<BlockSelfComponent>()->Init();
		Tile_Space[i]->SetActive(false);
		Tile_Space[i]->SetParent(root);
		this->AddEntity(Tile_Space[i]);
	}

	//Temporary solve error about sprite rendering
	tempSolution = new Entity("ts");
	tempSolution->AddComponent<SpriteRenderer>()->Init("");
	tempSolution->AddComponent<SaveComponent>();
	tempSolution->SetParent(root);
	this->AddEntity(tempSolution);

	return true;
}

void MapEditor::Update(Cot::Time& time)
{
	Scene::Update(time);
	
	//Base working
	//Temporary solve error about sprite rendering
	if (tempSolutionPos > 100) tempSolutionState = true;
	if (tempSolutionPos < -100) tempSolutionState = false;
	switch (tempSolutionState)
	{
	case false:
		tempSolutionPos++;
		break;
	case true:
		tempSolutionPos--;
		break;
	}
	tempSolution->SetPosition(Vec3(tempSolutionPos, 0));
	//Revised mouse position by grid
	revisedX = (int)GetMousePosition().x % gapX < gapX / 2 ?
				(int)GetMousePosition().x - ((int)GetMousePosition().x % gapX) : gapX + (int)GetMousePosition().x - ((int)GetMousePosition().x % gapX);
	revisedY = (int)GetMousePosition().y % gapY < gapY / 2 ?
				(int)GetMousePosition().y - ((int)GetMousePosition().y % gapY) : gapY + (int)GetMousePosition().y - ((int)GetMousePosition().y % gapY);

	//Fast place
	if (IsKeyDown(KeyCode::E))
		if (strcmp(lastTile, "") == 0) puts("Cannot found last use");
		else fastPlace = true;
	if (IsKeyStay(KeyCode::E))
	{
		if (strcmp(lastTile, "") != 0) ShowTile(lastTile);
	}
	if (IsKeyUp(KeyCode::E) && fastPlace == true)
	{
		PlaceTile(lastTile);
		HideTile(lastTile);
		fastPlace = false;
	}

	//Root move
	if (IsKeyDown(KeyCode::A)) nowX -= DEFAULT_GAP_X;
	if (IsKeyDown(KeyCode::D))
	{
		nowX += DEFAULT_GAP_X;
	
	}
	if (IsKeyDown(KeyCode::W)) nowY -= DEFAULT_GAP_Y;
	if (IsKeyDown(KeyCode::S)) nowY += DEFAULT_GAP_Y;
	root->SetPosition(Vec3(nowX, nowY));
}

//Place tile
void MapEditor::PlaceTile(const char* tileName)
{
	int pointer;
	for (pointer = 0; pointer < MAX_OBJECT; pointer++)
	{
		if (Tile_Space[pointer]->IsActive() == false) //If isn't active,
		{
#if OVERLAP == false
			//If overlap with something other, stop placing tile
			if (IsOverlap() == true)
			{
				puts("Is piled");
				break;
			}
#endif
			Tile_Space[pointer]->GetComponent<SpriteRenderer>()->Init(tileName);
			Tile_Space[pointer]->SetPosition(Vec3(revisedX, revisedY));
			Tile_Space[pointer]->SetActive(true);
			lastTile = tileName;

			break;
		}
	}
	if (pointer == MAX_OBJECT) puts("Block is full");
}
//Delete tile
void MapEditor::DeleteTile(Cot::Entity* delTarget)
{
	delTarget->SetPosition(Vec3(-5000, -5000));
	delTarget->SetActive(false);
}

//Check : Is pile with placed blocks
bool MapEditor::IsOverlap()
{
	Vec3 targetPos = Vec3(revisedX, revisedY);
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if ((int)targetPos.x == (int)Tile_Space[i]->GetPosition().x &&
			(int)targetPos.y == (int)Tile_Space[i]->GetPosition().y)
		{
			return true;
		}
	}
	return false;
}

//Show tile
void MapEditor::ShowTile(const char* tileName)
{
	Tile_for_Show->SetActive(true);
	SpriteRenderer* RenderTemp = Tile_for_Show->GetComponent<SpriteRenderer>()->Init(tileName);
	RenderTemp->SetDepth(6);
	Tile_for_Show->SetLocalPosition(GetMousePosition());
}
//Hide tile
void MapEditor::HideTile(const char* tileName)
{
	Tile_for_Show->SetActive(false);
}

//Check area click
bool MapEditor::IsAreaClick(RECT &rt)
{
	if (IsMouseDown(MouseButton::LButton))
	{
		//printf("%d %d %d %d vs %d %d\n", rt.left, rt.top, rt.right, rt.bottom, (int)GetMousePosition().x, (int)GetMousePosition().y);
		if ((int)GetMousePosition().x >= rt.left &&
			(int)GetMousePosition().x <= rt.right &&
			(int)GetMousePosition().y <= rt.bottom &&
			(int)GetMousePosition().y >= rt.top)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

//Place grid
void MapEditor::GridPlacing()
{
	int i = 0;
	int tempGapX = 0;
	int tempGapY = 0;
	//horizontal
	while (true)
	{
		if (tempGapY >= RESOLUTION_Y) break; //If grids are full in the screen, break

		gridLine[i] = new Entity("GRIDLINE");
		SpriteRenderer *RenderGrid = gridLine[i]->AddComponent<SpriteRenderer>()->Init("gridLine.png");
		RenderGrid->SetDepth(-1);
		RenderGrid->SetColor(Color(0.0f, 0.0f, 0.0f, 0.5f));
		gridLine[i]->SetLocalScale(Vec3(1.0f, 0.5f));
		gridLine[i]->SetLocalPosition(Vec3(RESOLUTION_X / 2, tempGapY));
		this->AddEntity(gridLine[i]);

		i++;
		tempGapY += gapY;
	}
	//vertical
	while (true)
	{
		if (tempGapX >= RESOLUTION_X) break; //If grids are full in the screen, break

		gridLine[i] = new Entity("GRIDLINE");
		SpriteRenderer *RenderGrid = gridLine[i]->AddComponent<SpriteRenderer>()->Init("gridLineVertical.png");
		RenderGrid->SetDepth(-1);
		RenderGrid->SetColor(Color(0.0f, 0.0f, 0.0f, 0.5f));
		gridLine[i]->SetLocalScale(Vec3(0.5f, 1.0f));
		gridLine[i]->SetLocalPosition(Vec3(tempGapX, RESOLUTION_Y / 2));
		this->AddEntity(gridLine[i]);

		i++;
		tempGapX += gapX;
	}
}
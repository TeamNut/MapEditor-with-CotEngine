#include "MapEditor.h"

#pragma warning(disable : 4996)
#define TILE_GAP 50
#define TILE_GRASS_01 "tile_grass_01.png"
#define TILE_GRASS_02 "tile_grass_02.png"
#define TILE_GRASS_03 "tile_grass_03.png"
#define TILE_AIRGRASS_01 "tile_airgrass_01.png"
#define TILE_AIRGRASS_02 "tile_airgrass_02.png"
#define TILE_AIRGRASS_03 "tile_airgrass_03.png"
#define TILE_AIRGRASS_LEFT_01 "tile_airgrass_left_01.png"
#define TILE_AIRGRASS_LEFT_02 "tile_airgrass_left_02.png"
#define TILE_AIRGRASS_LEFT_03 "tile_airgrass_left_03.png"
#define TILE_AIRGRASS_RIGHT_01 "tile_airgrass_right_01.png"
#define TILE_AIRGRASS_RIGHT_02 "tile_airgrass_right_02.png"
#define TILE_AIRGRASS_RIGHT_03 "tile_airgrass_right_03.png"


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
	obItemView = new Entity("ItemViewBackground");
	//obItemView->AddComponent<ItemViewComponent>();
	obItemView->SetPosition(Vec3(RESOLUTION_X / 2, RESOLUTION_Y - 85));
	SpriteRenderer *RenderItemView = obItemView->AddComponent<SpriteRenderer>()->Init("itemView.png");
	RenderItemView->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
	RenderItemView->SetDepth(0);
	this->AddEntity(obItemView);

	//ItemView
	ReadyTile(obTileGrass1, TILE_GRASS_01)->AddComponent<TileGrassComponent>()->Init(this);
	ReadyTile(obTileGrass2, TILE_GRASS_02)->AddComponent<TileGrass2Component>()->Init(this);
	ReadyTile(obTileGrass3, TILE_GRASS_03)->AddComponent<TileGrass3Component>()->Init(this);
	ReadyTile(obTileAirgrass1, TILE_AIRGRASS_01)->AddComponent<TileAirgrassComponent>()->Init(this);
	ReadyTile(obTileAirgrass2, TILE_AIRGRASS_02)->AddComponent<TileAirgrass2Component>()->Init(this);
	ReadyTile(obTileAirgrass3, TILE_AIRGRASS_03)->AddComponent<TileAirgrass3Component>()->Init(this);
	ReadyTile(obTileAirgrass1, TILE_AIRGRASS_LEFT_01)->AddComponent<TileAirgrassLeftComponent>()->Init(this);
	ReadyTile(obTileAirgrass2, TILE_AIRGRASS_LEFT_02)->AddComponent<TileAirgrassLeft2Component>()->Init(this);
	ReadyTile(obTileAirgrass3, TILE_AIRGRASS_LEFT_03)->AddComponent<TileAirgrassLeft3Component>()->Init(this);
	ReadyTile(obTileAirgrass1, TILE_AIRGRASS_RIGHT_01)->AddComponent<TileAirgrassRightComponent>()->Init(this);
	ReadyTile(obTileAirgrass2, TILE_AIRGRASS_RIGHT_02)->AddComponent<TileAirgrassRight2Component>()->Init(this);
	ReadyTile(obTileAirgrass3, TILE_AIRGRASS_RIGHT_03)->AddComponent<TileAirgrassRight3Component>()->Init(this);

	//Pool of a demo tile
	TileForShow = new Entity("");
	TileForShow->AddComponent<SpriteRenderer>()->Init("");
	TileForShow->SetLocalPosition(Vec3(-200, -200));
	this->AddEntity(TileForShow);

	//Pool of in-game tile
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		char cntStr[10] = { 0, };
		itoa(i, cntStr, 10);

		TileSpace[i] = new Entity(cntStr);
		TileSpace[i]->AddComponent<SpriteRenderer>()->Init("");
		TileSpace[i]->AddComponent<BlockSelfComponent>()->Init(this);
		TileSpace[i]->SetActive(false);
		TileSpace[i]->SetParent(root);
		this->AddEntity(TileSpace[i]);
	}

	//Temporary solve error about sprite rendering
	tempSolution = new Entity("ts");
	tempSolution->AddComponent<SpriteRenderer>()->Init("");
	tempSolution->AddComponent<SaveComponent>()->Init(this);
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

//Ready tile
Cot::Entity* MapEditor::ReadyTile(Cot::Entity* obTile, const char* tileName)
{
	obTile = new Entity("");
	TileRenderer = obTile->AddComponent<SpriteRenderer>()->Init(tileName);
	TileRenderer->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	TileRenderer->SetDepth(5);
	obTile->SetLocalScale(Vec3(0.4f, 0.4f));
	this->AddEntity(obTile);
	return obTile;
}

//Place tile
void MapEditor::PlaceTile(const char* tileName)
{
	int pointer;
	for (pointer = 0; pointer < MAX_OBJECT; pointer++)
	{
		if (TileSpace[pointer]->IsActive() == false) //If isn't active,
		{
#if OVERLAP == false
			//If overlap with something other, stop placing tile
			if (IsOverlap() == true)
			{
				puts("Is piled");
				break;
			}
#endif
			TileSpace[pointer]->GetComponent<SpriteRenderer>()->Init(tileName);
			TileSpace[pointer]->SetPosition(Vec3(revisedX, revisedY));
			TileSpace[pointer]->SetActive(true);
			lastTile = tileName;

			printf("RevisedPos: (%d, %d)\n", revisedX, revisedY);

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
		if ((int)targetPos.x == (int)TileSpace[i]->GetPosition().x &&
			(int)targetPos.y == (int)TileSpace[i]->GetPosition().y)
		{
			return true;
		}
	}
	return false;
}

//Show tile
void MapEditor::ShowTile(const char* tileName)
{
	TileForShow->SetActive(true);
	SpriteRenderer* RenderTemp = TileForShow->GetComponent<SpriteRenderer>()->Init(tileName);
	RenderTemp->SetDepth(6);
	TileForShow->SetLocalPosition(GetMousePosition());
}
//Hide tile
void MapEditor::HideTile(const char* tileName)
{
	TileForShow->SetActive(false);
}

//Check area click
bool MapEditor::IsAreaClick(RECT &rt, MouseButton bt)
{
	if (IsMouseDown(bt))
	{
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
//Check area click
bool MapEditor::IsAreaStay(RECT &rt, MouseButton bt)
{
	if (IsMouseStay(bt))
	{
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
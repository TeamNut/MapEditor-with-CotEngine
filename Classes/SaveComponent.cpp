#define _CRT_SECURE_NO_WARNINGS
#include "SaveComponent.h"
//Initialize to use exterior something

SaveComponent* SaveComponent::Init(const string& str)
{
	_str = str;


	return this;
}

void SaveComponent::OnEnable()
{

}

void SaveComponent::Reset()
{

}

void SaveComponent::Awake()
{

}

void SaveComponent::Start()
{

}

void SaveComponent::Update(Time& time)
{
	if (IsKeyDown(KeyCode::F5)) Save();
	if (IsKeyDown(KeyCode::F7)) Load();
}

void SaveComponent::OnDisable()
{
	//printf("OnDiable\n");
}

void SaveComponent::OnDestroy()
{
	//printf("OnDestroy\n");
}

//Ability
void SaveComponent::Save()
{
	//Declaration XML
	tinyxml2::XMLDocument saveDest;
	tinyxml2::XMLDeclaration* lpDecl = saveDest.NewDeclaration();
	saveDest.LinkEndChild(lpDecl);
	
	//Add root node
	tinyxml2::XMLElement* root = saveDest.NewElement("Main");
	saveDest.LinkEndChild(root);

	//Send default map data
	tinyxml2::XMLElement* mapDefault = saveDest.NewElement("Default");
	root->LinkEndChild(mapDefault);
	mapDefault->SetAttribute("MaxObject", MAX_OBJECT);

	//Send blocks data
	tinyxml2::XMLElement* block[MAX_OBJECT] = { 0, }; //Declaration pool of object
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		char blockName[50] = "SavedBlock_";
		char tempNum[10] = { 0, }; //for itoa
		_itoa(i, tempNum, 10);
		strcat(blockName, tempNum);
		block[i] = saveDest.NewElement(blockName);
		root->LinkEndChild(block[i]);
		
		block[i]->SetAttribute("Sprite", MapEditor::Tile_Space[i]->GetComponent<SpriteRenderer>()->GetTexture()->GetFilename().c_str());
		block[i]->SetAttribute("IsActive", MapEditor::Tile_Space[i]->IsActive());
		block[i]->SetAttribute("GetX", MapEditor::Tile_Space[i]->GetPosition().x);
		block[i]->SetAttribute("GetY", MapEditor::Tile_Space[i]->GetPosition().y);
	}
	
	//Save at
	puts("[SAVE] Enter your save file name without extension");
	char path[MAX_PATH] = { 0, };
	scanf("%s", path);
	strcat(path, ".xml");
	saveDest.SaveFile(path);
}
void SaveComponent::Load()
{
	//Get path
	puts("[LOAD] Enter file name you wanna load without extension");
	char path[MAX_PATH] = { 0, };
	scanf("%s", path);
	strcat(path, ".xml");

	//Load XML
	tinyxml2::XMLDocument openData;
	openData.LoadFile(path);

	//Access root
	tinyxml2::XMLElement* lpRoot = openData.FirstChildElement("Main");
	if (!lpRoot) puts("[ERROR] Did not load");
	puts("access");

	//Access block
	tinyxml2::XMLElement* lpBlock = lpRoot->FirstChildElement("SavedBlock_0");
	if (!lpBlock) puts("[ERROR] No data");
	puts("access");

	//Get block object
	int i = 0;
	while (i < MAX_OBJECT)
	{
		//Get attribute one by one
		char* sprite = (char*)lpBlock->FirstAttribute()->Value();
		bool isActive = lpBlock->BoolAttribute("IsActive");
		int getX = lpBlock->IntAttribute("GetX");
		int getY = lpBlock->IntAttribute("GetY");
		//Place on the map
		MapEditor::Tile_Space[i]->GetComponent<SpriteRenderer>()->Init(sprite);
		MapEditor::Tile_Space[i]->SetActive(isActive);
		MapEditor::Tile_Space[i]->SetPosition(Vec3(getX, getY));

		//Move pointer to the next
		i++;
		lpBlock = (tinyxml2::XMLElement*)lpBlock->NextSibling();
	}

}
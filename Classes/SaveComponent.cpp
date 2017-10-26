#define _CRT_SECURE_NO_WARNINGS
#include "SaveComponent.h"
#include "MapEditor.h"

SaveComponent* SaveComponent::Init(MapEditor* lpScene)
{
	lpMapEditor = lpScene;

	CreateKeyListener();
	keyListener = GetKeyListener();

	return this;
}

void SaveComponent::Update(Time& time)
{
	if (keyListener->IsKeyDown(KeyCode::F5)) Save();
	if (keyListener->IsKeyDown(KeyCode::F7)) Load();
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
		
		block[i]->SetAttribute("Sprite", lpMapEditor->Tile_Space[i]->GetComponent<SpriteRenderer>()->GetTexture()->GetFilename().c_str());
		block[i]->SetAttribute("IsActive", lpMapEditor->Tile_Space[i]->IsActive());
		block[i]->SetAttribute("GetX", lpMapEditor->Tile_Space[i]->GetPosition().x);
		block[i]->SetAttribute("GetY", lpMapEditor->Tile_Space[i]->GetPosition().y);
	}

	//Save at
	puts("[SAVE] Enter your save file name without extension");
	char path[MAX_PATH] = { 0, };
	scanf("%s", path);
	strcat(path, ".mapinfo");
	saveDest.SaveFile(path);

	//ENCRYPTING
	//
}
void SaveComponent::Load()
{
	//Get path
	puts("[LOAD] Enter file name you wanna load without extension");
	char path[MAX_PATH] = { 0, };
	scanf("%s", path);
	strcat(path, ".mapinfo");

	//DECRYPTING
	//

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
		lpMapEditor->Tile_Space[i]->GetComponent<SpriteRenderer>()->Init(sprite);
		lpMapEditor->Tile_Space[i]->SetActive(isActive);
		lpMapEditor->Tile_Space[i]->SetPosition(Vec3(getX, getY));

		//Move pointer to the next
		i++;
		lpBlock = (tinyxml2::XMLElement*)lpBlock->NextSibling();
	}

}

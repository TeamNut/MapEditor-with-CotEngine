#include "BlockSelfComponent.h"
#include <iostream>

#define RADIUS_BLOCK 75 //Area of half of block

bool once = false;

BlockSelfComponent* BlockSelfComponent::Init(MapEditor* lpScene)
{
	lpMapEditor = lpScene;

	CreateMouseListener();

	_renderer = GetOwner()->GetComponent<SpriteRenderer>();

	return this;
}

void BlockSelfComponent::Update(Time& time)
{
	//MDF
	_renderer->SetDepth(-5);
	tempVec3 = GetOwner()->GetPosition();

	selfArea = { (int)tempVec3.x - RADIUS_BLOCK, (int)tempVec3.y - RADIUS_BLOCK, (int)tempVec3.x + RADIUS_BLOCK, (int)tempVec3.y + RADIUS_BLOCK };
	//selfArea = RECT{ (int)_renderer->GetRect().GetMaxX(), (int)_renderer->GetRect().GetMinY(), (int)_renderer->GetRect().GetMaxX(), (int)_renderer->GetRect().GetMaxY() };

	//Remove
	if (lpMapEditor->IsAreaStay(selfArea, MouseButton::RButton, GetMouseListener()))
	{
		lpMapEditor->DeleteTile(GetOwner());
	}
}
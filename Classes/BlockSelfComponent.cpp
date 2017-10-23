#include "BlockSelfComponent.h"
//Initialize to use exterior something

#define RADIUS_BLOCK 75 //Area of half of block

BlockSelfComponent* BlockSelfComponent::Init()
{

	return this;
}

void BlockSelfComponent::OnEnable()
{

}

void BlockSelfComponent::Reset()
{

}

void BlockSelfComponent::Awake()
{

}

void BlockSelfComponent::Start()
{

}

void BlockSelfComponent::Update(Time& time)
{
	GetOwner()->GetComponent<SpriteRenderer>()->SetDepth(-5);
	tempVec3 = GetOwner()->GetPosition();
	selfArea = { (int)tempVec3.x - RADIUS_BLOCK, (int)tempVec3.y - RADIUS_BLOCK, (int)tempVec3.x + RADIUS_BLOCK, (int)tempVec3.y + RADIUS_BLOCK };

	//Click detection
	if (IsMouseStay(MouseButton::RButton) == true)
	{
		if ((int)GetMousePosition().x >= selfArea.left &&
			(int)GetMousePosition().x <= selfArea.right &&
			(int)GetMousePosition().y <= selfArea.bottom &&
			(int)GetMousePosition().y >= selfArea.top)
		{
			MapEditor::DeleteTile(GetOwner());
		}
	}
}

void BlockSelfComponent::OnDisable()
{

}

void BlockSelfComponent::OnDestroy()
{

}

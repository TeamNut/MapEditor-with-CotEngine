#pragma once

#include <CotEngine.h>
#include "MapEditor.h" //To use all of function and value

using namespace Cot;

Component(BlockSelfComponent)
{
	COT_COMPONENT(BlockSelfComponent);
private:
	Vec3 tempVec3; //Save position
	RECT selfArea; //Area of blockself

public:
	BlockSelfComponent* Init();

	void OnEnable() override;
	void Reset() override;
	void Awake() override;
	void Start() override;
	void Update(Time& time) override;
	void OnDisable() override;
	void OnDestroy() override;
};
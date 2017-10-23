#pragma once

#include <CotEngine.h>
#include "MapEditor.h"
#include "HeadValue.h"
#include "tinyxml2\tinyxml2.h"

using namespace Cot;

Component(SaveComponent)
{
	COT_COMPONENT(SaveComponent);
private:
	std::string _str;
	float _count;


public:
	SaveComponent* Init(const string& str);

	void OnEnable() override;
	void Reset() override;
	void Awake() override;
	void Start() override;
	void Update(Time& time) override;
	void OnDisable() override;
	void OnDestroy() override;

	void Save();
	void Load();
};
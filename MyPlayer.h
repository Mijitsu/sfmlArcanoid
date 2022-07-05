#pragma once
#include "MyObject.h"

class MyPlayer : public MyObject {
	float speed;
public:
	MyPlayer();
	~MyPlayer();
	virtual void Update() override;
};

#pragma once
#include <string>
#include "Memory.h"
#include "Offsets.h"
#include "Geom.h"

class Entity {
	uint32_t address;
	Vec3 position;
	float yaw;
	float pitch;
	int health;
	int team;
	std::string name;
	Memory* memory;
	
public:
	Entity(Memory *memory, uint32_t address);

	std::string getName() {
		return name;
	}

	int getTeam() {
		return team;
	}

	int getHealth();
	Vec3 getHeadPos();
	Vec3 getFeetPos();
	void setYaw(float yaw);
	void setPitch(float pitch);
};


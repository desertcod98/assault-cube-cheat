#include <iostream>
#include <iomanip>
#include <sstream>
#include "Memory.h"
#include "Offsets.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "Entity.h"
#include <vector>

const double PI = 3.14159265358979323846;
int screenXa = GetSystemMetrics(SM_CXSCREEN);
int screenYa = GetSystemMetrics(SM_CYSCREEN);

int main()
{
    auto memory = Memory("ac_client.exe");
    auto moduleAddress = memory.GetModuleAddress("ac_client.exe");
    uintptr_t playerOffset = moduleAddress + offsets::player_base_ptr;
    uintptr_t player = memory.Read<uint32_t>(playerOffset);
    Entity playerEntity = Entity(&memory, player);

    const uint32_t entityListBase = moduleAddress + offsets::entity_list_base_ptr;
    const uint32_t entityList = memory.Read<uint32_t>(entityListBase);

    std::vector<Entity> entities;

    for (int i = 0; i < 32; i++) { //32 is max player count - the player
        const uint32_t entityOffset = entityList + ((i + 1) * 4);
        const uint32_t entityBase = memory.Read<uint32_t>(entityOffset);

        if(!memory.isValidAddress(entityBase)) break;
        if (!memory.isValidEntity(entityBase)) break;

        Entity entity = Entity(&memory, entityBase); 
        entities.push_back(entity);
    }

    setRect();
	while (true)
	{
		view_matrix_t vm = memory.Read<view_matrix_t>(moduleAddress + offsets::matrix_base_ptr);
        
        int closestEntityIdx = -1;
        float closestEntityDistance = -1;

        Vec3 playerEntityHead = playerEntity.getHeadPos();

		for (int i = 0; i < entities.size(); i++) {
            if (entities[i].getTeam() == playerEntity.getTeam()) continue;
            if (entities[i].getHealth() < 1) continue;

            //ESP
			Vec3 headPos = entities[i].getHeadPos();
			Vec3 screenHeadPos = WorldToScreen(headPos, vm);
            Vec3 feetPos = entities[i].getFeetPos();
            Vec3 screenFeetPos = WorldToScreen(feetPos, vm);

            float h = screenFeetPos.y - screenHeadPos.y;
            float w = h / 2;

			DrawBorderBox(screenHeadPos.x - w/2, screenHeadPos.y - 30, w, h, 2);

            // PREP AIMBOT
            if (closestEntityIdx == -1) {
                closestEntityIdx = i;
                closestEntityDistance = Vec3SquareDistance(playerEntityHead, headPos);
            }
            else {
                if (closestEntityDistance > Vec3SquareDistance(playerEntityHead, headPos)) {
                    closestEntityIdx = i;
                    closestEntityDistance = Vec3SquareDistance(playerEntityHead, headPos);
                }
            }
		}
        //AIMBOT

        if (GetAsyncKeyState(VK_RBUTTON) && closestEntityIdx != -1) {
            Vec3 enemyPos = entities[closestEntityIdx].getHeadPos();
            Vec3 distance = enemyPos - playerEntityHead;

            float yaw = (float)std::atan2(distance.y, distance.x) * 180 / PI + 90;
            float pitch = (float)std::atan2(distance.z, std::sqrt(distance.x * distance.x + distance.y * distance.y)) * 180 / PI;
           
            if (yaw != 0) playerEntity.setYaw(yaw);
            playerEntity.setPitch(pitch);
        }
	}

    return 0;
}


#pragma once

namespace offsets {
	static int player_base_ptr = 0x195404;

	static int entity_health = 0xEC;
	static int entity_name = 0x205;
	static int entity_head = 0x4;
	static int entity_feet = 0x28;
	static int entity_team = 0x30C;
	static int entity_yaw = 0x34;
	static int entity_pitch = 0x38;

	static int entity_list_base_ptr = 0x18AC04;

	static int matrix_base_ptr = 0x17E094 - 0x104 + (16 * 0x4);
}

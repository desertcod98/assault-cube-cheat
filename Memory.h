#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Geom.h"

class Memory {
private:
	DWORD id = 0; //process id
	HANDLE process = NULL;

public:
	Memory(const std::string processName);
	~Memory();

	DWORD GetProcessId();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAddress(const std::string moduleName);

	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

	bool isValidAddress(uintptr_t address);
	bool isValidEntity(uint32_t address);

	template <typename T>
	T Read(uintptr_t address, int size = -1) {
		T value;
		const int res = ReadProcessMemory(this->process, (LPCVOID)address, &value, size == -1 ? sizeof(T) : size, NULL);
		
	
		return value;
	}

	std::string ReadString(uintptr_t address, int size) {
		char res[128];
		ReadProcessMemory(this->process, (LPCVOID)address, &res, sizeof(res), NULL);
		res[strlen(res)] = '\0';
		std::string final = std::string(res);
		return final;
	}

	Vec3 ReadVec3(uintptr_t address) {
		byte buf[4 * 3];
		ReadProcessMemory(this->process, (LPCVOID)address, &buf, sizeof(buf), NULL);
		float x;
		float y;
		float z;
		memcpy(&x, buf, 4);
		memcpy(&y, buf + 4, 4);
		memcpy(&z, buf + 8, 4);
		return Vec3{ x,y,z };
	}

	template <typename T>
	bool Write(uintptr_t address, T value) {
		return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
	}
};
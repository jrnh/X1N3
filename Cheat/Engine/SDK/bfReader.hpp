#include "SDK.h"
#pragma once

namespace SDK
{
	class bf_Read
	{
	public:
		uintptr_t base_address;
		uintptr_t cur_offset;

		bf_Read::bf_Read(uintptr_t addr)
		{
			base_address = addr;
			cur_offset = 0;
		}

		void bf_Read::SetOffset(uintptr_t offset)
		{
			cur_offset = offset;
		}

		void bf_Read::Skip(uintptr_t length)
		{
			cur_offset += length;
		}

		int bf_Read::ReadByte()
		{
			auto val = *reinterpret_cast<char*>(base_address + cur_offset);
			++cur_offset;
			return val;
		}

		bool bf_Read::ReadBool()
		{
			auto val = *reinterpret_cast<bool*>(base_address + cur_offset);
			++cur_offset;
			return val;
		}

		std::string bf_Read::ReadString()
		{
			char buffer[1024];
			auto str_length = *reinterpret_cast<char*>(base_address + cur_offset);
			++cur_offset;
			memcpy(buffer, reinterpret_cast<void*>(base_address + cur_offset), str_length > 255 ? 255 : str_length);
			buffer[str_length > 255 ? 255 : str_length] = '\0';
			cur_offset += str_length + 1;
			return std::string(buffer);
		}
	};
}
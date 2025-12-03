#pragma once

/*
 *  NFSVersionManager - Detects NFS game version using module entry point analysis
 * 
 *  Supported games:
 *   - Underground         v1.4         3.178.496 bytes
 *   - Underground 2       v1.2         4.800.512 bytes
 *   - Most Wanted 2005    v1.3         6.029.312 bytes
 *   - Carbon              v1.4         7.217.152 bytes
 *   - Prostreet           v1.1        28.739.656 bytes
 *   - Undercover          v1.0.0.1    10.589.456 bytes
 *   - The Run             v1.1.0.0    38.027.264 bytes
 *  
 *  Windows-only library
 * 
 *  Version v1.3.0
 *  GitHub page: https://github.com/Kevin4e/NFSVersionManager
 *  Author: Kevin4e
 *
 *  Target: C++17+
 */

 /*
  *  MIT License
  *  Copyright (c) 2025 Kevin4e
  *
  *  Permission is hereby granted, free of charge, to any person obtaining a copy
  *  of this software and associated documentation files (the "Software"), to deal
  *  in the Software without restriction, including without limitation the rights
  *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
  *  and to permit persons to whom the Software is
  *  furnished to do so, subject to the following conditions:
  *
  *  The above copyright notice and this permission notice shall be included in all
  *  copies or substantial portions of the Software.
  *
  *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  *  SOFTWARE.
  */

#include <Windows.h>
#include <cstdint>
#include <unordered_map>

struct NFSVersionManager {
public:
	// Keys used to identify each supported game
	enum class GameKey {
		Underground,
		Underground2,
		MostWanted,
		Carbon,
		Prostreet,
		Undercover,
		TheRun,
		UnknownNFS // Internal fallback, not meant to be checked by users
	};

private:
	// Finds the entry point relative virtual address (RVA) of the process into which the DLL has been injected
	static inline const uintptr_t entryPointRVA = []() noexcept {
		uintptr_t baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
		IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(baseAddress);
		IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(baseAddress + dosHeader->e_lfanew);

		return ntHeader->OptionalHeader.AddressOfEntryPoint;
	}();

	// Structure representing each game characterized by its executable's RVA and key
	static inline const std::unordered_map<uintptr_t, GameKey> games = {
		{ 0x270CB5,  GameKey::Underground  },
		{ 0x35BCC7,  GameKey::Underground2 },
		{ 0x3C4040,  GameKey::MostWanted   },
		{ 0x47E926,  GameKey::Carbon       },
		{ 0x428C25,  GameKey::Prostreet    },
		{ 0x4AEC55,  GameKey::Undercover   },
		{ 0x1005AFF, GameKey::TheRun       }
	};

public:
	// Finds the game given the RVA
	static inline GameKey detectedGameKey = []() noexcept {
		auto rvaIt = games.find(entryPointRVA);
		return rvaIt == games.end() ? GameKey::UnknownNFS : rvaIt->second;
	}();

	// Checks if the DLL has been injected into a specific game
	static inline bool is(GameKey gameKey) noexcept {
		return gameKey == detectedGameKey; // If it's the same as the detected game
	}
};
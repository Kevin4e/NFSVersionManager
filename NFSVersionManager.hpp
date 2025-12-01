#pragma once

/*
 *  NFSVersionManager - Detects NFS game version using module entry point analysis
 * 
 *  Supported games:
 *   - Underground       v1.4
 *   - Underground 2     v1.2
 *   - Most Wanted 2005  v1.3
 *   - Carbon            v1.4
 *   - Prostreet         v1.1
 *   - Undercover        v1.0.0.1
 *   - The Run           v1.1.0.0
 *  
 *  Windows-only library
 * 
 *  Version v1.1.0
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
#include <string>
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
	struct GameInfo {
		GameKey gameKey;
		std::string title;
		std::string exeSize; // in bytes
	};

	// Finds the entry point relative virtual address (RVA) of the process in which the DLL has been injected into
	static inline const uintptr_t entryPointRVA = []() noexcept {
		uintptr_t baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
		IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(baseAddress);
		IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(baseAddress + dosHeader->e_lfanew);

		return ntHeader->OptionalHeader.AddressOfEntryPoint;
	}();

	static inline std::string errorMessage{};

	// Builds the error message after a game's check fail
	static inline void setError(const GameInfo& gInfo) noexcept {
		errorMessage =
			"This .exe is not compatible. \r\n"
			"Use " + gInfo.title + " executable. \r\n"
			"Expected size: " + gInfo.exeSize + " bytes. \r\n";
	}

	// Structure representing each game characterized by its executable's RVA, key, title and size in bytes
	static inline const std::unordered_map<uintptr_t, GameInfo> games = {
		{ 0x270CB5,  { GameKey::Underground,   "Underground v1.4",      "3.178.496" } },
		{ 0x35BCC7,  { GameKey::Underground2,  "Underground 2 v1.2",    "4.800.512" } },
		{ 0x3C4040,  { GameKey::MostWanted,    "Most Wanted v1.3",      "6.029.312" } },
		{ 0x47E926,  { GameKey::Carbon,        "Carbon v1.4",           "7.217.152" } },
		{ 0x428C25,  { GameKey::Prostreet,     "Prostreet v1.1",       "28.739.656" } },
		{ 0x4AEC55,  { GameKey::Undercover,    "Undercover v1.0.0.1",  "10.589.456" } },
		{ 0x1005AFF, { GameKey::TheRun,        "The Run v1.1.0.0",     "38.027.264" } }
	};

public:
	// Finds the game given the RVA
	static inline GameKey detectedGameKey = []() noexcept {
		auto rvaIt = games.find(entryPointRVA);
		if (rvaIt == games.end()) return GameKey::UnknownNFS;

		return (rvaIt->second).gameKey;
	}();

	/*  Checks if the DLL has been injected into a specific game
	 *  If not, there happen one of the two cases:
	 * 
	 *  - The input parameter (g) is a game, and it builds the error message if 'buildError' is true related to that game
	 *  - The input parameter (g) is NOT a game (Game::UnknownNFS) and it won't build an error message (because it's not related to a supported game)
	 * 
	 *  Both cases return false, either way
	 */ 
	static inline bool is(GameKey gKey, bool buildError = false) noexcept {
		if (gKey == detectedGameKey) // If it's the same as the detected game
			return true;

		if (buildError) {
			auto gameInfoIt = std::find_if(games.begin(), games.end(), [gKey](const auto& pair) { // Find iterator of the game the same as 'g'
				return pair.second.gameKey == gKey;
			});

			if (gameInfoIt != games.end())
				setError(gameInfoIt->second);
		}
		
		return false;
	}

	// Returns the error message built from a failed check
	static inline std::string getErrorMessage() noexcept {
		return errorMessage;
	}

	// Displays the error message built from a failed check with a message box with an optional title
	static inline void displayErrorMessage(const std::string& title = "") noexcept {
		MessageBoxA(nullptr, errorMessage.c_str(), title.c_str(), MB_ICONERROR);
	}
};
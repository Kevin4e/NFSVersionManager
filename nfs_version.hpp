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
 *  Version v1.0.0
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

struct NFSVersionManager {
private:
	static inline uintptr_t entryPointRVA = []() {
		uintptr_t baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
		IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(baseAddress);
		IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(baseAddress + dosHeader->e_lfanew);

		return ntHeader->OptionalHeader.AddressOfEntryPoint;
	}();

	static inline std::string errorMessage{};

	static inline void setError(const std::string& game) noexcept {
		errorMessage =
			"This .exe is not compatible \n"
			"Use " + game + " executable. \n";
	}
public:
	static inline bool isUG1/*_1_4*/ () noexcept { // Underground v1.4
		if (entryPointRVA == 0x270CB5)
			return true;

		setError("Underground v1.4");

		return false;
	} 
	static inline bool isUG2/*_1_2*/() noexcept { // Underground 2 v1.2
		if (entryPointRVA == 0x35BCC7)
			return true;

		setError("Underground 2 v1.2");

		return false;
	}
	static inline bool isMW05/*_1_3*/() noexcept { // Most Wanted v1.3
		if (entryPointRVA == 0x3C4040)
			return true;

		setError("Most Wanted v1.3");

		return false;
	}
	static inline bool isCarbon/*_1_4*/() noexcept { // Carbon v1.4
		if (entryPointRVA == 0x47E926)
			return true;

		setError("Carbon v1.4");

		return false;
	}
	static inline bool isPS/*_1_1*/() noexcept { // Prostreet v1.1
		if (entryPointRVA == 0x428C25)
			return true;

		setError("Prostreet v1.1");

		return false;
	}
	static inline bool isUC/*_1_0_0_1*/() noexcept { // Undercover v1.0.0.1
		if (entryPointRVA == 0x4AEC55)
			return true;

		setError("Undercover v1.0.0.1");

		return false;
	}
	static inline bool isTR/*_1_1_0_0*/() noexcept { // The Run v1.1.0.0
		if (entryPointRVA == 0x1005AFF)
			return true;

		setError("The Run v1.1.0.0");

		return false;
	}
	static inline std::string getErrorMessage() noexcept {
		return errorMessage;
	}
	static inline void displayErrorMessage(const std::string& title = "") noexcept {
		MessageBoxA(nullptr, errorMessage.c_str(), title.c_str(), MB_ICONERROR);
	}
};
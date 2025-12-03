# NFS Version Manager
Detects NFS game version using module entry point analysis

## Overview
This library lets you check if a DLL was injected into a specific NFS game.

**C++17+** is required.

Supported games:
- **Underground**       `v1.4`
- **Underground 2**     `v1.2`
- **Most Wanted 2005**  `v1.3`
- **Carbon**            `v1.4`
- **Prostreet**         `v1.1`
- **Undercover**        `v1.0.0.1`
- **The Run**           `v1.1.0.0`

## Usage
To check the game, follow the prototype:
```cpp
if (NFSVersionManager::is(NFSVersionManager::GameKey::TheGameToCheck)) {
    // if body
}
else {
    // else body
}
```

---

Available enum keys:

```cpp
NFSVersionManager::GameKey::Underground;
NFSVersionManager::GameKey::Underground2;
NFSVersionManager::GameKey::MostWanted;
NFSVersionManager::GameKey::Carbon;
NFSVersionManager::GameKey::Prostreet;
NFSVersionManager::GameKey::Undercover;
NFSVersionManager::GameKey::TheRun;
NFSVersionManager::GameKey::UnknownNFS; // Internal fallback, not meant to be checked by users
```

---

### Tip
To reduce verbosity, use the following expression:
```cpp
using enum NFSVersionManager::GameKey; // Requires C++20
```
You can now use any enum key listed above without `NFSVersionManager::GameKey::`

---

### Full example
```cpp
using enum NFSVersionManager::GameKey;

BOOL WINAPI DllMain(HINSTANCE, DWORD ul_reason_for_call, LPVOID) // DLL entry point
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        if (!NFSVersionManager::is(MostWanted)) // If the DLL was not injected into Most Wanted v1.3
        {
            MessageBoxA (
                nullptr,
                "This .exe is not compatible. \r\n"
                "Use Most Wanted v1.3 executable. \r\n"
                "Expected size: 6.029.312 bytes.",
                "NFSMW Heat Raise via CTS by Kevin4e",
                MB_ICONERROR
            );
            
            return FALSE; // Detach DLL
        }
    }

    return TRUE;
}
```

## Credits
- **Kevin4e** - Author of the library

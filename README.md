# NFS Version Manager
Detects NFS game version using module entry point analysis

## Overview
This library lets you check if a DLL has been injected into a specific NFS game.

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
if (NFSVersionManager::is(NFSVersionManager::Game::TheGameToCheck)) {
    // if body
}
else {
    // else body
}
```

Function prototype:
```cpp
static inline bool is(Game g, bool buildError = false) noexcept;
```
If the check has failed, the library builds an error message related to the game if `buildError` is `true`.  
For example, if the check for **Most Wanted v1.3** has failed, the error message is this:  

```text
This .exe is not compatible.
Use Most Wanted v1.3 executable.
Expected size: 3.178.496 bytes.
```

You can directly display it with a message box by using:
```cpp
NFSVersionManager::displayErrorMessage("Message box title");
```

Or you can have it as string format by using:
```cpp
NFSVersionManager::getErrorMessage();
```

---

Available enum keys:

```cpp
NFSVersionManager::Game::Underground;
NFSVersionManager::Game::Underground2;
NFSVersionManager::Game::MostWanted;
NFSVersionManager::Game::Carbon;
NFSVersionManager::Game::Prostreet;
NFSVersionManager::Game::Undercover;
NFSVersionManager::Game::TheRun;
```

---

### Pro tip
To avoid verbosity, use the following expression:
```cpp
using enum NFSVersionManager::Game;
```
You can now use an enum key without `NFSVersionManager::Game::`

---

### Full example
```cpp
BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        if (!NFSVersionManager::is(MostWanted, true)) // If the DLL has not been injected into Most Wanted v1.3
        {
            NFSVersionManager::displayErrorMessage("My Mod by Author123");
            return FALSE; // Detach DLL
        }
    }

    return TRUE;
}
```

## Credits
- **Kevin4e** - Author of the library

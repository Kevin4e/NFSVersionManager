# NFSVersionManager
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
if (NFSVersionManager::isGAME()) {
    // if body
}
else {
    // else body
}
```

If the check has failed, the library builds an error message related to the game.  
For example, if the check for **Most Wanted v1.3** has failed, the error message is this:  

```text
This .exe is not compatible
Use Most Wanted v1.3 executable.
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

Available check functions:

```cpp
NFSVersionManager::isUG1();
NFSVersionManager::isUG2();
NFSVersionManager::isMW05();
NFSVersionManager::isCarbon();
NFSVersionManager::isPS();
NFSVersionManager::isUC();
NFSVersionManager::isTR();
```

## Credits
- **Kevin4e** - Author of the library

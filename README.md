# stdiopp.h

A lightweight C++ header library providing simplified I/O functions and useful utility tools for C++ projects.

## Features

### Core Functions
- **`printf(value)`** - Simplified console output (replaces `std::cout`)
- **`scanf(value)`** - Simplified console input (replaces `std::cin`)

### Utility Modules
- **`knif()`** - Calculate total code size across your project
  - Scans for `.cpp`, `.h`, `.hpp`, `.c`, `.inl` files
  - Reports file count and total size in KB/MB
  
- **`memory()`** - Display current RAM usage of your process
  - Cross-platform support (Windows, Linux, macOS)
  - Shows memory consumption in MB

- **`cpp_version()`** - Display the C++ standard version being used
  - Detects C++98 through C++26

## Installation

Simply copy `stdiopp.h` to your project directory and include it:

```cpp
#include "stdiopp.h"
```

## Requirements

- C++17 or higher (uses `<filesystem>`)
- Compiler support for your platform (Windows, Linux, or macOS)

## Usage Examples

### Basic I/O
```cpp
#include "stdiopp.h"

int main() {
    printf("Hello, World!\n");
    
    int number;
    printf("Enter a number: ");
    scanf(number);
    printf("You entered: ");
    printf(number);
    printf("\n");
    
    return 0;
}
```

### Utility Functions
```cpp
#include "stdiopp.h"

int main() {
    // Check C++ version
    cpp_version();
    
    // Display memory usage
    memory();
    
    // Calculate project code size
    knif();
    
    return 0;
}
```

### Example Output
```
C++ Version: C++17
Memory used: 2.45 MB
Code files: 15 | Size: 42.8 KB (0.04 MB)
```

## Platform Support

| Feature | Windows | Linux | macOS |
|---------|---------|-------|-------|
| `printf/scanf` | ✅ | ✅ | ✅ |
| `knif()` | ✅ | ✅ | ✅ |
| `memory()` | ✅ | ✅ | ✅ |
| `cpp_version()` | ✅ | ✅ | ✅ |

## How It Works

- **`knif()`** recursively scans your project folder (two levels up from the executable) for source files
- **`memory()`** uses platform-specific APIs:
  - Windows: `GetProcessMemoryInfo`
  - Linux: `getrusage`
  - macOS: `task_info`
- **I/O functions** are template-based wrappers around standard C++ streams

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## Author

**Max-Mend**

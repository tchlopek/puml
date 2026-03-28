# PlantUML State Diagram Parser

A C++17 library for parsing PlantUML state diagram syntax into an in-memory representation. This parser reads `.puml` files containing state diagram definitions and provides a structured API for programmatically working with state machines.

**Important:** The parser is not feature-complete. It was created for the state diagrams in mind, and currently supports only limited syntax.

## Features

- **Full State Diagram Support**: Parse complete PlantUML state diagram syntax including simple states, composite states, transitions, and default transitions
- **Structured Representation**: Convert parsed diagrams into strongly-typed C++ objects for easy manipulation
- **Error Reporting**: Comprehensive error messages with file position information
- **CMake Integration**: Easy to integrate into existing CMake projects
- **Modern C++**: Built with C++17 standard

## Building

### Prerequisites

- CMake >= 3.13
- C++17 compatible compiler (GCC on Linux)
- Ninja build system

### Quick Start with CMake Presets

This project includes CMake presets for convenient building. Use the following commands:

#### Debug Build

```bash
cmake --preset linux-cfg-debug
cmake --build --preset linux-build-debug
```

#### Release Build

```bash
cmake --preset linux-cfg-release
cmake --build --preset linux-build-release
```

#### Build with Tests

```bash
cmake --preset linux-cfg-test
cmake --build --preset linux-build-test
ctest --preset linux-test
```

### Available Presets

**Configure Presets:**
- `linux-cfg-debug` - Debug configuration with shared libraries enabled
- `linux-cfg-release` - Release configuration with shared libraries enabled
- `linux-cfg-test` - Test configuration (static linking, debug info, tests enabled)

**Build Presets:**
- `linux-build-debug` - Builds debug configuration
- `linux-build-release` - Builds release configuration (optimized)
- `linux-build-test` - Builds test suite

**Test Presets:**
- `linux-test` - Runs the test suite

### Build Output

Build artifacts are automatically placed in `build/` directory organized by preset name:
```
build/
├── linux-cfg-debug/      # Debug build output
├── linux-cfg-release/    # Release build output
└── linux-cfg-test/       # Test build output
```

## Integration

### CMake Integration

To integrate this library into your CMake project:

```cmake
# Option 1: Add as subdirectory
add_subdirectory(path/to/parser)

# Option 2: Use installed package
find_package(puml REQUIRED)

target_link_libraries(your_target PRIVATE puml::puml)
```

Include the header in your code:

```cpp
#include <puml/puml.hpp>
```

### Installation

After building with your chosen preset:

```bash
# For debug build
cmake --install build/linux-cfg-debug

# For release build
cmake --install build/linux-cfg-release
```

To specify a custom installation path:

```bash
cmake --install build/linux-cfg-release --prefix /custom/path
```

The library will be installed to the system default location (usually `/usr/local`) unless otherwise specified.

## Usage Example

```cpp
#include <puml/puml.hpp>
#include <iostream>
#include <filesystem>

int main() {
    // Parse a PlantUML state diagram file
    std::filesystem::path diagram_path = "state_diagram.puml";
    
    auto diagram = puml::parse(diagram_path);
    
    // Check for parsing errors
    if (!diagram.get_errors().empty()) {
        for (const auto& error : diagram.get_errors()) {
            std::cerr << "Parse error: " << error << std::endl;
        }
        return 1;
    }
    
    // Access the parsed states
    const auto& states = diagram.get_states();
    
    for (const auto& state : states) {
        std::cout << "State: " << state->get_name() << std::endl;
        
        // Access child states if composite
        if (!state->get_child_states().empty()) {
            std::cout << "  Child states:" << std::endl;
            for (const auto& child : state->get_child_states()) {
                std::cout << "    - " << child->get_name() << std::endl;
            }
        }
    }
    
    // Access transitions
    const auto& transitions = diagram.get_transitions();
    
    for (const auto& transition : transitions) {
        std::cout << "Transition: " << transition.get_source() 
                  << " -> " << transition.get_target();
        if (!transition.get_label().empty()) {
            std::cout << " [" << transition.get_label() << "]";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
```

## API Overview

### Main Types

- **`diagram`**: Represents a complete state diagram with states and transitions
- **`state`**: Represents a state (can be simple or composite)
- **`transition`**: Represents a transition between states
- **`context`**: Internal parser context for managing parsing state

### Key Functions

- `parse(const std::filesystem::path& filepath)`: Parse a PlantUML file and return a diagram
- `diagram::get_states()`: Get all top-level states
- `diagram::get_transitions()`: Get all transitions in the diagram
- `diagram::get_errors()`: Get any parsing errors that occurred
- `state::get_name()`: Get the state's name
- `state::get_child_states()`: Get child states (if composite)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Copyright (c) 2026 Tomasz Chłopek**

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## Project Structure

```
.
├── include/puml/          # Public API headers
│   ├── api.hpp           # API visibility macros
│   ├── puml.hpp          # Main header
│   ├── state.hpp         # State type definition
│   └── transition.hpp    # Transition type definition
├── src/
│   ├── builder.cpp/hpp   # Constructs diagram from CST
│   ├── context.cpp/hpp   # Parsing context management
│   ├── parser.cpp        # Main parsing entry point
│   ├── cst/              # Concrete Syntax Tree (internal)
│   └── token/            # Tokenization and lexical analysis
├── test/                 # Unit tests
├── CMakeLists.txt        # Build configuration
├── README.md             # This file
└── LICENSE               # MIT License
```

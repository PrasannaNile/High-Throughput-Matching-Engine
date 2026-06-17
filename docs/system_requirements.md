# Build & Toolchain Specification:

This document specifies the software requirements and the custom CMake build configuration used to compile this multi-file C++ project.

---

## 1. System Requirements

To build and run this project, your system must meet the following software requirements:

*   **Operating System**: Windows (10 or 11 recommended).
*   **C++ Compiler**: MinGW-w64 (GCC-based toolchain configured for Windows).
*   **Build System**: CMake (version 3.10 or higher recommended) and GNU Make.
*   **Dependencies**: Non-standard external libraries are required (located via custom modules).

---

## 2. CMake Project Architecture

The `CMakeLists.txt` is configured to organize the project structure dynamically, separating temporary build artifacts from final executable files.

*   **`build/` (Temporary Workspace)**: Contains all temporary configuration data, dependency caches, and compiled object (`.obj`) files. This directory keeps the root folder clean.
*   **`bin/` (Distribution Directory)**: The final compiled executable (`.exe`) file is automatically redirected here upon a successful build.
*   **`cmake/` (Custom Module Path)**: Contains specialized `Find<Library>.cmake` scripts. These modules tell CMake exactly where and how to locate complex, non-standard external dependencies.

---

## 3. Configuration & Compilation Guide

Follow these steps to generate the build files and compile the project using the command line.

### Step 1: Create the Build Workspace
Open your terminal in the project root directory and create the temporary `build` folder:
```bash
mkdir build
cd build
```

### Step 2: Configure the Project
Run the CMake configuration step. This command explicitly instructs CMake to use the **MinGW Makefiles** generator:
```bash
cmake -G "MinGW Makefiles" ..
```
*During this phase, CMake scans the `cmake/` folder to resolve external libraries and map the output paths.*

### Step 3: Build the Project
Compile the `.cpp` and `.h` source files into the final binary:
```bash
cmake --build .
```

### Step 4: Run the Application
Once the build completes successfully, navigate to the `bin` folder at the project root to run your executable:
```bash
cd ../bin
./your_executable_name.exe
```

---

## 4. Maintenance Notes
*   **Cleaning the Build**: To completely reset your environment, simply delete the `build/` and `bin/` directories.
*   **Adding Libraries**: If you introduce a new non-standard external dependency, place its corresponding `Find<Name>.cmake` file inside the `cmake/` directory.



# FUNCTIONAL REQUIREMENTS:

## Order Placement:
## Order Cancellation:
## Trade Reporting:


# NON-FUNCTIONAL REQUIREMENTS:

## Latency Priority:
## Thread Isolation:
## Data Persistence:


# OUT OF SCOPE:

## A Network Interface:
## User authentication or complex risk-management checks:
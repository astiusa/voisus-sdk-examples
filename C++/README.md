# Voisus C++ SDK Example

Included here is source code for an example application that uses the Voisus Client API. This example can be built for Linux or Windows.

## Linux

 * First install the Original Desktop Client for Linux (downloadable from Voisus Server)
 * Install CMake tool to generate Makefile (using your package manager)
 * Run ```cmake .``` in the C++ directory
 * Run ```make``` to build the example
 * Run ```./voisus-sdk-example``` to run the example

## Windows

 * First install the Original Desktop Client for Windows (downloadable from Voisus Server)
 * Install CMake to generate Visual Studio solution (from https://cmake.org/download/)
 * Run CMake GUI from start menu
   * Select the C++ directory as source directory and a new directory as build directory (BUILDDIR)
   * Configure and generate the solution
 * Open Visual Studio solution voisus-sdk-example created in build directory
 * Copy the VRCClient.lib file into the build directory
 * Build the solution in Visual Studio
 * Copy VRCClient.dll from Original Desktop Client install directory (e.g. C:\Program Files (x86)\ASTi\VoisusClient) into the directory with voisus-sdk-example executable (i.e. BUILDDIR\Debug or BUILDDIR\Release).
 * Run the voisus-sdk-example executable

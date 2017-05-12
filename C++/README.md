# Voisus C++ SDK Example

Included here is source code for a console application that uses the Voisus Client SDK library. This example can be built for Linux or Windows.

## Building the Example

### Linux

 * First install the Original Desktop Client for Linux (downloadable from Voisus Server)
 * Install CMake tool to generate Makefile (using your package manager)
 * Run ```cmake .``` in the C++ directory
 * Run ```make``` to build the example
 * Run ```./voisus-sdk-example``` to run the example

### Windows

 * First install the Original Desktop Client for Windows (downloadable from Voisus Server)
 * Install CMake to generate Visual Studio solution (from https://cmake.org/download/)
 * Run CMake GUI from start menu
   * Select the C++ directory as source directory and a new directory as build directory
   * Configure and generate the solution
 * Open Visual Studio solution voisus-sdk-example created in build directory
 * Copy the VRCClient.lib file into the build directory
 * Build the solution in Visual Studio
 * Copy VRCClient.dll from Original Desktop Client install directory (e.g. C:\Program Files (x86)\ASTi\VoisusClient) into the directory with voisus-sdk-example executable (i.e. Debug or Release in build dir).
 * Run the voisus-sdk-example executable

## Using the Example

To begin, you must have a Voisus server running a scenario that is configured with Roles and a Comm Plan. It may be helpful to first run the Original Desktop Client and connect to the server on your machine.

Here are some basic commands to run:
 * To connect the example application to the server, enter ```connect```. Then enter the IP address of the Voisus server.
 * To set a role, first get the list of roles by entering the ```get_roles``` command. Then use the ```set_role``` command to set a role using the role index number.
 * Use the ```status``` command at any time to check the connection state.
 * Use the ```get_radios``` command once connected to list the radios and their state.
 * **Note:** One of the radios is the "current" radio that will be affected by the ```get_radio_nets```, ```set_radio_net```, ```set_rx_enable```, and ```set_tx_enable``` commands. Use ```set_radio``` to change the current radio.
 * Hit Enter key to repeat the last command. This is useful for repeating the ```status``` command, for example.
 * Enter ```quit``` to exit the application.

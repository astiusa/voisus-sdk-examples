#include "stdafx.h"
VoisusPlugin vapi;
int _tmain(int argc, _TCHAR* argv[])
{
  // First we have some initialization to do
  if (!initialize_VRCC()) {
    std::cout << "Unable to load VRCC DLL.  Is the Voisus Client installed?" << std::endl;
    return 1;
  }

  // You can use Log_Write to write to the Voisus Client log-file.
  // The first parameter can be an application or function name
  // to make your log more readable.
  vapi.Log_Write("voisus-sdk-example", "VRCC DLL has been loaded");

  /*// You can get the current path of the log file like this:
  const char* logPath = vapi.Voisus_LogPath();
  // Not available in 5.6.2
  std::cout << "Log path: ";
  std::cout << logPath;
  std::cout << "\n\n";
  */

  std::cout << "VRCC DLL has been loaded" << std::endl;

  // Next we'll connect to a server
  if(!connectToServer()) {
    std::cout << "Unable to connect to server" << std::endl;
    return 1;
  }

  // Once we are connected, we need to select a Communication Role
  // for this client to use
  std::cout << "Connected to server.  Requesting Roles" << std::endl;
  selectRole();
  
  // Ok, now that we're connected to a Role, we can take
  // a look at our communication assets
  printRadios();

  std::cout << "Press any key to continue..." << std::endl;;
  char* input = new char(5);
  std::cin >> input;
  vapi.VRCC_Shutdown();
  
  return 0;
}

bool initialize_VRCC() {
 
  if (vapi.LoadDLL()) {
    vapi.VRCC_Start();
    return true;
  }
  else {
    return false;
  }
}

bool connectToServer() {
  char* ip = new char(50);
  std::cout << "Which Voisus Server IP would you like to connect to?..." << std::endl;
  std::cin >> ip;
  vapi.Voisus_ConnectServer(ip);
  for (int i=0; i<10; i++) {
    vapi.VRCC_Update(); // this should really be called from a main event loop
    if(vapi.Network_ConnectionStatus() == STATUS_CONNECTED)
      return true;
    Sleep(1000);
  }
  return false;
}

bool selectRole() {
  vapi.VRCC_Update(); // this should really be called from a main event loop
  int roleCount = vapi.Role_ListCount();
  if (roleCount == 0) {
    std::cout << "Current running scenario doesn't have any roles defined." << std::endl;;
    return false;
  }
  std::cout << "Index \t\tRole_Name \t\tRole_Id" << std::endl;
  for (int i = 0; i < roleCount; i++) {
    std::cout << i;
    std::cout << "\t\t";
    char result[100];
    strcpy(result, vapi.Role_Name(i));
    strcat(result, "\t\t");
    strcat(result, vapi.Role_Id(i));
    std::cout << result << std::endl;
  }
  int roleIndex=-1;
  char* userSelection = new char(2);
  std::cout << "Type the Index of the role to connect to:" << std::endl;
  std::cin >> userSelection;
  roleIndex = atoi(userSelection);
  const char* roleId = vapi.Role_Id(roleIndex);
  const char* roleName = vapi.Role_Name(roleIndex);
  std::cout << "Attempting to connect to role: " << roleName << std::endl;
  vapi.Role_SetRole(roleId);


  // Wait for role selection to take effect
  // Afterwards, we can start polling for radio information
  for (int i = 0; i < 10; i++) {
    vapi.VRCC_Update(); // this should really be called from a main event loop
    if(vapi.Network_ConnectState() == ROLE_CONNECTED) {
      std::cout << "Successfully connected to role: " << roleName << std::endl;
      return true;
    }
    Sleep(1000);
  }
  std::cout << "Unable to connect to the role in 10 seconds" << std::endl;
  return false;
}

void printRadios() {
  vapi.VRCC_Update(); // this should really be called from a main event loop
  //system("cls");
  std::cout << "\n\n\n";
  std::cout << "Current Radio Status:" << std::endl;

  // Get the total number of radios
  int numRadios = vapi.Radio_ListCount();
  std::cout << "Radio\tNet\t\tTxEn\tRxEn\tTx\tRx" << std::endl;

  // For each radio, get the current net name and the radio status
  for (int i = 0; i < numRadios; i++) {
    const char* netName = vapi.Radio_NetName(i);
    int txEn = vapi.Radio_IsTransmitEnabled(i);
    int rxEn = vapi.Radio_IsReceiveEnabled(i);
    int tx = vapi.Radio_IsTransmitting(i);
    int rx = vapi.Radio_IsReceiving(i);
    std::cout << i << "\t" << netName << "\t\t";
    std::cout << std::noboolalpha << txEn << "\t" << std::noboolalpha << rxEn <<  "\t";
    std::cout << std::noboolalpha << tx << "\t" << std::noboolalpha << rx <<  std::endl;
  }
}
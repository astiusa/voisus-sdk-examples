#ifndef VOISUS
#define VOISUS
#include <windows.h>
#include <stdio.h>
enum MicMode_t
{
	MIC_OFF = 0,               // microphone is disabled
	MIC_PTT = 1,              // microphone is controlled by the PTT button
	MIC_VOX = 2,              // microphone is controlled by voice level
	MIC_HOT = 3,              // microphone is "hot" - meaning on
}; 

// client connection status
enum ConnectionStatus_t
{
	STATUS_NONE         = 0,  // client has not connected to a target
	STATUS_DISCONNECTED = 1,  // client has disconnected from a target
	STATUS_CONNECTED    = 2   // client is currently connected to a target
};

enum ConnectionState_t
{
  TARGET_CONNECT     = 0,
  ROLE_GET           = 1,
  ROLES_RECEIVED     = 2,
  ROLE_SET           = 3,
  ROLE_CONNECT       = 4,
  ROLE_CONNECTED     = 5,
  TARGET_AUTHORIZE   = 6
};

// test modes
enum TestMode_t
{
	TEST_OFF = 0,             // normal operating mode
	TEST_WAVE = 1,            // play test tone through headset
	TEST_SIDETONE = 2         // test headset sidetone
}; 

enum Error_t
{
	ERROR_OFF = 0,          // No error
	ERROR_CREDITS = 1,		// Credit System Error
	ERROR_VOISUS = 2        // Voisus Server Error, check log
};

class VoisusPlugin
{
public:

	VoisusPlugin();
	~VoisusPlugin();
	void Log_Write(const char* function, const char* message);
  const char* Voisus_LogPath();

	int Voisus_ConnectServer(char*);
	void Voisus_Disconnect();
	void Voisus_Save();
  void VRCC_Update();
	Error_t Voisus_Error();

	int TargetConnection_Status(int listnum);

	int Radio_IsTransmitting(int radio_index);
	int Radio_IsReceiving(int tradio_index);
	int Radio_IsNetLocked(int radio_index);
	int Radio_IsRXModeLocked(int radio_index);

	const char* Radio_NetName(int radio_index);
	void Radio_SetNet(int radio_index,int net_index);
	int Radio_ListCount();
	int Radio_IsTransmitEnabled(int radio_index);
	void Radio_SetTransmitEnabled(int radio_idx, int value);
	void Radio_SetReceiveEnabled(int radio_idx, int value);
	int Radio_IsReceiveEnabled(int radio_index);
	int Radio_IsShared(int radio_index);
	const char* Radio_NetID(int radio_index,int net_index);
	int Radio_NetListCount(int fillId);
	const char* Radio_NetIDActive(int radio_index);
  void Radio_SetNetRxFrequency(int radio_index, const char *net_id, unsigned long long freq);
  void Radio_SetNetTxFrequency(int radio_index, const char *net_id, unsigned long long freq);
  unsigned long long Radio_NetRxFrequencyActive(int radio_index);
  unsigned long long Radio_NetTxFrequencyActive(int radio_index);

	const char* Network_ClientName();
  void Network_SetClientName(const char* clientName);
	const char* Network_TargetIP();
	int Network_TargetPort();
	int Network_ConnectionStatus();
	int Network_ConnectState();

	int Role_ListCount();
	const char* Role_Name(int list_index);
	const char* Role_Id(int list_index);
	void Role_SetRole(const char* role_id);
	const char* Role_Current_Name();
	const char* Role_Current_Id();
	int Role_Version();

	int Shared_Role_ListCount();
	const char* Shared_Role_Name(int list_index);
	const char* Shared_Role_Id(int list_index);
	void Shared_Role_SetRole(const char* role_id);
	const char* Shared_Role_Current_Name();
	const char* Shared_Role_Current_Id();


	float Headset_VoxThreshold();
	void Headset_SetMicrophoneMode(MicMode_t mode);
	MicMode_t Headset_MicrophoneMode();
	void Headset_SetVoxThreshold(float volume);
	
	float Radio_Volume(int radio_index);
	void Radio_SetVolume(int radio_index, float volume);
	float Headset_EarphoneVolume();
	void Headset_SetEarphoneVolume(float volume);
	
	void WorldPosition_Set(float xcoord, float ycoord,float zcoord);
	void PTT_SetPressed(int value);

	void Earshot_Enable(int enabled);
	void Earshot_PTTPressed(int enabled);
	int Earshot_Receiving();
	int Earshot_Transmitting();

	void VRCC_Start(int argc, char* argv[]);
  void VRCC_Shutdown();

	const char* Voisus_ClientBuildVersion();

	HWND getHWND();
	int LoadDLL();
	int UnloadDLL();

};
#endif

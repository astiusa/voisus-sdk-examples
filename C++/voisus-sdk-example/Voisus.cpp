
#include "stdafx.h"
HWND voisushwnd;
HINSTANCE hInstLibrary;
bool voisusOn;

/**
* Voisus API Calls
* Function Pointer Definitions followed by declarations
**/

typedef int (*_Voisus_Connect_fn)(const char* target_ip);
_Voisus_Connect_fn Voisus_ConnectServer_fn;

typedef void (*_Voisus_Disconnect_fn)();
_Voisus_Disconnect_fn Voisus_Disconnect_fn;
typedef int (*_Voisus_ConfigurationId_fn)();
_Voisus_ConfigurationId_fn Voisus_ConfigurationId_fn;
typedef Error_t (*_Voisus_Error_fn)();
_Voisus_Error_fn Voisus_Error_fn;
typedef void (*_Voisus_Save_fn)();
_Voisus_Save_fn Voisus_Save_fn;

typedef void (*_VRCC_Update_fn)();
_VRCC_Update_fn VRCC_Update_fn;

typedef int (*_Radio_NetListCount_fn)(int radio_index);
_Radio_NetListCount_fn Radio_NetListCount_fn;

// Headset Functions
typedef float (*_Headset_EarphoneVolume_fn)();
_Headset_EarphoneVolume_fn Headset_EarphoneVolume_fn;
typedef void (*_Headset_SetEarphoneVolume_fn)(float volume);
_Headset_SetEarphoneVolume_fn Headset_SetEarphoneVolume_fn;

typedef float (*_Radio_Volume_fn)(int radio_index);
_Radio_Volume_fn Radio_Volume_fn;
typedef void (*_Radio_SetVolume_fn)(int radio_index, float volume);
_Radio_SetVolume_fn Radio_SetVolume_fn;

typedef float (*_Headset_VoxThreshold_fn)();
_Headset_VoxThreshold_fn Headset_VoxThreshold_fn;
typedef void (*_Headset_SetVoxThreshold_fn)(float volume);
_Headset_SetVoxThreshold_fn Headset_SetVoxThreshold_fn;
typedef void (*_Headset_SetMicrophoneMode_fn)(MicMode_t mode);
_Headset_SetMicrophoneMode_fn Headset_SetMicrophoneMode_fn;
typedef MicMode_t (*_Headset_MicrophoneMode_fn)();
_Headset_MicrophoneMode_fn Headset_MicrophoneMode_fn;

// PTT Functions
typedef void (*_PTT_SetPressed_fn)(int value);
_PTT_SetPressed_fn PTT_SetPressed_fn;

// Radio Functions
typedef char* (*_Radio_NetName_fn)(int radio_index);
_Radio_NetName_fn Radio_NetName_fn;
typedef void (*_Radio_SetNet_fn)(int radio_index, int net_index);
_Radio_SetNet_fn Radio_SetNet_fn;
typedef int (*_Radio_IsNetLocked_fn)(int radio_index);
_Radio_IsNetLocked_fn Radio_IsNetLocked_fn;
typedef int (*_Radio_IsRXModeLocked_fn)(int radio_index);
_Radio_IsRXModeLocked_fn Radio_IsRXModeLocked_fn;
typedef int (*_Radio_IsTransmitting_fn)(int radio_index);
_Radio_IsTransmitting_fn Radio_IsTransmitting_fn;
typedef int (*_Radio_IsReceiving_fn)(int radio_index);
_Radio_IsReceiving_fn Radio_IsReceiving_fn;
typedef int (*_Radio_ListCount_fn)();
_Radio_ListCount_fn Radio_ListCount_fn;
typedef int (*_Radio_IsTransmitEnabled_fn)(int radio_index);
_Radio_IsTransmitEnabled_fn Radio_IsTransmitEnabled_fn;
typedef void (*_Radio_SetTransmitEnabled_fn)(int radio_index, int value);
_Radio_SetTransmitEnabled_fn Radio_SetTransmitEnabled_fn;
typedef void (*_Radio_SetReceiveEnabled_fn)(int radio_index, int value);
_Radio_SetReceiveEnabled_fn Radio_SetReceiveEnabled_fn;
typedef int (*_Radio_IsReceiveEnabled_fn)(int radio_index);
_Radio_IsReceiveEnabled_fn Radio_IsReceiveEnabled_fn;
typedef int (*_Radio_Is_Shared_fn)(int radio_index);
_Radio_Is_Shared_fn Radio_Is_Shared_fn;
typedef const char* (*_Radio_NetID_fn)(int radio_index, int net_index);
_Radio_NetID_fn Radio_NetID_fn;
typedef const char* (*_Radio_NetIDActive_fn)(int radio_index);
_Radio_NetIDActive_fn Radio_NetIDActive_fn;
typedef void (*_Radio_SetNetRxFrequency_fn)(int radio_index, const char *net_id, unsigned long long freq);
_Radio_SetNetRxFrequency_fn Radio_SetNetRxFrequency_fn;
typedef void (*_Radio_SetNetTxFrequency_fn)(int radio_index, const char *net_id, unsigned long long freq);
_Radio_SetNetTxFrequency_fn Radio_SetNetTxFrequency_fn;
typedef unsigned long long (*_Radio_NetRxFrequencyActive_fn)(int radio_index);
_Radio_NetRxFrequencyActive_fn Radio_NetRxFrequencyActive_fn;
typedef unsigned long long (*_Radio_NetTxFrequencyActive_fn)(int radio_index);
_Radio_NetTxFrequencyActive_fn Radio_NetTxFrequencyActive_fn;

// Role Functions
typedef int (*_Role_ListCount_fn)();
_Role_ListCount_fn Role_ListCount_fn;
typedef const char* (*_Role_Name_fn)(int list_index);
_Role_Name_fn Role_Name_fn;
typedef const char* (*_Role_Id_fn)(int list_index);
_Role_Id_fn Role_Id_fn;
typedef const char* (*_Role_Current_Name_fn)();
_Role_Current_Name_fn Role_Current_Name_fn;
typedef const char* (*_Role_Current_Id_fn)();
_Role_Current_Id_fn Role_Current_Id_fn;
typedef void (*_Role_SetRole_fn)(const char* role_id);
_Role_SetRole_fn Role_SetRole_fn;
typedef int (*_Role_Version_fn)();
_Role_Version_fn Role_Version_fn;

// Shared Role Functions
typedef int (*_Shared_Role_ListCount_fn)();
_Shared_Role_ListCount_fn Shared_Role_ListCount_fn;
typedef const char* (*_Shared_Role_Name_fn)(int list_index);
_Shared_Role_Name_fn Shared_Role_Name_fn;
typedef const char* (*_Shared_Role_Id_fn)(int list_index);
_Shared_Role_Id_fn Shared_Role_Id_fn;
typedef const char* (*_Shared_Role_Current_Name_fn)();
_Shared_Role_Current_Name_fn Shared_Role_Current_Name_fn;
typedef const char* (*_Shared_Role_Current_Id_fn)();
_Shared_Role_Current_Id_fn Shared_Role_Current_Id_fn;
typedef void (*_Shared_Role_SetRole_fn)(const char* role_id);
_Shared_Role_SetRole_fn Shared_Role_SetRole_fn;

//World Position Functions
typedef void (*_WorldPosition_Set_fn)(float xcoord, float ycoord, float zcoord);
_WorldPosition_Set_fn WorldPosition_Set_fn;

// Network Functions
typedef char* (*_Network_TargetIP_fn)();
_Network_TargetIP_fn Network_TargetIP_fn;
typedef int (*_Network_TargetPort_fn)();
_Network_TargetPort_fn Network_TargetPort_fn;
typedef const char* (*_Network_SetClientName_fn)(const char* clientName);
_Network_SetClientName_fn Network_SetClientName_fn;
typedef const char* (*_Network_ClientName_fn)();
_Network_ClientName_fn Network_ClientName_fn;

typedef void (*_Earshot_Enable_fn)(int enabled);
_Earshot_Enable_fn Earshot_Enable_fn;
typedef void (*_Earshot_PTTPressed_fn)(int enabled);
_Earshot_PTTPressed_fn Earshot_PTTPressed_fn;
typedef int (*_Earshot_Receiving_fn)();
_Earshot_Receiving_fn Earshot_Receiving_fn;
typedef int (*_Earshot_Transmitting_fn)();
_Earshot_Transmitting_fn Earshot_Transmitting_fn;

typedef int (*_Network_ConnectionStatus_fn)();
_Network_ConnectionStatus_fn Network_ConnectionStatus_fn;
typedef int (*_Network_ConnectState_fn)();
_Network_ConnectState_fn Network_ConnectState_fn;

typedef const char*(*_Voisus_ClientBuildVersion_fn)();
_Voisus_ClientBuildVersion_fn Voisus_ClientBuildVersion_fn;

typedef void (*_Log_Write_fn)(const char* function, const char* message);
_Log_Write_fn Log_Write_fn;

typedef const char* (*_Voisus_LogPath_fn)();
_Voisus_LogPath_fn Voisus_LogPath_fn;


typedef int (*_VRCC_Start_fn)(int argc, char* argv[]);
_VRCC_Start_fn VRCC_Start_fn;
typedef void (*_VRCC_Shutdown_fn)();
_VRCC_Shutdown_fn VRCC_Shutdown_fn;

/**
*  Functions that make Voisus API Calls
**/

VoisusPlugin::VoisusPlugin()
{

}

VoisusPlugin::~VoisusPlugin()
{

}

void VoisusPlugin::VRCC_Start(int argc, char* argv[])
{
	if (VRCC_Start_fn)
		VRCC_Start_fn(argc, argv);
}

void VoisusPlugin::VRCC_Shutdown()
{
  if (VRCC_Shutdown_fn)
    VRCC_Shutdown_fn();
}

void VoisusPlugin::Log_Write(const char* function, const char* message)
{
	if (Log_Write_fn)
		Log_Write_fn(function, message);
}

const char* VoisusPlugin::Voisus_LogPath()
{
	if (Voisus_LogPath_fn)
		return Voisus_LogPath_fn();
  else
    return "No Log Path";
}


int VoisusPlugin::Voisus_ConnectServer(char* targetIP)
{
	if (Voisus_ConnectServer_fn)
		return Voisus_ConnectServer_fn(targetIP);
	return -1;
}

void VoisusPlugin::Voisus_Disconnect()
{
	if (Voisus_Disconnect_fn)
		Voisus_Disconnect_fn();
}

Error_t VoisusPlugin::Voisus_Error()
{
	if (Voisus_Error_fn)
		return Voisus_Error_fn();
	else return ERROR_OFF;
}

void VoisusPlugin::Voisus_Save()
{
	if (Voisus_Save_fn)
		Voisus_Save_fn();
}

void VoisusPlugin::VRCC_Update()
{
	if (VRCC_Update_fn)
		VRCC_Update_fn();
}

void VoisusPlugin::PTT_SetPressed (int ptt)
{
	if (PTT_SetPressed_fn)
		PTT_SetPressed_fn(ptt);
}

int VoisusPlugin::Network_ConnectionStatus()
{
	if (Network_ConnectionStatus_fn)
		return Network_ConnectionStatus_fn();
	return -1;
}

int VoisusPlugin::Network_ConnectState()
{
	if (Network_ConnectState_fn)
		return Network_ConnectState_fn();
	return -1;
}

const char* VoisusPlugin::Network_TargetIP()
{
	if (Network_TargetIP_fn)
		return Network_TargetIP_fn();
	else return NULL;
}

int VoisusPlugin::Network_TargetPort()
{
	if (Network_TargetPort_fn)
		return Network_TargetPort_fn();
	else return 0;
}

const char* VoisusPlugin::Network_ClientName() {
  if (Network_ClientName_fn)
    return Network_ClientName_fn();
  else return "hello";
}

void VoisusPlugin::Network_SetClientName(const char* clientName) {
  if (Network_SetClientName_fn) 
    Network_SetClientName_fn(clientName);
}


// Role functions
int VoisusPlugin::Role_ListCount()
{
	if (Role_ListCount_fn)
		return Role_ListCount_fn();
	return 0;
}

const char* VoisusPlugin::Role_Name(int list_index)
{
	if (Role_Name_fn)
		return Role_Name_fn(list_index);
	return NULL;
}

const char* VoisusPlugin::Role_Id(int list_index)
{
	if (Role_Id_fn)
		return Role_Id_fn(list_index);
	return NULL;
}

const char* VoisusPlugin::Role_Current_Name()
{
	if (Role_Current_Name_fn)
		return Role_Current_Name_fn();
	return NULL;
}

const char* VoisusPlugin::Role_Current_Id()
{
	if (Role_Current_Id_fn)
		return Role_Current_Id_fn();

	return "NULL";
}

void VoisusPlugin::Role_SetRole(const char* role_id)
{
	if (Role_SetRole_fn)
		Role_SetRole_fn(role_id);
}

int VoisusPlugin::Role_Version()
{
	if (Role_Version_fn)
		return Role_Version_fn();
	return 0;
}

// Shared Role Functions
int VoisusPlugin::Shared_Role_ListCount()
{
	if (Shared_Role_ListCount_fn)
		return Shared_Role_ListCount_fn();
	return 0;
}

const char* VoisusPlugin::Shared_Role_Name(int list_index)
{
	if (Shared_Role_Name_fn)
		return Shared_Role_Name_fn(list_index);
	return NULL;
}

const char* VoisusPlugin::Shared_Role_Id(int list_index)
{
	if (Shared_Role_Id_fn)
		return Shared_Role_Id_fn(list_index);
	return NULL;
}

const char* VoisusPlugin::Shared_Role_Current_Name()
{
	if (Shared_Role_Current_Name_fn)
		return Shared_Role_Current_Name_fn();
	return NULL;
}

const char* VoisusPlugin::Shared_Role_Current_Id()
{
	if (Shared_Role_Current_Id_fn)
		return Shared_Role_Current_Id_fn();
	return NULL;
}

void VoisusPlugin::Shared_Role_SetRole(const char* role_id)
{
	if (Shared_Role_SetRole_fn)
		Shared_Role_SetRole_fn(role_id);
}


MicMode_t VoisusPlugin::Headset_MicrophoneMode()
{
	if (Headset_MicrophoneMode_fn)
		return Headset_MicrophoneMode_fn();
	else return MIC_OFF;
}

void VoisusPlugin::Headset_SetEarphoneVolume(float volume)
{
	if (Headset_SetEarphoneVolume_fn)
		Headset_SetEarphoneVolume_fn(volume);
}

float VoisusPlugin::Headset_EarphoneVolume()
{
	if (Headset_EarphoneVolume_fn)
		return Headset_EarphoneVolume_fn();
	return 0;
}

float VoisusPlugin::Radio_Volume(int radio_index)
{
	if (Radio_Volume_fn)
		return Radio_Volume_fn(radio_index);
	return 0;
}

void VoisusPlugin::Radio_SetVolume(int radio_index, float volume)
{
	if (Radio_SetVolume_fn)
		Radio_SetVolume_fn(radio_index, volume);
}


float VoisusPlugin::Headset_VoxThreshold()
{
	if (Headset_VoxThreshold_fn)
		return Headset_VoxThreshold_fn();
	return -1;
}

void VoisusPlugin::Headset_SetVoxThreshold(float volume)
{
	if (Headset_SetVoxThreshold_fn)
		Headset_SetVoxThreshold_fn(volume);
}

void VoisusPlugin::Headset_SetMicrophoneMode(MicMode_t mode)
{
	if (Headset_SetMicrophoneMode_fn)
		Headset_SetMicrophoneMode_fn(mode);
}

int VoisusPlugin::Radio_NetListCount(int radio_index)
{
	if (Radio_NetListCount_fn)
		return Radio_NetListCount_fn(radio_index);
	else return -1;
}

int VoisusPlugin::Radio_IsNetLocked(int radio_index)
{
	if(Radio_IsNetLocked_fn)
		return Radio_IsNetLocked_fn(radio_index);
	else return 1;
}

int VoisusPlugin::Radio_IsRXModeLocked(int radio_index)
{
	if (Radio_IsRXModeLocked_fn)
		return Radio_IsRXModeLocked_fn(radio_index);
	else return 1;
}

int VoisusPlugin::Radio_IsTransmitting(int radio_index)
{
	if (Radio_IsTransmitting_fn)
		return Radio_IsTransmitting_fn(radio_index);
	else
		return 0;
}

int VoisusPlugin::Radio_IsReceiving(int radio_index)
{
	if (Radio_IsReceiving_fn)
		return Radio_IsReceiving_fn(radio_index);
	else
		return 0;
}

const char* VoisusPlugin::Radio_NetID(int radio_index, int net_index)
{
	if (Radio_NetID_fn!=NULL)
	{
		return Radio_NetID_fn(radio_index, net_index);
	}
	else return NULL;
}

const char* VoisusPlugin::Radio_NetIDActive(int radio_index)
{
	if (Radio_NetIDActive_fn!=NULL)
	{
		return Radio_NetIDActive_fn(radio_index);
	}
	else return NULL;
}

const char* VoisusPlugin::Radio_NetName(int radio_index)
{
	if (Radio_NetName_fn!=NULL)
	{
		return Radio_NetName_fn(radio_index);
	}
	else return NULL;
}

void VoisusPlugin::Radio_SetNet(int radio_index, int net_index)
{
	if(Radio_SetNet_fn)
		Radio_SetNet_fn(radio_index,net_index);
}

int VoisusPlugin::Radio_ListCount()
{
	if (Radio_ListCount_fn)
		return Radio_ListCount_fn();
	else return -1;
}

int VoisusPlugin::Radio_IsTransmitEnabled(int radio_idx)
{
	if (Radio_IsTransmitEnabled_fn)
		return Radio_IsTransmitEnabled_fn(radio_idx);
	else return 0;
}

int VoisusPlugin::Radio_IsReceiveEnabled(int radio_idx)
{
	if (Radio_IsReceiveEnabled_fn)
		return Radio_IsReceiveEnabled_fn(radio_idx);
	else return 0;
}

void VoisusPlugin::Radio_SetTransmitEnabled(int radio_idx, int value)
{
	if (Radio_SetTransmitEnabled_fn)
		Radio_SetTransmitEnabled_fn(radio_idx, value);
}

void VoisusPlugin::Radio_SetReceiveEnabled(int radio_idx, int value)
{
	if (Radio_SetReceiveEnabled_fn)
		Radio_SetReceiveEnabled_fn(radio_idx, value);
}

int VoisusPlugin::Radio_IsShared(int radio_idx)
{
	if (Radio_Is_Shared_fn)
		return Radio_Is_Shared_fn(radio_idx);
	return 0;
}

void VoisusPlugin::Radio_SetNetRxFrequency(int radio_idx, const char* net_id, unsigned long long freq)
{
	if (Radio_SetNetRxFrequency_fn)
		Radio_SetNetRxFrequency_fn(radio_idx, net_id, freq);
}

void VoisusPlugin::Radio_SetNetTxFrequency(int radio_idx, const char* net_id, unsigned long long freq)
{
	if (Radio_SetNetTxFrequency_fn)
		Radio_SetNetTxFrequency_fn(radio_idx, net_id, freq);
}

unsigned long long VoisusPlugin::Radio_NetRxFrequencyActive(int radio_index)
{
  if (Radio_NetRxFrequencyActive_fn) {
    return Radio_NetRxFrequencyActive_fn(radio_index);
  }
  return 0;
}

unsigned long long VoisusPlugin::Radio_NetTxFrequencyActive(int radio_index)
{
  if (Radio_NetTxFrequencyActive_fn) {
    return Radio_NetTxFrequencyActive_fn(radio_index);
  }
  return 0;
}

void VoisusPlugin::Earshot_Enable(int enabled)
{
	if (Earshot_Enable_fn)
		Earshot_Enable_fn(enabled);
}
void VoisusPlugin::Earshot_PTTPressed(int enabled)
{
	if (Earshot_PTTPressed_fn)
		Earshot_PTTPressed_fn(enabled);
}
int VoisusPlugin::Earshot_Receiving()
{
	if (Earshot_Receiving_fn)
		return Earshot_Receiving_fn();
	return -1;
}
int VoisusPlugin::Earshot_Transmitting()
{
	if (Earshot_Transmitting_fn)
		return Earshot_Transmitting_fn();
	return -1;
}


int VoisusPlugin::UnloadDLL()
{
	return 0;
}

void VoisusPlugin::WorldPosition_Set(float xcoord, float ycoord,float zcoord)
{

	if (WorldPosition_Set_fn){
		WorldPosition_Set_fn(xcoord, ycoord, zcoord);
		//Used to debug world position. Set to true to get a print out of positions in the voisus log.
		if(false){
			char pos[80];
			sprintf(pos,"%f",xcoord);
			Log_Write("xcoord",pos);
			sprintf(pos,"%f",ycoord);
			Log_Write("ycoord",pos);
			sprintf(pos,"%f",zcoord);
			Log_Write("zcoord",pos);
		}
	}
}

const char* VoisusPlugin::Voisus_ClientBuildVersion()
{
	if(Voisus_ClientBuildVersion_fn)
		return Voisus_ClientBuildVersion_fn();
	return "";
}

int VoisusPlugin::LoadDLL()
{
	HKEY hkey;
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\ASTi\\VoisusClient",0,KEY_QUERY_VALUE,&hkey))
	{
		char path[100];
		DWORD szPath = sizeof(path);
		if (ERROR_SUCCESS == RegQueryValueEx(hkey,"InstallDir",NULL,NULL,(LPBYTE)path,&szPath))
		{
			strcat(path,"\\VRCClient.dll");
			hInstLibrary = LoadLibrary(path);
		}
		RegCloseKey(hkey);
	}

	if (hInstLibrary)
	{
		//Network functions
		Voisus_Disconnect_fn = (_Voisus_Disconnect_fn)GetProcAddress(hInstLibrary, "Voisus_Disconnect");
		Voisus_ConnectServer_fn = (_Voisus_Connect_fn)GetProcAddress(hInstLibrary,"Voisus_ConnectServer");
		Voisus_Error_fn = (_Voisus_Error_fn)GetProcAddress(hInstLibrary,"Voisus_Error");
		Voisus_Save_fn = (_Voisus_Save_fn)GetProcAddress(hInstLibrary,"Voisus_Save");
    VRCC_Update_fn = (_VRCC_Update_fn)GetProcAddress(hInstLibrary,"VRCC_Update");
		Voisus_ClientBuildVersion_fn = (_Voisus_ClientBuildVersion_fn)GetProcAddress(hInstLibrary,"Voisus_ClientBuildVersion");

		Network_TargetIP_fn = (_Network_TargetIP_fn)GetProcAddress(hInstLibrary,"Network_TargetIP");
		Network_TargetPort_fn = (_Network_TargetPort_fn)GetProcAddress(hInstLibrary,"Network_TargetPort");
		Network_ConnectionStatus_fn = (_Network_ConnectionStatus_fn)GetProcAddress(hInstLibrary,"Network_ConnectionStatus");
		Network_ConnectState_fn	= (_Network_ConnectState_fn)GetProcAddress(hInstLibrary,"Network_ConnectState");
    Network_ClientName_fn	= (_Network_ClientName_fn)GetProcAddress(hInstLibrary,"Network_ClientName");
    Network_SetClientName_fn	= (_Network_SetClientName_fn)GetProcAddress(hInstLibrary,"Network_SetClientName");

		Role_ListCount_fn = (_Role_ListCount_fn)GetProcAddress(hInstLibrary, "Role_ListCount");
		Role_Name_fn = (_Role_Name_fn)GetProcAddress(hInstLibrary, "Role_Name");
		Role_Id_fn = (_Role_Id_fn)GetProcAddress(hInstLibrary, "Role_Id");
		Role_Current_Name_fn = (_Role_Current_Name_fn)GetProcAddress(hInstLibrary, "Role_NameActive");
		Role_Current_Id_fn = (_Role_Current_Id_fn)GetProcAddress(hInstLibrary, "Role_IdActive");
		Role_SetRole_fn = (_Role_SetRole_fn)GetProcAddress(hInstLibrary, "Role_SetRole");
		Role_Version_fn = (_Role_Version_fn)GetProcAddress(hInstLibrary, "Role_Version");

		Shared_Role_ListCount_fn = (_Shared_Role_ListCount_fn)GetProcAddress(hInstLibrary, "EntityState_ListCount");
		Shared_Role_Name_fn = (_Shared_Role_Name_fn)GetProcAddress(hInstLibrary, "EntityState_Name");
		Shared_Role_Id_fn = (_Shared_Role_Id_fn)GetProcAddress(hInstLibrary, "EntityState_Id");
		Shared_Role_Current_Name_fn = (_Shared_Role_Current_Name_fn)GetProcAddress(hInstLibrary, "EntityState_NameActive");
		Shared_Role_Current_Id_fn = (_Shared_Role_Current_Id_fn)GetProcAddress(hInstLibrary, "EntityState_IdActive");
		Shared_Role_SetRole_fn = (_Shared_Role_SetRole_fn)GetProcAddress(hInstLibrary, "EntityState_SetEntityState");

		Radio_NetName_fn = (_Radio_NetName_fn)GetProcAddress(hInstLibrary,"Radio_NetNameActive");
		Radio_IsNetLocked_fn = (_Radio_IsNetLocked_fn)GetProcAddress(hInstLibrary,"Radio_IsNetLocked");
		Radio_IsRXModeLocked_fn = (_Radio_IsRXModeLocked_fn)GetProcAddress(hInstLibrary,"Radio_IsRXModeLocked");
		Radio_SetNet_fn = (_Radio_SetNet_fn)GetProcAddress(hInstLibrary,"Radio_SetNet");
		Radio_ListCount_fn = (_Radio_ListCount_fn)GetProcAddress(hInstLibrary,"Radio_ListCount");
		Radio_IsTransmitting_fn = (_Radio_IsTransmitting_fn)GetProcAddress(hInstLibrary,"Radio_IsTransmitting");
		Radio_IsReceiving_fn = (_Radio_IsReceiving_fn)GetProcAddress(hInstLibrary,"Radio_IsReceiving");
		Radio_IsTransmitEnabled_fn = (_Radio_IsTransmitEnabled_fn)GetProcAddress(hInstLibrary,"Radio_IsTransmitEnabled");
		Radio_SetTransmitEnabled_fn = (_Radio_SetTransmitEnabled_fn)GetProcAddress(hInstLibrary,"Radio_SetTransmitEnabled");
		Radio_SetReceiveEnabled_fn = (_Radio_SetReceiveEnabled_fn)GetProcAddress(hInstLibrary,"Radio_SetReceiveEnabled");
		Radio_IsReceiveEnabled_fn = (_Radio_IsReceiveEnabled_fn)GetProcAddress(hInstLibrary,"Radio_IsReceiveEnabled");
		Radio_Is_Shared_fn = (_Radio_Is_Shared_fn)GetProcAddress(hInstLibrary, "Radio_IsShared");
		Radio_NetListCount_fn = (_Radio_NetListCount_fn)GetProcAddress(hInstLibrary,"Radio_NetListCount");
		Radio_NetID_fn = (_Radio_NetID_fn)GetProcAddress(hInstLibrary,"Radio_NetID");
		Radio_NetIDActive_fn = (_Radio_NetIDActive_fn)GetProcAddress(hInstLibrary,"Radio_NetIDActive");
    Radio_SetNetRxFrequency_fn = (_Radio_SetNetRxFrequency_fn)GetProcAddress(hInstLibrary,"Radio_SetNetRxFrequency");
    Radio_SetNetTxFrequency_fn = (_Radio_SetNetTxFrequency_fn)GetProcAddress(hInstLibrary,"Radio_SetNetTxFrequency");
    Radio_NetRxFrequencyActive_fn = (_Radio_NetRxFrequencyActive_fn)GetProcAddress(hInstLibrary,"Radio_NetRxFrequencyActive");
    Radio_NetTxFrequencyActive_fn = (_Radio_NetTxFrequencyActive_fn)GetProcAddress(hInstLibrary,"Radio_NetTxFrequencyActive");

		Headset_SetMicrophoneMode_fn = (_Headset_SetMicrophoneMode_fn)GetProcAddress(hInstLibrary,"Headset_SetMicrophoneMode");
		Headset_MicrophoneMode_fn = (_Headset_MicrophoneMode_fn)GetProcAddress(hInstLibrary,"Headset_MicrophoneMode");
		Headset_VoxThreshold_fn = (_Headset_VoxThreshold_fn)GetProcAddress(hInstLibrary,"Headset_VoxThreshold");
		Headset_SetVoxThreshold_fn = (_Headset_SetVoxThreshold_fn)GetProcAddress(hInstLibrary,"Headset_SetVoxThreshold");

		Radio_Volume_fn = (_Radio_Volume_fn)GetProcAddress(hInstLibrary,"Radio_Volume");
		Radio_SetVolume_fn = (_Radio_SetVolume_fn)GetProcAddress(hInstLibrary,"Radio_SetVolume");
		Headset_EarphoneVolume_fn = (_Headset_EarphoneVolume_fn)GetProcAddress(hInstLibrary,"Headset_EarphoneVolume");
		Headset_SetEarphoneVolume_fn = (_Headset_SetEarphoneVolume_fn)GetProcAddress(hInstLibrary,"Headset_SetEarphoneVolume");

		Earshot_Enable_fn = (_Earshot_Enable_fn)GetProcAddress(hInstLibrary,"Earshot_Enable");
		Earshot_PTTPressed_fn = (_Earshot_PTTPressed_fn)GetProcAddress(hInstLibrary,"Earshot_SetPTT");
		Earshot_Receiving_fn = (_Earshot_Receiving_fn)GetProcAddress(hInstLibrary,"Earshot_Receiving");
		Earshot_Transmitting_fn = (_Earshot_Transmitting_fn)GetProcAddress(hInstLibrary,"Earshot_Transmitting");

		WorldPosition_Set_fn = (_WorldPosition_Set_fn)GetProcAddress(hInstLibrary,"WorldPosition_Set");

		PTT_SetPressed_fn = (_PTT_SetPressed_fn)GetProcAddress(hInstLibrary,"PTT_SetPressed");

		Log_Write_fn = (_Log_Write_fn)GetProcAddress(hInstLibrary,"Log_Write");
    Voisus_LogPath_fn = (_Voisus_LogPath_fn)GetProcAddress(hInstLibrary,"Voisus_LogPath");

		VRCC_Start_fn = (_VRCC_Start_fn)GetProcAddress(hInstLibrary,"VRCC_Start");
    VRCC_Shutdown_fn = (_VRCC_Shutdown_fn)GetProcAddress(hInstLibrary,"VRCC_Shutdown");
		if(VRCC_Start_fn) return true;
		return false;
	}
	else
	{
		return false;
	}
}



//
//  Voisus Remote Control Client (VRCC) interface
//
//  Copyright 2015 Advanced Simulation Technology, inc.

#ifndef VRCC_H
#define VRCC_H

#include <vrc_types.h>

// Define external linkages
#if defined(_WIN32)
#  if defined(VRCC_BUILD)
#    define VRC_API __declspec(dllexport)
#  else
#    define VRC_API __declspec(dllimport)
#  endif
#else
#  define VRC_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Starts the VRC messaging client
/// @details This function must be called before any other VRCC API calls can be made.
/// @param argc Count of arguments passed to main Voisus client process
/// @param argv NULL-terminated list of arguments
/// @returns 1 on success, 0 on error
VRC_API int VRCC_Start(int argc, char* argv[]);

/// @brief Shuts down the VRC messaging client
/// @details This function should be called before exiting the program,
/// typically after a call to ::Voisus_Shutdown.
VRC_API void VRCC_Shutdown();

/// @brief Update the internal state of the VRC Client
/// @details This function must be called in order to receive any updates to the
/// @details state of the VRC Client. Typically this will be called in the main
/// @details execution loop before accessing any other API calls.
/// @return 1 on state changed, 0 otherwise
VRC_API int VRCC_Update(void);

/// @brief Connects to a Voisus Server
/// @details Initiates Voisus Client connection to specified server.
/// @param target_ip IPv4 address of the server
/// @see Network_ConnectState, Network_ConnectionStatus
VRC_API void Voisus_ConnectServer(const char* target_ip);

/// @brief Disconnects from a Voisus Server
/// @details Disconnects Voisus client from the current connection
/// @see Network_ConnectState, Network_ConnectionStatus
void Voisus_Disconnect();

/// @brief Gets current Voisus error state
/// @returns error code of type ::Error_t
int Voisus_Error();

/// @brief Saves current client configuration to file
/// @details Writes the current settings to a file.
/// Values will be automatically written after some operations, therefore
/// this function is optional.
/// The last saved settings are automatically loaded when the Voisus Client process starts.
void Voisus_Save();

/// @brief Gets the path to the Voisus client log file
/// @details This function is useful for displaying the log in a user application.
/// @returns full path to log file
const char* Voisus_LogPath();

/// @brief Gets the build version of the Voisus client
/// @returns build version string
const char* Voisus_ClientBuildVersion();

/// @brief Gets the version of the Voisus client message protocol
/// @returns version string
const char* Voisus_ClientMsgVersion();

/// @brief Gets the timestamp of the Voisus client message protocol
/// @returns version string
const char* Voisus_ClientMsgDate();

/// @brief Gets the build version of the Voisus server
/// @returns build version string
const char* Voisus_ServerBuildVersion();

/// @brief Gets the version of the Voisus server message protocol
/// @returns version string
const char* Voisus_ServerMsgVersion();

/// @brief Gets the timestamp of the Voisus server message protocol
/// @returns version string
const char* Voisus_ServerMsgDate();

/// @brief Monitors for system power events (on Windows XP/Vista/7/8)
/// @details On system suspend/sleep, the client will exit cleanly.
/// @param hwnd A valid window handle (HWND) used by the GUI
void Voisus_MonitorPowerEvents(int hwnd);

/// @brief Sets the master volume on the server
/// @details This volume affects software clients as well as hardware devices
/// @details like ACU2 or AI-S.
/// @param volume value in range [0.0, 100.0]
void Voisus_SetServerMasterVolume(float volume);

/// @brief Sets the sidetone volume on the server
/// @details This volume only applies to hardware devices like ACU2 or AI-S.
/// @param volume value in range [0.0, 100.0]
void Voisus_SetServerSidetoneVolume(float volume);

/// @brief Gets the Voisus Server address
/// @returns string containing IPv4 address of Voisus Server for this client.
/// Connection status can be determined through Network API functions.
/// @see Network_ConnectState, Network_ConnectionStatus
const char* Network_TargetIP();

/// @brief Gets the Client address used to connect to the Server
/// @returns IPv4 address of Client connection
const char* Network_ClientIP();

/// @brief Gets the connection status of client
/// @details This function returns whether the client is connected
/// or disconnected from the Server. For more detailed connection
/// information, see ::Network_ConnectState.
/// @returns status of type ::ConnectionStatus_t
/// @see Network_ConnectState
int Network_ConnectionStatus();

/// @brief Gets the detailed connection state of the client
/// @details This function returns detailed information about the
/// connection including getting/setting Role information.
/// @returns detailed connection state of type ::ConnectState_t
int Network_ConnectState();

/// @brief Gets the user-settable client name
/// @details The client name is published on the Server and to other clients.
/// @returns client name, or empty string
const char* Network_ClientName();

/// @brief Sets the client name
/// @details The client name is published on the Server and to other clients.
/// @param name User-settable name for the client.
void Network_SetClientName(const char* name);

/// @brief Gets the unique ID of the Operator
/// @details This is the 32-character unique identifier of the Operator instance
/// on the server that the client is currently connected to.
/// @returns operator ID if connected, empty string otherwise
const char* Network_OperatorId();

/// @brief Gets the total number of Roles available to the client
/// @returns number of roles
int Role_ListCount();

/// @brief Gets the version count of Role updates
/// @details This counter increments when role information is updated.
/// @returns count of role updates
int Role_Version();

/// @brief Gets the name of a specified Role
/// @param list_index index of role in list
/// @returns name of Role, or empty string
/// @see Role_ListCount
const char* Role_Name(int list_index);

/// @brief Gets the unique ID of a specified Role
/// @param list_index index of role in list
/// @returns 32-character unique identifier of Role, or empty string
/// @see Role_ListCount
const char* Role_Id(int list_index);

/// @brief Gets the name of the current Role
/// @details This value updates only after a successful connection is made.
/// @returns name of Role, or empty string
/// @see Role_SetRole
const char* Role_NameActive();

/// @brief Gets the unique ID of the current Role
/// @details This value updates only after a successful connection is made.
/// @returns 32-character unique identifier of Role, or empty string
/// @see Role_SetRole
const char* Role_IdActive();

/// @brief Gets the name of the last-set Role
/// @details This value updates immediately.
/// @returns name of Role, or empty string
/// @see Role_SetRole
const char* Role_NameSet();

/// @brief Gets the unique ID of the last-set Role
/// @details This value updates immediately.
/// @returns 32-character unique identifier for Role, or empty string
/// @see Role_SetRole
const char* Role_IdSet();

/// @brief Gets whether autotune ability is enabled for a role
/// @returns 1 if role_id is valid and autotune enabled, 0 otherwise
int Role_AutotuneEnabled(const char* role_id);

/// @brief Gets whether live radio control ability is enabled for a role
/// @returns 1 if role_id is valid and live radio control enabled, 0 otherwise
int Role_RadCtrlEnabled(const char* role_id);

/// @brief Sets a new Role to connect with
/// @details Sends a request to connect to a new role with the
/// specified unique ID. When the connection is complete,
/// the value returned by ::Role_IdActive will match the role_id
/// parameter.
/// @param role_id 32-character unique identifier for Role
/// @see Role_Id
void Role_SetRole(const char* role_id);

/// @brief Gets whether calling is enabled for a role
/// @param role_id 32-character unique identifier for Role
/// @returns 1 if role_id is valid and calling is enabled, 0 otherwise
int Role_CallingEnabled(const char* role_id);

/// @brief Gets whether PTT is required to transmit audio on a call
/// @details If enabled, audio will only be sent to ongoing call when PTT is
/// @details pressed.
/// @details
/// @details If disabled, call audio will be automatically transmitted when on a
/// @details call. Pressing PTT in this mode will direct mic audio from ongoing
/// @details call to radio transmission.
/// @param role_id 32-character unique identifier for Role
/// @returns 1 if role_id is valid and calling is enabled, 0 otherwise
int Role_CallPTTEnabled(const char* role_id);

/// @brief Gets whether chat is enabled for a role
/// @param role_id 32-character unique identifier for Role
/// @returns 1 if role_id is valid and chat is enabled, 0 otherwise
int Role_ChatEnabled(const char* role_id);

/// @brief Get the channel index to display at a given offset
/// @param role_id 32-character unique identifier for Role
/// @param index offset in display array
/// @returns channel index if channel is assigned at that location, -1 otherwise
int Role_ChannelDisplayMap(const char* role_id, int index);

/// @brief Gets the total number of Entity States (Vehicles) available to the client
/// @returns number of entity states
int EntityState_ListCount();

/// @brief Gets the version count of Entity State updates
/// @details This counter increments when entity state information is updated.
/// @returns count of entity state updates
int EntityState_Version();

/// @brief Gets the name of a specified Entity State (Vehicle)
/// @param list_index index of entity state in list
/// @returns name of Entity State, or empty string
/// @see EntityState_ListCount
const char* EntityState_Name(int list_index);

/// @brief Gets the unique ID of a specified Entity State (Vehicle)
/// @param list_index index of entity state in list
/// @returns 32-character unique identifier of Entity State, or empty string
/// @see EntityState_ListCount
const char* EntityState_Id(int list_index);

/// @brief Gets the name of the current Entity State (Vehicle)
/// @details This value updates only after Entity State is set successfully
/// @returns name of Entity State, or empty string
/// @see EntityState_SetEntityState
const char* EntityState_NameActive();

/// @brief Gets the unique ID of the currently selected Entity State
/// @details This value updates only after Entity State is set successfully
/// @returns 32-character unique identifier of Entity State, or empty string
const char* EntityState_IdActive();

/// @brief Gets the name of the last-set Entity State
/// @details This value updates immediately
/// @returns name of Entity State, or empty string
const char* EntityState_NameSet();

/// @brief Gets the unique ID of the last-set Entity State (Vehicle)
/// @details This value updates immediately
/// @returns 32-character unique identifier for Entity State, or empty string
const char* EntityState_IdSet();

/// @brief Sets a new Entity State (Vehicle) to connect with
/// @details Sends a request to connect to a new entity state with the
/// specified unique ID. When the connection is complete,
/// the value returned by ::EntityState_IdActive will match the id
/// parameter.
/// @param id 32-character unique identifier for Entity State
/// @see EntityState_Id
void EntityState_SetEntityState(const char* id);

/// @brief Gets the vox threshold
/// @details Threshold for Vox system. Higher thresholds require
/// greater voice volume to trigger transmission.
/// @returns threshold in range [0.0, 100.0]
float Headset_VoxThreshold();

/// @brief Gets the microphone mode
/// @details The mode can either be Off, Vox, PTT, or Hot.
/// In vox mode, voice level determines transmission activity (based
/// on vox threshold). In PTT mode, transmission is only made when
/// PTT is pressed. In hot mode, voice transmission is always active.
/// @returns mode of type ::MicMode_t
int Headset_MicrophoneMode();

/// @brief Gets the earphone volume
/// @returns volume in range [0.0, 100.0]
float Headset_EarphoneVolume();

/// @brief Gets the microphone volume
/// @returns volume in range [0.0, 100.0]
float Headset_MicVolume();

/// @brief Gets the sidetone volume
/// @details Sidetone is the audio feedback of the client's voice to their
/// own earphone.
/// Sidetone is provided by the USB headset or sound card hardware, therefore
/// may not be available.
/// @returns volume in range [0.0, 100.0]
/// @see Headset_HasSidetone
float Headset_SidetoneVolume();

/// @brief Gets whether headset has sidetone
/// @returns 1 if headset has sidetone, 0 otherwise
int Headset_HasSidetone();

/// @brief Selects from a preset headset configuration
/// @details Sets the headset preset. Each preset contains
/// default values. There are presets for Plantronics USB
/// headset and the ASTi Radius.
/// @param preset value of type ::HeadsetPreset_t
void Headset_SetHeadsetPreset(int preset);

/// @brief Sets the vox threshold
/// @details Sets the current Vox threshold to the specified value.
/// Higher thresholds require greater voice volume to trigger transmission.
/// @param threshold value in range [0.0, 100.0]
void Headset_SetVoxThreshold(float threshold);

/// @brief Sets the microphone mode
/// @details Sets the microphone mode to either Off, Vox, PTT, or Hot.
/// In vox mode, voice level determines transmission activity (based
/// on vox threshold). In PTT mode, transmission is only made when
/// PTT is pressed. In hot mode, voice transmission is always active.
/// @param mode value of type ::MicMode_t
void Headset_SetMicrophoneMode(int mode);

/// @brief Sets the microphone mute during an active call
/// @param active 1 => mute is active, 0 => mute is inactive
void Headset_SetCallMicrophoneMute(int active);

/// @brief Sets the earphone volume
/// @param volume value in range [0.0, 100.0]
void Headset_SetEarphoneVolume(float volume);

/// @brief Sets the microphone volume
/// @param volume value in range [0.0, 100.0]
void Headset_SetMicVolume(float volume);

/// @brief Sets the sidetone volume
/// @details Sets the current sidetone volume to the specified value.
/// Sidetone is the audio feedback of the client's voice to their own earphone.
/// Sidetone is provided by the USB headset or sound card hardware, therefore
/// may not be available.
/// @param volume value in range [0.0, 100.0]
/// @see Headset_HasSidetone
void Headset_SetSidetoneVolume(float volume);

/// @brief Gets whether client successfully configure an audio device
/// @returns 1 for configured, 0 otherwise
int Headset_DeviceConfigured();

/// @brief Sets the software push-to-talk (PTT) state for a given PTT
/// @details When the pressed parameter is non-zero, audio will be
/// transmitted on any radios that have their transmit state enabled and
/// are designated for this PTT.
/// @param ptt index of PTT to update
/// @param pressed 1 for pressed, 0 otherwise
/// @see Radio_SetTransmitEnabled, Radio_IsTransmitEnabled, Radio_PTT
void PTT_SetPressed_Multi(int ptt, int pressed);

/// @brief Sets the software push-to-talk (PTT) state for primary PTT
/// @details When the ptt parameter is non-zero, audio will be
/// transmitted on any radios that have their transmit state enabled.
/// @param pressed 1 for pressed, 0 otherwise
/// @see Radio_SetTransmitEnabled, Radio_IsTransmitEnabled, Radio_PTT, PTT_SetPressed_Multi
void PTT_SetPressed(int pressed);

/// @brief Gets the current pressed state of a specified software push-to-talk (PTT)
/// @details The value reflects the state of a software PTT (not hardware).
/// @param ptt index of PTT to query
/// @returns 1 for pressed, 0 otherwise
/// @see PTT_HWGetPressed
int PTT_GetPressed_Multi(int ptt);

/// @brief Gets the current pressed state of the primary software push-to-talk (PTT) state
/// @details The value reflects the state of the software PTT (not hardware).
/// @returns 1 for pressed, 0 otherwise
/// @see PTT_HWGetPressed, PTT_GetPressed_Multi
int PTT_GetPressed();

/// @brief Gets the current hardware push-to-talk (PTT) state (multiple)
/// @details This value only reflects the state of the specified hardware PTT
/// (not software) including joysticks. Pass -1 for ANY PTT (values are OR'd).
/// @param ptt index of hardware PTT to query
/// @returns 1 for pressed, 0 otherwise
/// @see PTT_GetPressed, Joystick_Pressed
int PTT_HWGetPressed_Multi(int ptt);

/// @brief Gets the current hardware push-to-talk (PTT) state
/// @details This value only reflects the state of the primary hardware PTT
/// (not software) including joysticks.
/// @returns 1 for pressed, 0 otherwise
/// @see PTT_GetPressed, Joystick_Pressed, PTT_HWGetPressed_Multi
int PTT_HWGetPressed();

/// @brief Gets the current number of radios
/// @returns number of radios
int Radio_ListCount();

/// @brief Gets the name of a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns name of radio, or empty string
/// @see Radio_ListCount
const char* Radio_Name(int radio_index);

/// @brief Sets the net for a radio by index
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @see Radio_ListCount, Radio_NetListCount
void Radio_SetNet(int radio_index, int net_index);

/// @brief Override the receive frequency for a net assigned to a particular radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_id 32-character unique identifier for net
/// @param freq receive frequency (in Hz)
/// @see Radio_ListCount, Radio_NetID
void Radio_SetNetRxFrequency(int radio_index, const char* net_id, unsigned long long freq);

/// @brief Get the receive frequency for the currently tuned net of a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns receive frequency of net, or 0 if radio_index is invalid
/// @see Radio_ListCount
unsigned long long Radio_NetRxFrequencyActive(int radio_index);

/// @brief Override the transmit frequency for a net assigned to a particular radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_id 32-character unique identifier for net
/// @param freq transmit frequency (in Hz)
/// @see Radio_ListCount, Radio_NetID
void Radio_SetNetTxFrequency(int radio_index, const char* net_id, unsigned long long freq);

/// @brief Get the transmit frequency for the currently tuned net of a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns transmit frequency of net, or 0 if radio_index is invalid
/// @see Radio_ListCount
unsigned long long Radio_NetTxFrequencyActive(int radio_index);

/// @brief Sets the net for a radio by unique ID
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_id 32-character unique identifier for net
/// @see Radio_ListCount, Radio_NetID
void Radio_SetNetID(int radio_index, const char* net_id);

/// @brief Gets the number of nets for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns number of nets available
/// @see Radio_ListCount
int Radio_NetListCount(int radio_index);

/// @brief Gets the name of a net by index for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns name of net, or empty string
/// @see Radio_ListCount, Radio_NetListCount
const char* Radio_NetName(int radio_index, int net_index);

/// @brief Gets the name of currently selected net for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns name of net, or empty string
/// @see Radio_ListCount
const char* Radio_NetNameActive(int radio_index);

/// @brief Gets the unique ID of a net for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns 32-character unique identifier of net, or empty string
/// @see Radio_ListCount, Radio_NetListCount
const char* Radio_NetID(int radio_index, int net_index);

/// @brief Gets the frequency of the radio's net
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns returns unsigned long long for frequency or 0 if none
/// @see Radio_ListCount, Radio_NetListCount
unsigned long long Radio_NetFrequency(int radio_index, int net_index);

/// @brief Gets the waveform of the radio's net
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns returns const char * for waveform or "" if none
/// @see Radio_ListCount, Radio_NetListCount
const char * Radio_NetWaveform(int radio_index, int net_index);

/// @brief Gets the crypto enabled of the radio's net
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns returns 0 if disabled, 1 if enabled
/// @see Radio_ListCount, Radio_NetListCount
int Radio_NetCryptoEnabled(int radio_index, int net_index);

/// @brief Gets the Net ID (for Frequency Hop nets only)
/// @details Freqhop nets will have a ::Radio_NetWaveform value of "HaveQuick" or "SINCGARS"
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns returns net_id for freqhop-enabled net, 0 otherwise
/// @see Radio_ListCount, Radio_NetListCount, Radio_NetWaveform
int Radio_NetFreqHopNetId(int radio_index, int net_index);

/// @brief Gets the unique ID of currently selected net for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 32-character unique identifier of net, or empty string
/// @see Radio_ListCount
const char* Radio_NetIDActive(int radio_index);

/// @brief Sets the receive enable for a radio
/// @details Enables or disables receiving of audio for the given radio.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param enable 1 for enable, 0 for disable
/// @see Radio_ListCount
void Radio_SetReceiveEnabled(int radio_index, int enable);

/// @brief Sets the transmit enable for a radio
/// @details Enables or disables transmission of audio on the selected radio.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param enable 1 for enable, 0 for disable
/// @see Radio_ListCount
void Radio_SetTransmitEnabled(int radio_index, int enable);

/// @brief Sets the crypto enable state for a radio
/// @details Enables or disables cipher text transmission for a radio.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param enable 1 for enable, 0 for disable
/// @see Radio_ListCount, Radio_CryptoEnabled
void Radio_SetCryptoEnable(int radio_index, int enable);

/// @brief Sets the receive volume for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param volume value in range [0.0, 100.0]
/// @see Radio_ListCount
void Radio_SetVolume(int radio_index, float volume);

/// @brief Sets the stereo receive volumes for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param volume_left value in range [0.0, 100.0]
/// @param volume_right value in range [0.0, 100.0]
/// @see Radio_ListCount
void Radio_SetVolumeStereo(int radio_index, float volume_left, float volume_right);

/// @brief Sets the audio balance for a radio
/// @details Audio balance can be left, right or center.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param balance value of type ::Balance_t
/// @see Radio_ListCount, Radio_Balance
void Radio_SetBalance(int radio_index, int balance);

/// @brief Sets the PTT to use for a radio
/// @details Each radio is assigned a PTT that should activate it when pressed.
/// @details Use this function to override the default PTT as specified in the Role.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param ptt_index which PTT to use
/// @see Radio_PTT, PTT_SetPressed_Multi
void Radio_SetPTT(int radio_index, int ptt_index);

/// @brief Sets the radio effects for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param effects_id radio effects id to set, empty string to unset
/// @see Radio_ListCount, Radio_RadioEffects, RadioEffects_IDFirst, RadioEffects_IDNext
void Radio_SetRadioEffects(int radio_index, const char* effects_id);

/// @brief Gets the receive enable for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for enabled, 0 for disabled
/// @see Radio_ListCount, Radio_SetReceiveEnabled
int Radio_IsReceiveEnabled(int radio_index);

/// @brief Gets the transmit enable for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for enabled, 0 for disabled
/// @see Radio_ListCount, Radio_SetTransmitEnabled
int Radio_IsTransmitEnabled(int radio_index);

/// @brief Gets the receive state for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for receiving, 0 otherwise
/// @see Radio_ListCount
int Radio_IsReceiving(int radio_index);

/// @brief Gets the transmit state for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for transmitting, 0 otherwise
/// @see Radio_ListCount
int Radio_IsTransmitting(int radio_index);

/// @brief Gets whether a radio is shared by two or more operators.
/// Shared radios are accessed through Entity States (Vehicles).
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for shared, 0 otherwise
/// @see Radio_ListCount
int Radio_IsShared(int radio_index);

/// @brief Gets the receive volume for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns volume in range [0.0, 100.0]
/// @see Radio_ListCount
float Radio_Volume(int radio_index);

/// @brief Gets the stereo (left ear) receive volume for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns volume in range [0.0, 100.0]
/// @see Radio_ListCount
float Radio_VolumeStereoLeft(int radio_index);

/// @brief Gets the stereo (right ear) receive volume for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns volume in range [0.0, 100.0]
/// @see Radio_ListCount
float Radio_VolumeStereoRight(int radio_index);

/// @brief Gets whether net selection is locked for a radio
/// @details When net selection is locked, the net cannot be changed
/// by the client.  This configuration is set in the definition of a Role
/// on the Voisus Server.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for locked, 0 otherwise
/// @see Radio_ListCount
int Radio_IsNetLocked(int radio_index);

/// @brief Gets whether the RX/TX enables are locked for a radio
/// @details When the RX/TX enables are locked, the receive and transmit
/// enables cannot be changed by the client.  This configuration is set
/// in the definition of a Role on the Voisus Server.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 for locked, 0 otherwise
/// @see Radio_ListCount
int Radio_IsRXModeLocked(int radio_index);

/// @brief Gets the audio balance for a radio (left, right, center)
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns balance of type ::Balance_t
int Radio_Balance(int radio_index);

/// @brief Gets the type of radio (e.g. URC-200)
/// @details Used when displaying a radio that is meant to simulate a
/// specific hardware radio.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns name of radio type (empty string indicates generic radio)
const char* Radio_Type(int radio_index);

/// @brief Gets whether radio has crypto mode enabled
/// @details Enabled means cipher text mode. Disabled means plain text mode.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 if cipher text is enabled, 0 otherwise
int Radio_CryptoEnabled(int radio_index);

/// @brief Gets the version count for radio updates
/// @details This counter increments when any radio information is updated.
/// @returns count of radio updates
int Radio_Version();

/// @brief Gets the PTT identifier for the radio
/// @details Return value of 0 indicates primary PTT, 1 is secondary, etc.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns ptt identifier
int Radio_PTT(int radio_index);

/// @brief Gets the radio effects set for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 32-character unique ID of radio effects, or empty string
const char* Radio_RadioEffects(int radio_index);

/// @brief Gets the Radio Control Id of a radio configured to control live radios
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 32-character unique ID of radio control, or empty string
/// @see Radio_ListCount
const char* Radio_RadCtrlId(int radio_index);

/// @brief Gets the audio level of a radio
/// @details Audio level calculation must be enabled first. Audio level is
/// @details calculated 5 times per second as an RMS value of received
/// @details radio audio and is not affected by volume adjustments.
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns Audio level value between 0.0 and 1.0. Returns 0.0 if disabled.
/// @see Radio_AudioLevelEnable, Radio_AudioLevelEnabled
float Radio_AudioLevel(int radio_index);

/// @brief Gets whether audio level calculation is enabled for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @returns 1 if calculation is enabled, 0 otherwise
/// @see Radio_AudioLevel
int Radio_AudioLevelEnabled(int radio_index);

/// @brief Enables or disables audio level calculation for a radio
/// @param radio_index index of radio in range [0, radio_count-1]
/// @param enable 1 for enable, 0 for disable
/// @see Radio_ListCount, Radio_AudioLevelEnabled
void Radio_SetAudioLevelEnable(int radio_index, int enable);

/// @brief Writes a message to the Voisus client log
/// @details The message will be logged as "<function> : <msg>".  See the
/// Voisus log for examples.
/// @param function the function or scope that wrote the message
/// @param msg the log message
/// @see Voisus_LogPath
/// Parses msg for " and \n characters and replaces them with "" and ' '
void Log_Write(const char* function, const char* msg);

/// @brief Enable Earshot support
/// @details This function must be called with a non-zero argument
/// before any other Earshot calls are made. By default, Earshot is disabled.
/// @param enable non-zero for enable, 0 for disable
void Earshot_Enable(int enable);

/// @brief Sets the Earshot push-to-talk (PTT) state
/// @details When the ptt parameter is non-zero, audio will be
/// transmitted into the ambient sound environment.
/// @param ptt 1 for pressed, 0 otherwise
/// @see Earshot_Enable
void Earshot_SetPTT(int ptt);

/// @brief Gets the receive state for Earshot
/// @returns 1 for receiving, 0 otherwise
/// @see Earshot_Enable
int Earshot_Receiving(void);

/// @brief Gets the transmit state for Earshot
/// @returns 1 for transmitting, 0 otherwise
/// @see Earshot_Enable
int Earshot_Transmitting(void);

/// @brief Sets the world position for a Voisus operator
/// @details The world position is specified in geocentric x, y, z coordinates.
/// Coordinates are used to position a player in the three-dimensional audio space
/// for interaction with the Earshot audio environment.
/// @param xcoord X coordinate
/// @param ycoord Y coordinate
/// @param zcoord Z coordinate
void WorldPosition_Set(float xcoord, float ycoord, float zcoord);

/// @brief Gets the current number of detected joysticks
/// @returns number of joysticks
int Joystick_ListCount();

/// @brief Gets the name of a specified joystick
/// @param list_index index of joystick in the range [0, number of joysticks - 1]
/// @returns name of Joystick, or empty string
/// @see Joystick_ListCount
const char* Joystick_Name(int list_index);

/// @brief Gets the number of buttons for a specified joystick
/// @param list_index index of joystick in the range [0, number of joysticks - 1]
/// @returns number of buttons for joystick, or -1 on error
/// @see Joystick_ListCount
int Joystick_ButtonCount(int list_index);

/// @brief Gets the active joystick index for a specified PTT
/// @param ptt index of PTT to query (0 for primary, 1 for secondary)
/// @returns index of the active joystick for the specificed PTT, -1 if not set
int Joystick_Active_Multi(int ptt);

/// @brief Gets the active joystick index
/// @returns index of the active joystick for primary PTT, -1 if not set
int Joystick_Active();

/// @brief Gets the active joystick button index
/// @param ptt index of PTT to query (0 for primary, 1 for secondary)
/// @returns index of the active joystick button for the specified PTT, -1 if not set
int Joystick_ButtonActive_Multi(int ptt);

/// @brief Gets the active joystick button index
/// @returns index of the active joystick button, -1 if not set
int Joystick_ButtonActive();

/// @brief Gets the current joystick pressed state
/// @param ptt index of PTT to query (0 for primary, 1 for secondary)
/// @returns whether active joystick button is pressed
int Joystick_Pressed_Multi(int ptt);

/// @brief Gets the current joystick pressed state
/// @returns whether active joystick button is pressed
int Joystick_Pressed();

/// @brief Selects the active joystick button
/// @details Sets the active joystick button that will be monitored
/// for button presses used for push-to-talk (PTT) functionality.
/// @param ptt index of PTT to query (0 for primary, 1 for secondary)
/// @param js index of joystick
/// @param btn index of button
/// @see Joystick_Pressed
void Joystick_SetButton_Multi(int ptt, int js, int btn);

/// @brief Selects the active joystick button
/// @details Sets the active joystick button that will be monitored
/// for button presses used for push-to-talk (PTT) functionality.
/// @param js index of joystick
/// @param btn index of button
/// @see Joystick_Pressed
void Joystick_SetButton(int js, int btn);

/// @brief Gets currently selected Codec
/// @returns codec of type ::Codec_t
int Codec_Get();

/// @brief Sets a new Codec
/// @param codec value of type ::Codec_t
void Codec_Set(int codec);

/// @brief Gets the lock on all Call and Endpoint data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Call_ReleaseLock
void Call_GetLock();

/// @brief Releases the lock on all Call and Endpoint data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Call_GetLock
void Call_ReleaseLock();

/// @brief Create a new call and join it
/// @details For more information, see documentation on \ref calls.
/// @returns 32-character unique ID of call
/// @see Call_Invite, Phone_SetCall
const char* Call_Create();

/// @brief Send an invitation to another endpoint
/// @details For more information, see documentation on \ref invitations.
/// @param call_id 32-character unique ID of call
/// @param endpoint_id 32-character unique ID of endpoint to invite
/// @see Call_Endpoint_State
void Call_Invite(const char* call_id, const char* endpoint_id);

/// @brief Send an invitation to an endpoint to dial a phone number
/// @details Intended for use with endpoints representing phone lines.
/// @warning If the invited endpoint accepts the invitation, client will
/// @warning automatically leave current call and be transferred to new call.
/// @details For more information, see documentation on \ref invitations.
/// @param call_id 32-character unique ID of call
/// @param endpoint_id 32-character unique ID of endpoint to invite
/// @param dial_number string containing the phone number to call
/// @see Call_Endpoint_State
void Call_Invite_Dial(const char* call_id, const char* endpoint_id, const char* dial_number);

/// @brief Invite all members of crew to a call
void Call_InviteCrew();

/// @brief Get the first call in set of calls for this endpoint
/// @returns 32-character unique ID of call, or empty string if none
/// @see Call_GetLock
const char* Call_IDFirst();

/// @brief Get the next call in set of calls for this endpoint
/// @returns 32-character unique ID of call, or empty string if none
/// @see Call_GetLock, Call_IDFirst
const char* Call_IDNext();

/// @brief Get the size of the set of calls for this endpoint
/// @returns count of calls
int Call_ListCount();

/// @brief Gets the version count for call and endpoint updates
/// @details This counter increments when any Call or Endpoint information is updated
/// @details provided updates are not locked due to ::Call_GetLock.
/// @returns count of updates
int Call_Endpoint_Version();

/// @brief Get the first Endpoint for a call
/// @returns 32-character unique ID of endpoint, or empty string if none
/// @see Call_GetLock
const char* Call_Endpoint_IDFirst(const char* call_id);

/// @brief Get the next Endpoint for a call
/// @returns 32-character unique ID of endpoint, or empty string if none
/// @see Call_GetLock, Call_Endpoint_IDFirst
const char* Call_Endpoint_IDNext(const char* call_id);

/// @brief Get the current state of an Endpoint on a call
/// @details For more information, see documentation on \ref calls.
/// @param call_id 32-character unique ID of call
/// @param ep_id 32-character unique ID of endpoint
/// @returns state of type ::CallProgress_t
/// @see Call_GetLock, Call_Endpoint_IDFirst
int Call_Endpoint_State(const char* call_id, const char* ep_id);

/// @brief Gets the version count for call invitation updates
/// @details This counter increments when any invitation is added
/// @details provided updates are not locked due to ::Call_GetLock.
/// @returns count of updates
int Call_Invitation_Version();

/// @brief Get the first Invitation from list
/// @details Invitations will remain until cleared with ::Call_Invitation_ClearAll
/// @param invite pointer to structure of type ::CallInvitation_t (for return value)
/// @returns 1 if invitation found, 0 otherwise
/// @see Call_GetLock
int Call_Invitation_First(CallInvitation_t* invite);

/// @brief Get the next Invitation from list
/// @details Invitations will remain until cleared with ::Call_Invitation_ClearAll
/// @param invite pointer to structure of type ::CallInvitation_t (for return value)
/// @returns 1 if invitation found, 0 otherwise
/// @see Call_GetLock, Call_Invitation_First
int Call_Invitation_Next(CallInvitation_t* invite);

/// @brief Clear all invitations from list
/// @details This method should be called after all invitations in the list are read.
/// @details Invitations are one-way notifications without state and will not time out.
/// @see Call_GetLock
void Call_Invitation_ClearAll();

/// @brief Update current state of user Endpoint for a call
/// @details For more information, see documentation on \ref calls.
/// @param call_id 32-character unique ID of call
/// @param call_state state of type ::CallProgress_t
void Call_Progress(const char* call_id, int call_state);

/// @brief Leave a call with a specified reason
/// @details For more information, see documentation on \ref calls.
/// @param call_id 32-character unique ID of call
/// @param leave_reason reason of type ::CallLeave_t
void Call_Leave(const char* call_id, int leave_reason);

/// @brief Get the count phones for this endpoint
/// @details For more information, see documentation on \ref phones.
/// @returns 1 if phone present, 0 otherwise
int Phone_ListCount();

/// @brief Get the active call ID
/// @returns 32-character unique ID for call
const char* Phone_CallActive();

/// @brief Get the receive volume for a phone
/// @returns volume in range [0.0, 100.0]
float Phone_Volume();

/// @brief Set the active call for phone
/// @details For more information, see documentation on \ref phones.
/// @param call_id 32-character unique ID of call, or empty string to clear
/// @see Call_Create
void Phone_SetCall(const char* call_id);

/// @brief Sets the receive volume for a phone
/// @param volume value in range [0.0, 100.0]
void Phone_SetVolume(float volume);

/// @brief Connects to a Voisus Cloud
/// @details Initiates Voisus Client connection to specified server cloud.
/// @param cloud_id Unique name of the cloud
/// @see Network_ConnectState, Network_ConnectionStatus
void Voisus_ConnectCloud(const char* cloud_id);

/// @brief Gets the last set Cloud to connect to
/// @returns Unique name of the cloud
const char* Network_CloudSet();

/// @brief Gets the currently connected Cloud
/// @returns Unique name of the cloud
const char* Network_CloudActive();

/// @brief Get the current connection mode (e.g. Cloud)
/// @returns mode of type ::ConnectionMode_t
int Network_ConnectionMode();

/// @brief Gets the lock on all Cloud data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Cloud_ReleaseLock
void Cloud_GetLock();

/// @brief Releases the lock on all Cloud data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Cloud_GetLock
void Cloud_ReleaseLock();

/// @brief Get the first Cloud
/// @returns 32-character unique ID of Cloud, or empty string if none
/// @see Cloud_GetLock
const char* Cloud_IDFirst();

/// @brief Get the next Cloud
/// @returns 32-character unique ID of Cloud, or empty string if none
/// @see Cloud_GetLock, Cloud_IDFirst
const char* Cloud_IDNext();

/// @brief Gets the current number of detected clouds
/// @returns number of clouds
int Cloud_ListCount();

/// @brief Gets the current number of detected clouds
/// @returns number of clouds
/// @see Cloud_IDFirst, Cloud_IDNext
int Cloud_GetServerCount(const char* uuid);

/// @brief Gets the version count for Clouds
/// @details This counter increments when any cloud information is
/// updated. (e.g. new server added/removed)
/// @returns count of cloud updates
int Cloud_Version();

/// @brief Gets the lock on all Operator data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Operator_ReleaseLock
void Operator_GetLock();

/// @brief Releases the lock on all Operator data
/// @warning This method is deprecated in VRCC 5.13.0 and above
/// @see Operator_GetLock
void Operator_ReleaseLock();

/// @brief Get the first Operator
/// @returns 32-character unique ID of operator, or empty string if none
/// @see Operator_GetLock
const char* Operator_IDFirst();

/// @brief Get the next Operator
/// @returns 32-character unique ID of Operator, or empty string if none
/// @see Operator_GetLock, Operator_IDFirst
const char* Operator_IDNext();

/// @brief Gets the current number of Operators
/// @returns number of Operators
int Operator_ListCount();

/// @brief Get a field for an Operator
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"role"</em></td><td>Role name</td></tr>
/// @details <tr><td></td><td></td><td><em>"clientname"</em></td><td>Client name</td></tr>
/// @details <tr><td></td><td></td><td><em>"hostname"</em></td><td>Hostname of server that client is connected to</td></tr>
/// @details <tr><td></td><td></td><td><em>"connected"</em></td><td>"true" if connected, "false" otherwise</td></tr>
/// @details <tr><td></td><td></td><td><em>"callactive"</em></td><td>"true" if currently on a call (busy), "false" otherwise</td></tr>
/// @details <tr><td></td><td></td><td><em>"clientversion"</em></td><td>Version of client</td></tr>
/// @details <tr><td></td><td></td><td><em>"serverversion"</em></td><td>Version of server</td></tr>
/// @details </table>
/// @details For more information, see documentation on \ref endpoints.
/// @param uuid 32-character unique ID of Operator
/// @param field_name name of field
/// @returns field value, or empty string if field not found
/// @see Operator_GetLock, Operator_IDFirst, Operator_IDNext
const char* Operator_GetField(const char* uuid, const char* field_name);

/// @brief Gets the version count for Operators
/// @details This counter increments when any Operator information is
/// updated, including operators added/removed or fields changed
/// @details provided updates are not locked due to ::Operator_GetLock.
/// @returns count of Operator updates
int Operator_Version();

/// @brief Gets the number of radios that can be controlled
/// @returns number of controllable live radios
int RadCtrl_ListCount();

/// @brief Gets the name of a live radio to control
/// @returns name of radio, or empty string if not found
const char* RadCtrl_Name(int index);

/// @brief Poll server for updated radio state information
/// @param name name of live radio to control
/// @see RadCtrl_ListCount, RadCtrl_Name
void RadCtrl_Poll(const char* name);

/// @brief Get live radio setting string value by name
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"mod_mode"</em></td><td>Modulation mode (e.g. AM, FM)</td></tr>
/// @details <tr><td></td><td></td><td><em>"tx_mod_mode"</em></td><td>Transmit modulation mode (e.g. AM, FM)</td></tr>
/// @details <tr><td></td><td></td><td><em>"power_lvl"</em></td><td>Power level (e.g. LOW, MED, HIGH)</td></tr>
/// @details <tr><td></td><td></td><td><em>"load_preset"</em></td><td>Are presets loadable? (e.g. TRUE, FALSE), must be TRUE in order to set any presets, or FALSE to modify any individual settings</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of value to retrieve
/// @returns string value of the specified setting, or empty string if not found
/// @see RadCtrl_ListCount, RadCtrl_Name, RadCtrl_GetOptionsStr
const char* RadCtrl_GetValueStr(const char* name, const char* setting);

/// @brief Get list of options for a live radio string setting
/// @param name name of live radio to control
/// @param setting name of setting for retrieve options list for
/// @returns string containing comma-separated list of valid options for setting, or empty string if not found
/// @see RadCtrl_ListCount, RadCtrl_Name, RadCtrl_GetValueStr
const char* RadCtrl_GetOptionsStr(const char* name, const char* setting);

/// @brief Get live radio setting int value by name
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"freq"</em></td><td>Frequency (in Hz)</td></tr>
/// @details <tr><td></td><td></td><td><em>"tx_freq"</em></td><td>Transmit Frequency (in Hz)</td></tr>
/// @details <tr><td></td><td></td><td><em>"preset"</em></td><td>Current preset (0-9), only valid if 'load_preset' is set to "TRUE"</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of value to retrieve
/// @returns int value of the specified setting, or -1 if not found
/// @see RadCtrl_ListCount, RadCtrl_Name
int RadCtrl_GetValueInt(const char* name, const char* setting);

/// @brief Get live radio setting float value by name
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"rx_power"</em></td><td>Receive Power</td></tr>
/// @details <tr><td></td><td></td><td><em>"squelch"</em></td><td>Squelch Level</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of value to retrieve
/// @returns int value of the specified setting, or -1 if not found
/// @see RadCtrl_ListCount, RadCtrl_Name
float RadCtrl_GetValueFloat(const char* name, const char* setting);

/// @brief Change a string setting of a live radio
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"mod_mode"</em></td><td>Modulation mode (e.g. AM, FM)</td></tr>
/// @details <tr><td></td><td></td><td><em>"tx_mod_mode"</em></td><td>Transmit modulation mode (e.g. AM, FM)</td></tr>
/// @details <tr><td></td><td></td><td><em>"power_lvl"</em></td><td>Power level (e.g. LOW, MED, HIGH)</td></tr>
/// @details <tr><td></td><td></td><td><em>"load_preset"</em></td><td>Enable preset mode? (e.g. TRUE, FALSE), set to TRUE before loading any presets or to FALSE before modifying any individual settings</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of setting to modify
/// @param value new value for setting
/// @see RadCtrl_ListCount, RadCtrl_Name
void RadCtrl_SetValueStr(const char* name, const char* setting, const char* value);

/// @brief Change an integer setting of a live radio
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"freq"</em></td><td>Frequency (in Hz)</td></tr>
/// @details <tr><td></td><td></td><td><em>"tx_freq"</em></td><td>Transmit Frequency (in Hz)</td></tr>
/// @details <tr><td></td><td></td><td><em>"preset"</em></td><td>Preset to load (0-9), can only load presets if 'load_preset' option is set to "TRUE"</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of setting to modify
/// @param value new value for setting
/// @see RadCtrl_ListCount, RadCtrl_Name
void RadCtrl_SetValueInt(const char* name, const char* setting, int value);

/// @brief Change a float setting of a live radio
/// @details Supported field names are
/// @details <table border="0">
/// @details <tr><td></td><td></td><td><em>"rx_power"</em></td><td>Receive Power</td></tr>
/// @details <tr><td></td><td></td><td><em>"squelch"</em></td><td>Squelch Level</td></tr>
/// @details </table>
/// @param name name of live radio to control
/// @param setting name of setting to modify
/// @param value new value for setting
/// @see RadCtrl_ListCount, RadCtrl_Name
void RadCtrl_SetValueFloat(const char* name, const char* setting, float value);

/// @brief Get error string for last radio control "set" operation
/// @returns string containing error message, or empty string if successful
const char* RadCtrl_Error();

/// @brief Gets the version count of Radio Control responses to new settings
/// @details This counter increments once for each RadCtrl_Set* API call.
/// @details If the response is an error, the error message can be fetched using
/// @details ::RadCtrl_Error.
/// @returns count of responses to radio control setting changes
/// @see RadCtrl_Error, RadCtrl_SetValueInt, RadCtrl_SetValueStr
int RadCtrl_ErrorVersion();

/// @brief Update user-settable DIS parameters for an operator
/// @details Settable fields are <i>site, app, entity and radio_offset</i> in the ::DISParams_t
/// @details structure. Set values to 0 to use system defaults.
/// @see DIS_GetParams
void DIS_SetParams(DISParams_t* dis_params);

/// @brief Get DIS parameters configured on server for an operator
/// @details Values are returned in the ::DISParams_t structure
/// @see DIS_SetParams
void DIS_GetParams(DISParams_t* dis_params);

/// @brief Update DIS exercise for operator radios
/// @param exercise value of new exercise in the range 1-255
/// @see DIS_GetExercise
void DIS_SetExercise(int exercise);

/// @brief Get DIS exercise for operator radios
/// @returns DIS exercise number for operator radios
/// @see DIS_SetExercise
int DIS_GetExercise();

/// @brief Enable/disable auxiliary audio input to client
/// @param enable 1 for enable, 0 for disable
/// @param sample_rate Audio sample rate (in Hz)
/// @param encoding Audio sample encoding (in ::AudioEncoding_t)
/// @see AuxAudio_Send
void AuxAudio_Enable(int enable, unsigned int sample_rate, unsigned int encoding);

/// @brief Send auxiliary audio to server (substitute for mic audio)
/// @param samples Audio samples
/// @param len Length of audio samples (in bytes)
/// @see AuxAudio_Enable
void AuxAudio_Send(unsigned char* samples, unsigned int len);

/// @brief Register callback to receive auxiliary audio from server
/// @param func Audio callback function of type ::AudioCallback
/// @see AuxAudio_Enable, AuxAudio_Send
void AuxAudio_Register(AudioCallback func);

/// @brief Get the number of radio effects
/// @returns count of radio effects
int RadioEffects_ListCount();

/// @brief Get the first radio effect in set of radio effects
/// @returns 32-character unique ID of effect, or empty string if none
const char* RadioEffects_IDFirst();

/// @brief Get the next radio effect in set of radio effects
/// @returns 32-character unique ID of effect, or empty string if none
/// @see Call_IDFirst
const char* RadioEffects_IDNext();

/// @brief Get the name of a radio effect
/// @param radio_effects_id 32-character unique ID of radio effect
/// @returns Name of radio effect, or empty string if id not found
/// @see RadioEffects_IDFirst, RadioEffects_IDNext
const char* RadioEffects_Name(const char* radio_effects_id);

/// @brief Gets the version count for jammer updates
/// @details This counter increments when any jammer information is updated.
/// @returns count of jammer updates
int Jammer_Version();

/// @brief Gets the current number of jammers
/// @returns number of jammers
int Jammer_ListCount();

/// @brief Gets the number of nets for a jammer
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @returns number of nets available
/// @see Jammer_ListCount
int Jammer_NetListCount(int jammer_index);

/// @brief Gets the name of a net for a jammer
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns name of net, or empty string
/// @see Jammer_ListCount, Jammer_NetListCount
const char* Jammer_NetName(int jammer_index, int net_index);

/// @brief Gets the unique ID of a net for a jammer
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @param net_index index of net in range [0, net_count-1]
/// @returns 32-character unique identifier of net, or empty string
/// @see Jammer_ListCount, Jammer_NetListCount
const char* Jammer_NetID(int jammer_index, int net_index);

/// @brief Gets the unique ID of currently selected net for a jammer
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @returns 32-character unique identifier of net, or empty string
/// @see Jammer_ListCount
const char* Jammer_NetIDActive(int jammer_index);

/// @brief Gets the transmit state for a jammer
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @returns 1 for transmitting, 0 otherwise
/// @see Jammer_ListCount
int Jammer_IsTransmitting(int jammer_index);

/// @brief Sets the net for a jammer by unique ID
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @param net_id 32-character unique identifier for net
/// @see Jammer_ListCount, Jammer_NetID
void Jammer_SetNetID(int jammer_index, const char* net_id);

/// @brief Enable/disable a jammer to begin/end transmission
/// @param jammer_index index of jammer in range [0, jammer_count-1]
/// @param enable 0 to disable, otherwise enable
/// @see Jammer_ListCount
void Jammer_SetEnable(int jammer_index, int enable);

/// @brief Gets the unique ID of the active Playback audio device
/// @details Playback devices are speakers and headsets
/// @param type Type of audio device (playback/capture) of type ::AudioDeviceType_t
/// @returns audio device ID, or empty string
/// @see AudioDevice_ListCount
const char* AudioDevice_IDActive(AudioDeviceType_t type);

/// @brief Get the first audio device of specified type
/// @param type Type of audio device (playback/capture) of type ::AudioDeviceType_t
/// @returns Unique ID of device, or empty string if none
const char* AudioDevice_IDFirst(AudioDeviceType_t type);

/// @brief Get the next audio device of specified type
/// @param type Type of audio device (playback/capture) of type ::AudioDeviceType_t
/// @returns Unique ID of device, or empty string if none
/// @see AudioDevice_IDFirst
const char* AudioDevice_IDNext(AudioDeviceType_t type);

/// @brief Get the name of an audio device of specified type by ID
/// @param type Type of audio device (playback/capture) of type ::AudioDeviceType_t
/// @param id Unique ID of device
/// @returns Name of device, or empty string if ID is not found
/// @see AudioDevice_IDFirst, AudioDevice_IDNext
const char* AudioDevice_Name(AudioDeviceType_t type, const char* id);

/// @brief Set the audio device (playback or capture) to use
/// @param type Type of audio device (playback/capture) of type ::AudioDeviceType_t
/// @param id Unique ID of device
/// @see AudioDevice_IDFirst, AudioDevice_IDNext
void AudioDevice_SetDevice(AudioDeviceType_t type, const char* id);

/// @brief Gets the version count of Audio Device updates
/// @details This counter increments when audio device information is updated.
/// @returns count of audio device updates
int AudioDevice_Version();

/// @brief Request a new license of specified type
/// @details Check status of license request (pending, granted, released or
/// @details lost) with ::License_Status.
/// @param type Type of license
/// @returns Identifier for license request, -1 on error
/// @see License_Status
int License_Request(const char* type);

/// @brief Release a license
/// @details Check status of license request (pending, granted, released or
/// @details lost) with ::License_Status.
/// @param license_id Identifier for license
/// @see License_Status
void License_Release(int license_id);

/// @brief Get status of license request
/// @param license_id Identifier for license
/// @see License_Request
int License_Status(int license_id);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

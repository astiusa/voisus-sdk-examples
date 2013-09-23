namespace VoisusCS
{

    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Runtime.InteropServices;
    using System.Diagnostics;
    using System.Threading;

    /// <summary>
    /// C# wrapper for the VRCC 
    /// </summary>
    /// <exception cref="DllNotFoundException">Thrown if the VRCC.dll is not in the same runtime directory</exception>
    public static class VRCC
    {
        #region private
        /* These are functions which need redefinitions to be used externally without the safe keyword */
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static int VRCC_Start(int argc, ref IntPtr argv);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_LogPath")]
        extern unsafe static sbyte* Voisus_LogPath_Unsafe ();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ClientBuildVersion")]
        extern unsafe static sbyte* Voisus_ClientBuildVersion_Unsafe ();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ClientMsgVersion")]
        extern unsafe static sbyte* Voisus_ClientMsgVersion_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ClientMsgDate")]
        extern unsafe static sbyte* Voisus_ClientMsgDate_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ServerBuildVersion")]
        extern unsafe static sbyte* Voisus_ServerBuildVersion_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ServerMsgVersion")]
        extern unsafe static sbyte* Voisus_ServerMsgVersion_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Voisus_ServerMsgDate")]
        extern unsafe static sbyte* Voisus_ServerMsgDate_Unsafe();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_TargetIP")]
        extern unsafe static sbyte* Network_TargetIP_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_ClientIP")]
        extern unsafe static sbyte* Network_ClientIP_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_ClientName")]
        extern unsafe static sbyte* Network_ClientName_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_OperatorId")]
        extern unsafe static sbyte* Network_OperatorId_Unsafe();
        
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_Name")]
        extern unsafe static sbyte* Role_Name_Unsafe(int list_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_Id")]
        extern unsafe static sbyte* Role_Id_Unsafe(int list_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_NameActive")]
        extern unsafe static sbyte* Role_NameActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_IdActive")]
        extern unsafe static sbyte* Role_IdActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_NameSet")]
        extern unsafe static sbyte* Role_NameSet_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Role_IdSet")]
        extern unsafe static sbyte* Role_IdSet_Unsafe();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_Id")]
        extern unsafe static sbyte* EntityState_Id_Unsafe(int list_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_NameActive")]
        extern unsafe static sbyte* EntityState_NameActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_Name")]
        extern unsafe static sbyte* EntityState_Name_Unsafe(int list_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_IdActive")]
        extern unsafe static sbyte* EntityState_IdActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_NameSet")]
        extern unsafe static sbyte* EntityState_NameSet_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "EntityState_IdSet")]
        extern unsafe static sbyte* EntityState_IdSet_Unsafe();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_NetName")]
        extern unsafe static sbyte* Radio_NetName_Unsafe(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_NetNameActive")]
        extern unsafe static sbyte* Radio_NetNameActive_Unsafe(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_NetID")]
        extern unsafe static sbyte* Radio_NetID_Unsafe(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_NetWaveform")]
        extern unsafe static sbyte* Radio_NetWaveform_Unsafe(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_NetIDActive")]
        extern unsafe static sbyte* Radio_NetIDActive_Unsafe(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Radio_Type")]
        extern unsafe static sbyte* Radio_Type_Unsafe(int radio_index);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Joystick_Name")]
        extern unsafe static sbyte* Joystick_Name_Unsafe (int list_index);
       
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Call_IDFirst")]
        extern unsafe static sbyte* Call_IDFirst_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Call_IDNext")]
        extern unsafe static sbyte* Call_IDNext_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Call_Endpoint_IDFirst")]
        extern unsafe static sbyte* Call_Endpoint_IDFirst_Unsafe([MarshalAs(UnmanagedType.LPStr)] String call_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Call_Endpoint_IDNext")]
        extern unsafe static sbyte* Call_Endpoint_IDNext_Unsafe([MarshalAs(UnmanagedType.LPStr)] String call_id);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Phone_CallActive")]
        extern unsafe static sbyte* Phone_CallActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_CloudSet")]
        extern unsafe static sbyte* Network_CloudSet_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Network_CloudActive")]
        extern unsafe static sbyte* Network_CloudActive_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Cloud_IDFirst")]
        extern unsafe static sbyte* Cloud_IDFirst_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Cloud_IDNext")]
        extern unsafe static sbyte* Cloud_IDNext_Unsafe();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Operator_IDFirst")]
        extern unsafe static sbyte* Operator_IDFirst_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Operator_IDNext")]
        extern unsafe static sbyte* Operator_IDNext_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "Operator_GetField")]
        extern unsafe static sbyte* Operator_GetField_Unsafe([MarshalAs(UnmanagedType.LPStr)] String uuid, [MarshalAs(UnmanagedType.LPStr)] String field_name);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "RadCtrl_GetValueStr")]
        extern unsafe static sbyte* RadCtrl_GetValueStr_Unsafe([MarshalAs(UnmanagedType.LPStr)] String name, [MarshalAs(UnmanagedType.LPStr)] String setting);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "RadCtrl_GetOptionsStr")]
        extern unsafe static sbyte* RadCtrl_GetOptionsStr_Unsafe([MarshalAs(UnmanagedType.LPStr)] String name, [MarshalAs(UnmanagedType.LPStr)] String setting);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "RadCtrl_Error")]
        extern unsafe static sbyte* RadCtrl_Error_Unsafe();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "RadCtrl_Name")]
        extern unsafe static sbyte* RadCtrl_Name_Unsafe(int index);


        #endregion private

        #region public
        /* These are functions which can be used externally without needing the safe keyword */
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Voisus_ConnectServer([MarshalAs(UnmanagedType.LPStr)] String target_ip);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void VRCC_Shutdown();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int VRCC_Update();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Voisus_Disconnect();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static Error_t Voisus_Error();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Voisus_Save();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Log_Write([MarshalAs(UnmanagedType.LPStr)] String function, [MarshalAs(UnmanagedType.LPStr)] String msg);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Network_SetClientName([MarshalAs(UnmanagedType.LPStr)] String name);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ConnectionStatus_t Network_ConnectionStatus();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ConnectState_t Network_ConnectState();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ConnectionMode_t Network_ConnectionMode();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Role_SetRole(String roleid);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_AutotuneEnabled([MarshalAs(UnmanagedType.LPStr)] String role_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_RadCtrlEnabled([MarshalAs(UnmanagedType.LPStr)] String role_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_CallingEnabled([MarshalAs(UnmanagedType.LPStr)] String role_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Role_ChatEnabled ([MarshalAs(UnmanagedType.LPStr)] String role_id);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int EntityState_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int EntityState_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void EntityState_SetEntityState([MarshalAs(UnmanagedType.LPStr)] String id);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Headset_VoxThreshold();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static MicMode_t Headset_MicrophoneMode();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Headset_EarphoneVolume();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Headset_MicVolume();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Headset_SidetoneVolume();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Headset_HasSidetone();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetHeadsetPreset(HeadsetPreset_t preset);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetVoxThreshold(float threshold);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetMicrophoneMode(MicMode_t mode);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetCallMicrophoneMute(int active);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetEarphoneVolume(float volume);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetMicVolume(float volume);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Headset_SetSidetoneVolume(float volume);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void PTT_SetPressed_Multi(int ptt, int pressed);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void PTT_SetPressed(int pressed);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int PTT_GetPressed_Multi(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int PTT_GetPressed();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int PTT_HWGetPressed_Multi(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int PTT_HWGetPressed();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetNet(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_NetListCount(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_NetCryptoEnabled(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_NetFreqHopNetId(int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetReceiveEnabled(int radio_index, int enable);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetTransmitEnabled(int radio_index, int enable);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetCryptoEnable(int radio_index, int enable);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetVolume(int radio_index, float volume);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsReceiveEnabled(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsTransmitEnabled(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsReceiving(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsTransmitting(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsShared(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Radio_Volume(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_Balance(Balance_t radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsNetLocked(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_IsRXModeLocked(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_CryptoEnabled(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Radio_PTT(int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ulong 	Radio_NetFrequency (int radio_index, int net_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetNetRxFrequency(int radio_index, [MarshalAs(UnmanagedType.LPStr)] String net_id, [MarshalAs(UnmanagedType.U8)] ulong freq);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetNetTxFrequency(int radio_index, [MarshalAs(UnmanagedType.LPStr)] String net_id, [MarshalAs(UnmanagedType.U8)] ulong freq);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Radio_SetNetID_Unsafe(int radio_index, [MarshalAs(UnmanagedType.LPStr)] String net_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ulong Radio_NetTxFrequencyActive (int radio_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static ulong Radio_NetRxFrequencyActive (int radio_index);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Earshot_Enable(int enable);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Earshot_SetPTT(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Earshot_Receiving();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Earshot_Transmitting();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void WorldPosition_Set(float xcoord, float ycoord, float zcoord);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_ButtonCount(int list_index);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_Active_Multi(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_Active();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_ButtonActive_Multi(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_ButtonActive();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_Pressed_Multi(int ptt);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Joystick_Pressed();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Joystick_SetButton_Multi(int ptt, int js, int btn);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Joystick_SetButton(int js, int btn);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static Codec_t Codec_Get();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Codec_Set(Codec_t codec);
        
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_GetLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_ReleaseLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Call_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Call_Endpoint_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_Invitation_ClearAll();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_Invite ([MarshalAs(UnmanagedType.LPStr)] String call_id, [MarshalAs(UnmanagedType.LPStr)] String endpoint_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static CallProgress_t Call_Endpoint_State([MarshalAs(UnmanagedType.LPStr)] String call_id, [MarshalAs(UnmanagedType.LPStr)] String ep_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Call_Invitation_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Call_Invitation_First([MarshalAs(UnmanagedType.LPStruct)] CallInvitation_t invite);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Call_Invitation_Next([MarshalAs(UnmanagedType.LPStruct)] CallInvitation_t invite);
        
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_Progress([MarshalAs(UnmanagedType.LPStr)] String call_id, CallProgress_t call_state);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Call_Leave([MarshalAs(UnmanagedType.LPStr)] String call_id, CallLeave_t leave_reason);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Phone_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static float Phone_Volume();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Phone_SetVolume(float volume);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Phone_SetCall([MarshalAs(UnmanagedType.LPStr)] String call_id);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Voisus_ConnectCloud([MarshalAs(UnmanagedType.LPStr)] String cloud_id);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Cloud_GetLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Cloud_ReleaseLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Cloud_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Cloud_Version();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Cloud_GetServerCount([MarshalAs(UnmanagedType.LPStr)] String uuid);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Operator_GetLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void Operator_ReleaseLock();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Operator_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Operator_Version();

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int RadCtrl_ListCount();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int RadCtrl_ErrorVersion();
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void RadCtrl_Poll([MarshalAs(UnmanagedType.LPStr)] String name);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static int RadCtrl_GetValueInt ([MarshalAs(UnmanagedType.LPStr)] String name, [MarshalAs(UnmanagedType.LPStr)] String setting);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void RadCtrl_SetValueStr ([MarshalAs(UnmanagedType.LPStr)] String name, [MarshalAs(UnmanagedType.LPStr)] String setting, [MarshalAs(UnmanagedType.LPStr)] String value);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void RadCtrl_SetValueInt ([MarshalAs(UnmanagedType.LPStr)] String name, [MarshalAs(UnmanagedType.LPStr)] String setting, int value);

        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void DIS_SetParams ([MarshalAs(UnmanagedType.LPStruct)] DISParams_t dis_params);
        [DllImport("VRCClient.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static void DIS_GetParams ([MarshalAs(UnmanagedType.LPStruct)] DISParams_t dis_params);

        #endregion public

        #region redefinitions
        /* Safe public alternatives to the unsafe private functions */

        public static void VRCC_Start()
        {
            IntPtr argv = IntPtr.Zero;
            if (VRCC_Start(0, ref argv) == 0)
                throw new VRCCException("VoisusMain.exe failed to start - verify that it's been installed correctly.");
        }

        public static String Voisus_LogPath()
        {
            unsafe { return new String(Voisus_LogPath_Unsafe()); }
        }

        public static String Voisus_ClientBuildVersion()
        {
            unsafe { return new String(Voisus_ClientBuildVersion_Unsafe()); }
        }

        public static String Voisus_ClientMsgVersion()
        {
        unsafe { return new String(Voisus_ClientMsgVersion_Unsafe()); }
        }

        public static String Voisus_ClientMsgDate()
        {
        unsafe { return new String(Voisus_ClientMsgDate_Unsafe()); }
        }

        public static String Voisus_ServerBuildVersion()
        {
        unsafe { return new String(Voisus_ServerBuildVersion_Unsafe()); }
        }

        public static String Voisus_ServerMsgVersion()
        {
        unsafe { return new String(Voisus_ServerMsgVersion_Unsafe()); }
        }

        public static String Voisus_ServerMsgDate()
        {
            unsafe { return new String(Voisus_ServerMsgDate_Unsafe()); }
        }

        public static String Network_ClientIP()
        {
            unsafe { return new String(Network_ClientIP_Unsafe()); }
        }

        public static String Network_ClientName()
        {
            unsafe { return new String(Network_ClientName_Unsafe()); }
        }

        public static String Network_OperatorId()
        {
            unsafe { return new String(Network_OperatorId_Unsafe()); }
        }

        public static String Network_TargetIP()
        {
            unsafe { return new String(Network_TargetIP_Unsafe()); }
        }

        public static String Role_Name(int list_index)
        {
            unsafe { return new String(Role_Name_Unsafe(list_index)); }
        }
  
        public static String Role_Id(int list_index)
        {
            unsafe { return new String(Role_Id_Unsafe(list_index)); }
        }
    
        public static String Role_NameActive()
        {
            unsafe { return new String(Role_NameActive_Unsafe()); }
        }
      
        public static String Role_IdActive()
        {
            unsafe { return new String(Role_IdActive_Unsafe()); }
        }
       
        public static String Role_NameSet()
        {
            unsafe { return new String(Role_NameSet_Unsafe()); }
        }
       
        public static String Role_IdSet()
        {
            unsafe { return new String(Role_IdSet_Unsafe()); }
        }
        
        public static String EntityState_Id(int list_index)
        {
            unsafe { return new String(EntityState_Id_Unsafe(list_index)); }
        }
       
        public static String EntityState_Name(int list_index)
        {
            unsafe { return new String(EntityState_Name_Unsafe(list_index)); }
        }

        public static String EntityState_NameActive()
        {
            unsafe { return new String(EntityState_NameActive_Unsafe()); }
        }
       
        public static String EntityState_IdActive()  
        {
            unsafe { return new String(EntityState_IdActive_Unsafe()); }
        }
        
        public static String  EntityState_NameSet() 
        {
            unsafe { return new String(EntityState_NameSet_Unsafe()); }
        }

        public static String EntityState_IdSet()            
        {
            unsafe { return new String(EntityState_IdSet_Unsafe()); }
        }

        public static String Radio_NetName (int radio_index, int net_index)
        {
            unsafe { return new String(Radio_NetName_Unsafe(radio_index, net_index)); }
        }

        public static String Radio_NetNameActive (int radio_index)
        {
            unsafe { return new String(Radio_NetNameActive_Unsafe(radio_index)); }
        }

        public static String Radio_NetID (int radio_index, int net_index)
        {
            unsafe { return new String(Radio_NetID_Unsafe(radio_index, net_index)); }
        }

        public static String  Radio_NetWaveform (int radio_index, int net_index)
        {
            unsafe { return new String(Radio_NetWaveform_Unsafe(radio_index, net_index));}
        }

        public static String Radio_NetIDActive (int radio_index)
        {
            unsafe { return new String(Radio_NetIDActive_Unsafe(radio_index)); }
        }

        public static String Radio_Type (int radio_index)
        {
            unsafe { return new String(Radio_Type_Unsafe(radio_index)); }
        }

        public static String Joystick_Name(int list_index)
        {
            unsafe { return new String(Joystick_Name_Unsafe(list_index)); }
        }

        public static String Call_IDFirst()        
        {
            unsafe { return new String(Call_IDFirst_Unsafe()); }
        }

        public static String Call_IDNext()       
        {
            unsafe { return new String(Call_IDNext_Unsafe()); }
        }

        public static String Call_Endpoint_IDFirst(String call_id)        
        {
            unsafe { return new String(Call_Endpoint_IDFirst_Unsafe(call_id)); }
        }

        public static String Call_Endpoint_IDNext(String call_id)
        {
            unsafe { return new String(Call_Endpoint_IDNext_Unsafe(call_id)); }
        }
        public static String Phone_CallActive()        
        {
            unsafe { return new String(Phone_CallActive_Unsafe()); }
        }
        public static String Network_CloudSet()       
        {
            unsafe { return new String(Network_CloudSet_Unsafe()); }
        }
        public static String Network_CloudActive()      
        {
            unsafe { return new String(Network_CloudActive_Unsafe()); }
        }
        public static String Cloud_IDFirst()       
        {
            unsafe { return new String(Cloud_IDFirst_Unsafe()); }
        }
        public static String Cloud_IDNext()     
        {
            unsafe { return new String(Cloud_IDNext_Unsafe()); }
        }

        public static String Operator_IDFirst()      
        {
            unsafe { return new String(Operator_IDFirst_Unsafe()); }
        }
        public static String Operator_IDNext()
        {
            unsafe { return new String(Operator_IDNext_Unsafe()); }
        }

        public static String Operator_GetField(String uuid, String field_name)   
        {
            unsafe { return new String(Operator_GetField_Unsafe(uuid, field_name)); }
        }

        public static String RadCtrl_GetValueStr(String name, String setting)      
        {
            unsafe { return new String(RadCtrl_GetValueStr_Unsafe(name, setting)); }
        }

        public static String RadCtrl_GetOptionsStr(String name, String setting)        {
            unsafe { return new String(RadCtrl_GetOptionsStr_Unsafe(name, setting)); }
        }
        public static String RadCtrl_Error()         
        {
            unsafe { return new String(RadCtrl_Error_Unsafe()); }
        }
        public static String RadCtrl_Name(int index)
        {
            unsafe { return new String(RadCtrl_Name_Unsafe(index)); }
        }
        #endregion redefinitions
        
        #region alternate versions

        /* Functions not specified in the VRCC that would make sense to have in C# */

        public static Boolean Role_AutotuneEnabled_Bool(String role_id)
        {
            return Role_AutotuneEnabled(role_id) == 1;
        }

        public static Boolean Role_RadCtrlEnabled_Bool(String role_id)
        {
            return Role_RadCtrlEnabled(role_id) == 1;
        }

        public static Boolean Role_CallingEnabled_Bool(String role_id)
        {
            return Role_CallingEnabled(role_id) == 1;
        }

        public static Boolean Role_ChatEnabled_Bool(String role_id)
        {
            return Role_ChatEnabled(role_id) == 1;
        }

        public static Boolean Headset_HasSidetone_Bool()
        {
            return Headset_HasSidetone() == 1;
        }

        public static Boolean PTT_GetPressed_Multi_Bool(int ptt)
        {
            return PTT_GetPressed_Multi(ptt) == 1;
        }

        public static Boolean PTT_GetPressed_Bool()
        {
            return PTT_GetPressed() == 1;
        }

        public static Boolean PTT_HWGetPressed_Multi_Bool(int ptt)
        {
            return PTT_HWGetPressed_Multi(ptt) == 1;
        }

        public static Boolean PTT_HWGetPressed_Bool()
        {
            return PTT_HWGetPressed() == 1;
        }

        public static Boolean Radio_IsReceiveEnabled_Bool(int radio_index)
        {
            return Radio_IsReceiveEnabled(radio_index) == 1;
        }

        public static Boolean Radio_IsTransmitEnabled_Bool(int radio_index)
        {
            return Radio_IsTransmitEnabled(radio_index) == 1;
        }

        public static Boolean Radio_IsReceiving_Bool(int radio_index)
        {
            return Radio_IsReceiving(radio_index) == 1;
        }

        public static Boolean Radio_IsTransmitting_Bool(int radio_index)
        {
            return Radio_IsTransmitting(radio_index) == 1;
        }

        public static Boolean Radio_IsShared_Bool(int radio_index)
        {
            return Radio_IsShared(radio_index) == 1;
        }

        public static Boolean Radio_IsNetLocked_Bool(int radio_index)
        {
            return Radio_IsNetLocked(radio_index) == 1;
        }

        public static Boolean Radio_IsRXModeLocked_Bool(int radio_index)
        {
            return Radio_IsRXModeLocked(radio_index) == 1;
        }

        public static Boolean Radio_CryptoEnabled_Bool(int radio_index)
        {
            return Radio_CryptoEnabled(radio_index) == 1;
        }

        public static Boolean Earshot_Receiving_Bool()
        {
            return Earshot_Receiving() == 1;
        }
        
        public static Boolean Earshot_Transmitting_Bool()
        {
            return Earshot_Transmitting() == 1;
        }

        public static Boolean Joystick_Pressed_Multi_Bool(int ptt)
        {
            return Joystick_Pressed_Multi(ptt) == 1;
        }
        public static Boolean Joystick_Pressed_Bool()
        {
            return Joystick_Pressed() == 1;
        }

        #endregion alternate versions
    }
}

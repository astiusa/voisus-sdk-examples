/*
 *  Voisus SDK Example Application
 *  Copyright 2017 Advanced Simulation Technology, inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "vrcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <io.h>
    #include <winsock2.h>
#else
    #include <unistd.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

int Current_radio;
int Current_jammer;

void connect(void);
void disconnect(void);
void help(void);
void get_radio(void);
void get_jammer(void);
void get_radio_nets(void);
void get_jammer_nets(void);
void get_radios(void);
void get_jammers(void);
void get_roles(void);
void set_client_name(void);
void set_ptt(void);
void set_radio(void);
void set_jammer(void);
void set_radio_net(void);
void set_jammer_net(void);
void set_role(void);
void set_jammer_enable(void);
void set_rx_enable(void);
void set_tx_enable(void);
void jammer_set_enable(void);
void jammer_start_recording(void);
void jammer_start_replaying(void);
void jammer_stop_recording(void);
void jammer_stop_replaying(void);
void quit_app(void);
void status(void);

typedef void (*samplefunc)();

typedef struct {
    const char* name;
    const char* desc;
    samplefunc func;
} COMMAND_T;

COMMAND_T Commands[] = {{"connect", "Connect to server", connect},
                        {"disconnect", "Disconnect from server", disconnect},
                        {"help", "Print the command descriptions", help},
                        {"get_radio", "Get current radio info", get_radio},
                        {"get_jammer", "Get current jammer info", get_jammer},
                        {"get_radio_nets", "Get nets assigned to current radio", get_radio_nets},
                        {"get_jammer_nets", "Get nets assigned to current jammer", get_jammer_nets},
                        {"get_radios", "Get info on all radios", get_radios},
                        {"get_jammers", "Get info on all jammers", get_jammers},
                        {"get_roles", "Get list of roles", get_roles},
                        {"set_client_name", "Set client name", set_client_name},
                        {"set_ptt", "Set PTT state (pressed or released)", set_ptt},
                        {"set_radio", "Set the current radio by index", set_radio},
                        {"set_jammer", "Set the current jammer by index", set_jammer},
                        {"set_radio_net", "Set the net for a radio by index", set_radio_net},
                        {"set_jammer_net", "Set the net for a jammer by index", set_jammer_net},
                        {"set_role", "Set the role to use", set_role},
                        {"set_jammer_enable", "Set transmit enable for current jammer", set_jammer_enable},
                        {"set_rx_enable", "Set receive enable for current radio", set_rx_enable},
                        {"set_tx_enable", "Set transmit enable for current radio", set_tx_enable},
                        {"jammer_start_recording", "Begin recording on current jammer", jammer_start_recording},
                        {"jammer_start_replaying", "Begin replaying on current jammer", jammer_start_replaying},
                        {"jammer_stop_recording", "Stop recording on current jammer", jammer_stop_recording},
                        {"jammer_stop_replaying", "Stop replaying on current jammer", jammer_stop_replaying},
                        {"quit", "Quit the application", quit_app},
                        {"status", "Get the current status", status},
                        {NULL, NULL, NULL}};

///////////////////////////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////////////////////////

void my_sleep(unsigned int ms)
{
#ifdef WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

size_t get_input(char* buf, size_t bufsz)
{
    int sz = 0;
    while (1)
    {   sz = read(fileno(stdin), buf, bufsz);
        if (-1 != sz)
        {   buf[sz-1] = '\0';
            return sz;
        }
    }
    return 0;
}

void check_server(void)
{
    if (TARGET_CONNECT == Network_ConnectState())
        printf("WARNING: Not connected to server.\n");
}

void check_connected(void)
{
    if (ROLE_CONNECTED != Network_ConnectState())
        printf("WARNING: Not connected to role.\n");
}

void execute(const char* buf)
{
    static char Last_cmd[1024];
    COMMAND_T* cmd = Commands;
    if ((0 == strlen(buf)) && (strlen(Last_cmd)))
        buf = Last_cmd;
    while (cmd->name)
    {   if (0 == strcmp(cmd->name, buf))
        {   check_server();
            check_connected();
            cmd->func();
            sprintf(Last_cmd, cmd->name);
            return;
        }
        ++cmd;
    }
    printf("Unknown command. Type help to see available commands.");
}

void print_radio(int idx)
{
    printf("Radio index %d:%s\n"
           "    Active Net: %s\n"
           "    Transmit Enabled: %s\n"
           "    Receive Enabled: %s\n"
           "    Receiving: %s\n"
           "    Transmitting: %s\n",
           idx,
           (idx == Current_radio) ? " (*** Current ***)" : "",
           Radio_NetNameActive(idx),
           Radio_IsTransmitEnabled(idx) ? "true" : "false",
           Radio_IsReceiveEnabled(idx) ? "true" : "false",
           Radio_IsReceiving(idx) ? "true" : "false",
           Radio_IsTransmitting(idx) ? "true" : "false");
}

const char* jammer_state(int state)
{
    switch (state)
    {   case JAMMER_STATE_INIT:
            return "Jammer Initialized";
        case JAMMER_STATE_WAITING:
            return "Jammer Waiting For Audio";
        case JAMMER_STATE_RECORDING:
            return "Jammer Recording Audio";
        case JAMMER_STATE_REPLAYING:
            return "Jammer Replaying Audio";
        case JAMMER_STATE_IDLE:
            return "Jammer Ready With Audio";
        default:
            return NULL;
    }
}

void print_jammer(int idx)
{
    int active_net_idx;
    for (active_net_idx = 0; active_net_idx < Jammer_NetListCount(Current_jammer); active_net_idx++)
    {   if (!strcmp(Jammer_NetID(Current_jammer, active_net_idx), Jammer_NetIDActive(Current_jammer)))
            break;
    }
    printf("Jammer index %d:%s\n"
           "    Active Net Name: %s\n"
           "    Transmitting: %s\n"
           "    Record/Replay State: %s\n"
           "    Replay Progress: %d%%\n"
           "    Replay Duration: %d ms\n",
           idx,
           (idx == Current_jammer) ? "(*** Current ***)" : "",
           Jammer_NetName(Current_jammer, active_net_idx),
           Jammer_IsTransmitting(idx) ? "true":"false",
           jammer_state(Jammer_RecordReplayState(idx)),
           Jammer_RecordReplayProgress(idx),
           Jammer_RecordReplayDurationMs(idx));
}

///////////////////////////////////////////////////////////////////////////////
// Commands
///////////////////////////////////////////////////////////////////////////////

void connect(void)
{
    char ip[32];
    printf("Enter IP address of server: ");
    fflush(stdout);
    get_input(ip, sizeof(ip));
    Voisus_ConnectServer(ip);
}

void disconnect(void)
{
    Voisus_Disconnect();
}

void help(void)
{
    COMMAND_T* cmd = Commands;
    while (cmd->name)
    {   printf("%-20s %s\n", cmd->name, cmd->desc);
        cmd++;
    }
}

void get_radio(void)
{
    if (Current_radio < Radio_ListCount())
        print_radio(Current_radio);
}

void get_jammer(void)
{
    if (Current_jammer < Jammer_ListCount())
        print_jammer(Current_jammer);
}

void get_radio_nets(void)
{
    printf("Nets assigned to Radio %d:\n", Current_radio);
    for (int i = 0; i < Radio_NetListCount(Current_radio); i++)
    {   int current_net = !strcmp(Radio_NetID(Current_radio, i),
                                  Radio_NetIDActive(Current_radio));
        printf("Net index %d:%s\n"
               "    Name: %s\n"
               "    Frequency: %llu Hz\n"
               "    Waveform: %s\n"
               "    Crypto enabled: %s\n",
               i,
               current_net ? " (*** Current ***)" : "",
               Radio_NetName(Current_radio, i),
               Radio_NetFrequency(Current_radio, i),
               Radio_NetWaveform(Current_radio, i),
               Radio_NetCryptoEnabled(Current_radio, i) ? "true" : "false");
    }
}

void get_jammer_nets(void)
{
    printf("Nets assigned to Jammer %d:\n", Current_jammer);
    for (int i = 0; i < Jammer_NetListCount(Current_jammer); i++)
    {   int current_net = !strcmp(Jammer_NetID(Current_jammer, i),
                                  Jammer_NetIDActive(Current_jammer));
        printf("Net index %d:%s\n"
               "    Name: %s\n"
               "    Net ID: %s\n",
               i,
               current_net ? " (*** Current ***)" : "",
               Jammer_NetName(Current_jammer, i),
               Jammer_NetID(Current_jammer, i)
               );
    }
}

void get_radios(void)
{
    for (int i = 0; i < Radio_ListCount(); i++)
        print_radio(i);
}

void get_jammers(void)
{
    for (int i = 0; i < Jammer_ListCount(); i++)
        print_jammer(i);
}

void get_roles(void)
{
    for (int i = 0; i < Role_ListCount(); i++)
        printf("    Role %d:\t%s\n", i, Role_Name(i));
}

void set_client_name(void)
{
    char name[32];
    printf("Enter client name: ");
    fflush(stdout);
    get_input(name, sizeof(name));
    Network_SetClientName(name);
}

void set_ptt(void)
{
    printf("Setting Push-To-Talk state to %s.\n",
           PTT_GetPressed() ? "Released" : "Pressed");
    PTT_SetPressed(!PTT_GetPressed());
}

void set_radio(void)
{
    char idxstr[32];
    printf("Enter radio number (see: get_radios): ");
    fflush(stdout);
    get_input(idxstr, sizeof(idxstr));
    int idx = atoi(idxstr);
    if (idx < Radio_ListCount())
    {   Current_radio = idx;
        get_radios();
    }
    else
        printf("Bad radio index. Current radio index is %d.\n", Current_radio);
}

void set_jammer(void)
{
    char idxstr[32];
    printf("Enter jammer number (see: get_jammers): ");
    fflush(stdout);
    get_input(idxstr, sizeof(idxstr));
    int idx = atoi(idxstr);
    if (idx < Jammer_ListCount())
    {   Current_jammer = idx;
        get_jammers();
    }
    else
        printf("Bad jammer index. Current jammer index is %d.\n", Current_jammer);
}

void set_radio_net(void)
{
    char idxstr[32];
    if (0 == Radio_ListCount())
    {   printf("No radios.");
        return;
    }
    printf("Enter net number (see: get_radio_nets): ");
    fflush(stdout);
    get_input(idxstr, sizeof(idxstr));
    int idx = atoi(idxstr);
    if (idx < Radio_NetListCount(Current_radio))
        Radio_SetNet(Current_radio, idx);
    else
        printf("Bad net index.\n");
}

void set_jammer_net(void)
{
    char idxstr[32];
    if (0 == Jammer_ListCount())
    {   printf("No jammers.");
        return;
    }
    printf("Enter net number (see: get_jammer_nets): ");
    fflush(stdout);
    get_input(idxstr, sizeof(idxstr));
    int idx = atoi(idxstr);
    if (idx < Jammer_NetListCount(Current_jammer))
    {   const char* netID = Jammer_NetID(Current_jammer, idx);
        Jammer_SetNetID(Current_jammer, netID);
    }
    else
        printf("Bad net index.\n");
}

void set_role(void)
{
    char idxstr[32];
    printf("Enter role number (see: get_roles): ");
    fflush(stdout);
    get_input(idxstr, sizeof(idxstr));
    int idx = atoi(idxstr);
    const char* role_id = Role_Id(idx);
    if (strlen(role_id))
    {   Role_SetRole(role_id);
        printf("Set role to %s.\n", Role_Name(idx));
    }
    else
        printf("Unknown role.\n");
}

void set_jammer_enable(void)
{
    char enablestr[32];
    printf("Enter 'enable' to enable the selected jammer, or 'disable' to disable the selected jammer: ");
    fflush(stdout);
    get_input(enablestr, sizeof(enablestr));
    if (0 == strcmp(enablestr, "enable"))
    {   Jammer_SetEnable(Current_jammer, 1);
        printf("Jammer %d enabled\n", Current_jammer);
    }
    else if (0 == strcmp(enablestr, "disable"))
    {   Jammer_SetEnable(Current_jammer, 0);
        printf("Jammer %d disabled\n", Current_jammer);
    }else
        printf("Invalid entry\n");
}


void set_rx_enable(void)
{
    if (Current_radio >= Radio_ListCount())
        return;
    printf("Setting Receive Enable of Radio %d to %s.\n",
           Current_radio,
           Radio_IsReceiveEnabled(Current_radio) ? "Disabled" : "Enabled");
    Radio_SetReceiveEnabled(Current_radio,
                            !Radio_IsReceiveEnabled(Current_radio));
}

void set_tx_enable(void)
{
    if (Current_radio >= Radio_ListCount())
        return;
    printf("Setting Transmit Enable of Radio %d to %s.\n",
           Current_radio,
           Radio_IsTransmitEnabled(Current_radio) ? "Disabled" : "Enabled");
    Radio_SetTransmitEnabled(Current_radio,
                             !Radio_IsTransmitEnabled(Current_radio));
}

void jammer_start_recording(void)
{
    printf("Enter how long (in seconds) you'd like to record.(Max 30 Seconds): ");
    char timestr[32];
    fflush(stdout);
    get_input(timestr, sizeof(timestr));
    int time = atoi(timestr);
    if (time > 30 || time < 0)
    {   printf("Invalid entry\n");
        return;
    }
    Jammer_StartRecording(Current_jammer, time);
}

void jammer_stop_recording(void)
{
    Jammer_StopRecording(Current_jammer);
}

void jammer_start_replaying(void)
{
    printf("Enter 'loop' to loop recording, or 'play' to play normally: ");
    char optstr[32];
    fflush(stdout);
    get_input(optstr, sizeof(optstr));
    if (0 == strcmp(optstr, "loop"))
        Jammer_StartReplaying(Current_jammer, 1);
    else if (0 == strcmp(optstr, "play"))
        Jammer_StartReplaying(Current_jammer, 0);
    else
        printf("Invalid entry\n");
}

void jammer_stop_replaying(void)
{
    Jammer_StopReplaying(Current_jammer);
}

void quit_app(void)
{
    VRCC_Shutdown();
    exit(0);
}

void status(void)
{
    printf("Voisus Server IP Address: %s\n"
           "Client Name: %s\n"
           "Connection State: %d\n"
           "Connection Status: %s\n"
           "Role: %s\n",
           Network_TargetIP(),
           Network_ClientName(),
           Network_ConnectState(),
           Network_ConnectionStatus() == STATUS_CONNECTED ? "Connected" : "Disconnected",
           Role_NameActive());
}

int input_available()
{
#ifndef WIN32
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(0, &fds);
#else
    HANDLE eventHandles[] = {GetStdHandle(STD_INPUT_HANDLE)};
    DWORD result = WSAWaitForMultipleEvents(1, eventHandles, FALSE, 0, TRUE);
    switch (result)
    {   case WSA_WAIT_EVENT_0:  // event on stdin
            return 1;
        case WSA_WAIT_TIMEOUT:  // no events
        default:
            break;
    };
#endif
    return 0;
}

void init(void)
{
#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,0), &wsadata);
#endif
}

int main(int argc, char* argv[])
{
    init();
    printf("VRCC C/C++ Library Sample Application\n\n");
    printf("Type help to see available commands.\n\n");

    VRCC_Start(argc, argv);

    char cmd[1024];
    printf("> ");
    fflush(stdout);
    while(1)
    {   if (input_available())
        {   get_input(cmd, sizeof(cmd));
            execute(cmd);
            printf("\n> ");
            fflush(stdout);
        }
        else
        {   VRCC_Update(); // Must be called periodically to get updates
            my_sleep(50);
        }
    }

    return 0;
}
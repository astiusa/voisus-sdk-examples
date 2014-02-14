using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using VoisusCS;

/*
 * Simple console application for testing the VRCC C# wrapper
 * 
 * Commands take the format <function><whitespace><argument>
 * 
 * Type get_help at the prompt to see possible commands
 * 
 * This class uses a delegate to programmatically pass off control to the function
 * specified at the command line.  To add a command, just define a public static function
 * that takes a String argument.  The name of the function will become the name of the command.
 */
namespace ConsoleApplication
{
    class Program
    {
        static int currentRadio;

        #region VRCC commands

        public static void connect(String IPAddress)
        {
            if (IPAddress == null || IPAddress == "")
            {
                Console.WriteLine("Connect to what IP adress?");
                Console.WriteLine();
                Console.Write("> ");
                IPAddress = Console.ReadLine();
            }
            VRCC.Voisus_ConnectServer(IPAddress);
            Console.WriteLine("Connecting to " + IPAddress);
        }

        public static void disconnect(String parameters)
        {
            VRCC.Voisus_Disconnect();
            Console.WriteLine("Disconnecting");
        }

        public static void get_roles(String parameters)
        {
            Console.WriteLine("Available Roles: ");
            for (int i = 0; i < VRCC.Role_ListCount(); ++i)
            {
                Console.WriteLine("Index " + i + ": " + VRCC.Role_Name(i));
            }
        }

        public static void set_role(String role_index)
        {
            if (role_index == null || role_index == "")
            {
                Console.WriteLine("Specify a role by its Index:");
                Console.WriteLine();
                get_roles(null);
                Console.WriteLine();
                Console.Write("> ");
                role_index = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(role_index);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be an integer corresponding to a Role Index");
                return;
            }
            String roleID = VRCC.Role_Id(index);
            VRCC.Role_SetRole(roleID);
            Console.WriteLine("RoleID = " + roleID);
            Console.WriteLine("Assigning to role " + VRCC.Role_Name(Convert.ToInt32(role_index)));
        }

        public static void get_vehicles(String parameters)
        {
            for(int i = 0; i < VRCC.EntityState_ListCount(); ++i)
            {
                Console.Write("Vehicle Index: " + i);
                Console.Write(" Name: " + VRCC.EntityState_Name(i));
                Console.WriteLine();
            }
        }

        public static void set_vehicle(String vehicle_index)
        {
            if (vehicle_index == null || vehicle_index == "")
            {
                Console.WriteLine("Specify a vehicle by its Index:");
                Console.WriteLine();
                get_vehicles(null);
                Console.WriteLine();
                Console.Write("> ");
                vehicle_index = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(vehicle_index);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be an integer corresponding to a Vehicle Index");
                return;
            }
            String vehicleID = VRCC.EntityState_Id(index);
            VRCC.EntityState_SetEntityState(vehicleID);
            Console.WriteLine("VehicleID = " + vehicleID);
            Console.WriteLine("Assigning to vehicle " + VRCC.EntityState_Name(index));
        }

        public static void get_radios(String parameters)
        {
            Console.WriteLine("\"Current\" Radio Index: " + currentRadio);
            for (int i = 0; i < VRCC.Radio_ListCount(); ++i)
            {
                Console.Write("Radio Index " + i + ": ");
                Console.Write(" Active Net: " + VRCC.Radio_NetNameActive(i));
                Console.Write(" Transmit Enabled: " + Convert.ToBoolean(VRCC.Radio_IsTransmitEnabled(i)));
                Console.Write(" Receive Enabled: " + Convert.ToBoolean(VRCC.Radio_IsReceiveEnabled(i)));
                Console.WriteLine();
            }
        }

        public static void cycle_radio(String parameters)
        {
            ++currentRadio;
            if (currentRadio > VRCC.Radio_ListCount()) currentRadio = 0;
            Console.WriteLine("\"Current\" Radio Index: " + currentRadio);
            Console.Write(" Active Net: " + VRCC.Radio_NetNameActive(currentRadio));
            Console.Write(" Transmit Enabled: " + Convert.ToBoolean(VRCC.Radio_IsTransmitEnabled(currentRadio)));
            Console.Write(" Receive Enabled: " + Convert.ToBoolean(VRCC.Radio_IsReceiveEnabled(currentRadio)));
            Console.WriteLine();
        }

        public static void get_nets(String parameters)
        {
            Console.WriteLine("Available Nets on Radio " + currentRadio + " :");
            for(int i = 0; i < VRCC.Radio_NetListCount(currentRadio); ++i)
            {
                Console.WriteLine(VRCC.Radio_NetRxFrequencyActive(currentRadio));
                Console.Write("Net Index " + i + ": " + VRCC.Radio_NetName(currentRadio, i));
                Console.Write(" Freq: " + VRCC.Radio_NetFrequency(currentRadio, i));
                Console.Write(" Waveform: " + VRCC.Radio_NetWaveform(currentRadio, i));
                Console.Write(" Crypto : " + Convert.ToBoolean(VRCC.Radio_NetCryptoEnabled(currentRadio, i)));
                Console.WriteLine();
            }
        }

        public static void set_net(String net_index)
        {
            if (net_index == null || net_index == "")
            {
                Console.WriteLine("Specify a net by its Index:");
                Console.WriteLine();
                get_nets(null);
                Console.WriteLine();
                Console.Write("> ");
                net_index = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(net_index);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be an integer corresponding to a Net Index");
                return;
            }
            VRCC.Radio_SetNet(currentRadio, index);
            Console.WriteLine("\"Current\" Radio Index: " + currentRadio);
            Console.WriteLine("Net ID: " + VRCC.Radio_NetID(currentRadio, index));
            Console.Write(" Active Net: " + VRCC.Radio_NetNameActive(currentRadio));
        }

        public static void get_stats(String parameters)
        {
            Console.WriteLine("Voisus Server: " + VRCC.Network_TargetIP());
            Console.WriteLine("Client Name: " + VRCC.Network_ClientName());
            Console.WriteLine("Connection State: " + VRCC.Network_ConnectState());
            Console.WriteLine("Connection Status: " + VRCC.Network_ConnectionStatus());
            Console.WriteLine("Role: " + VRCC.Role_NameActive());
            Console.WriteLine("Vehicle: " + VRCC.EntityState_NameActive());
        }

        public static void set_clientname(String name)
        {
            VRCC.Network_SetClientName(name);
            Console.WriteLine("Client name: " + name);
        }

        public static void get_operators(String parameters)
        {
            String opID = VRCC.Operator_IDFirst();
            Console.WriteLine(VRCC.Operator_ListCount());
            for (int i = 0; i < VRCC.Operator_ListCount(); ++i)
            {
                Console.Write("Operator " + i + ": ");
                Console.Write("Name: " + VRCC.Operator_GetField(opID, "clientname"));
                Console.Write(" Role: " + VRCC.Operator_GetField(opID, "name"));
                Console.Write(" IP Address: " + VRCC.Operator_GetField(opID, "clientaddress"));
                opID = VRCC.Operator_IDNext();
            }
        }

        public static void get_receive(String parameters)
        {
            if (!VRCC.Radio_IsReceiveEnabled_Bool(currentRadio))
            {
                Console.Write("Not ");
            }
            Console.WriteLine("Receiving");
        }

        public static void set_receive(String int_enabled)
        {
            if (int_enabled == null || int_enabled == "")
            {
                Console.WriteLine("Specify a receive enable mode for the current radio (1 for enabled 0 for not enabled)");
                Console.WriteLine();

                Console.Write("> ");
                int_enabled = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(int_enabled);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be either 1 or 0");
                return;
            }
            VRCC.Radio_SetReceiveEnabled(currentRadio, index);
            Console.WriteLine("Receiving: " + Convert.ToBoolean(index));
        }

        public static void get_transmit(String parameters)
        {
            if (!VRCC.Radio_IsTransmitEnabled_Bool(currentRadio))
            {
                Console.Write("Not ");
            }
            Console.WriteLine("Transmitting");
        }

        public static void set_transmit(String int_enabled)
        {
            if (int_enabled == null || int_enabled == "")
            {
                Console.WriteLine("Specify a transmit enable mode for the current radio (1 for enabled 0 for not enabled)");
                Console.WriteLine();

                Console.Write("> ");
                int_enabled = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(int_enabled);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be either 1 or 0");
                return;
            }
            VRCC.Radio_SetTransmitEnabled(currentRadio, index);
            Console.WriteLine("Transmitting: " + Convert.ToBoolean(index));
        }

        public static void get_micmode(String parameters)
        {
            Console.WriteLine("Mic mode: " + VRCC.Headset_MicrophoneMode());
        }

        public static void set_micmode(String int_mode)
        {
            if (int_mode == null || int_mode == "")
            {
                Console.WriteLine("Specify a mic mode by its Index:");
                Console.WriteLine();
                for (int i = 0; i < (Enum.GetNames(typeof(MicMode_t))).Length; ++i)
                {
                    Console.WriteLine("Index " + i + ": " + (MicMode_t)i);
                }
                Console.WriteLine();
                Console.Write("> ");
                int_mode = Console.ReadLine();
            }
            Int32 index = new Int32();
            try
            {
                index = Convert.ToInt32(int_mode);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be an integer corresponding to a Mic Mode");
                return;
            }
            VRCC.Headset_SetMicrophoneMode((MicMode_t)index);
            Console.WriteLine("Setting mic mode: " + (MicMode_t)index);
        }

        public static void set_ptt(String bool_push)
        {
            if (bool_push == null || bool_push == "")
            {
                Console.WriteLine("Specify a push to talk button state (true for pushed false for released):");
                Console.WriteLine();
            }

            Boolean push = new Boolean();

            try
            {
                push = Convert.ToBoolean(bool_push);
            }
            catch (System.FormatException)
            {
                Console.WriteLine("Invalid argument: must be value 1, 0, true, or false");
                Console.WriteLine();
            }

            VRCC.PTT_SetPressed(push);

            Console.WriteLine("Setting push to talk: " + push);
        }

        #endregion VRCC commands

        public static void get_help(String parameters)
        {
            Console.WriteLine("Available commands: ");
            Console.WriteLine();
            for (int i = 0; i < methodInfos.Length - 4; ++i)
            {
                Console.Write(methodInfos[i].Name);
                ParameterInfo[] paramInfos = methodInfos[i].GetParameters();
                if (paramInfos[0].Name == "parameters")
                {
                    Console.Write(", ");
                    continue;
                }
                Console.Write(": [" + paramInfos[0].Name + "], ");
            }
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("If you're not sure what argument to supply to a command, call it with no arguments to receive usage info");
        }

        
        delegate void command(String parameters = null);

        static MethodInfo[] methodInfos = typeof(Program).GetMethods();
        
        static void execute(String input)
        {
            String[] split = input.Split(" ".ToCharArray(), 2);
            String method = split[0];
            String args = null;
            if (split.Length > 1)
            {
                args = split[1];
            }
            for (int i = 0; i < methodInfos.Length; ++i)
            {
                if (methodInfos[i].Name == method)
                {

                    Delegate del = Delegate.CreateDelegate(typeof(command), methodInfos[i]);
                    del.DynamicInvoke(args);
                }
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Working Directory: " + System.IO.Directory.GetCurrentDirectory());
            
            Console.WriteLine("Voisus Install Directory: " + VRCC.VoisusInstallDir);
            
            Console.WriteLine("VRCC C# Library Test");
            Console.WriteLine();
            Console.WriteLine("Type get_help to see available commands.");
            VRCC.VRCC_Start();


            Console.WriteLine();
            Console.Write("> ");
            String input = "";
            while (true)
            {   if (Console.KeyAvailable)
                {   input = Console.ReadLine();
                    execute(input);
                    Console.WriteLine();
                    Console.Write("> ");
                }
                VRCC.VRCC_Update();
                System.Threading.Thread.Sleep(50);
            }
        }
    }
}

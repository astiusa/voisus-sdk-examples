using System;
using System.Runtime.InteropServices;

namespace VoisusCS
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct CallInvitation_t
    {
        [MarshalAs(UnmanagedType.LPStr)]
        String call_id;

        [MarshalAs(UnmanagedType.LPStr)]
        String endpoint_id;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct DISParams_t
    {
        int site;
        int app;
        int entity;
        int radio_offset;
        [MarshalAs(UnmanagedType.LPArray, SizeConst=32)]
        sbyte[] exercise_name;
    }
}
namespace VoisusCS
{
    public enum MicMode_t 
    {
        MIC_OFF,
        MIC_PTT,
        MIC_VOX, 
        MIC_HOT 
    };

    public enum ConnectionStatus_t 
    { 
        STATUS_NONE, 
        STATUS_DISCONNECTED,
        STATUS_CONNECTED 
    };

    public enum TestMode_t 
    { 
        TEST_OFF,
        TEST_WAVE, 
        TEST_SIDETONE, 
        TEST_LOOPBACK, 
        TEST_SEND_WAVE 
    };

    public enum Error_t 
    { 
        ERROR_OFF, 
        ERROR_CREDITS,
        ERROR_VOISUS,
        ERROR_AUTHORIZE
    };

    public enum HeadsetPreset_t 
    { 
        HEADSET_PRESET_CUSTOM,
        HEADSET_PRESET_ASTI, 
        HEADSET_PRESET_PLANT_DA40, 
        HEADSET_PRESET_PLANT_655, 
        HEADSET_PRESET_PLANT_P420 
    };

    public enum ChannelSelectMode_t 
    { 
        CHANNEL_SELECT_NONE, 
        CHANNEL_SELECT_NET,
        CHANNEL_SELECT_RADIO,
        CHANNEL_SELECT_RADIO_TXRX 
    };

    public enum ConnectionMode_t 
    { 
        CONNECT_MODE_NONE, 
        CONNECT_MODE_STANDALONE, 
        CONNECT_MODE_SERVER,
        CONNECT_MODE_CLOUD 
    };

    public enum ConnectState_t 
    { 
        TARGET_CONNECT, 
        ROLE_GET, 
        ROLES_RECEIVED, 
        ROLE_SET, 
        ROLE_CONNECT,
        ROLE_CONNECTED, 
        TARGET_AUTHORIZE 
    };

    public enum Codec_t 
    { 
        CODEC_16K_SPCM16 = 1,
        CODEC_8K_G711U = 4 
    };

    public enum Balance_t 
    { 
        BALANCE_LEFT = 1,
        BALANCE_RIGHT = 2,
        BALANCE_CENTER = 128 
    };

    public enum CallProgress_t
    { 
        CALL_STATE_NONE = 0, 
        CALL_STATE_LEAVING = 10, 
        CALL_STATE_CONNECTED = 20,
        CALL_STATE_SIGNALING = 30,
        CALL_STATE_HOLDING = 40 
    };

    public enum CallLeave_t
    { 
        CALL_LEAVE_UNSPECIFIED = 0, 
        CALL_LEAVE_REJECTED = 1, 
        CALL_LEAVE_BUSY = 2, 
        CALL_LEAVE_NO_ANSWER = 3, 
        CALL_LEAVE_HANG_UP = 4, 
        CALL_LEAVE_LOST_CONTACT = 5, 
        CALL_LEAVE_REDIRECT = 6
    };
}

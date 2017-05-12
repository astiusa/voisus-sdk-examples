//
//  Voisus Remote Control Client (VRCC) types
//
//  Copyright 2015 Advanced Simulation Technology, inc.

#ifndef VRC_TYPES_H
#define VRC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/// Client connection status
enum ConnectionStatus_t
{
    STATUS_NONE,                    ///< Client has not connected to a target
    STATUS_DISCONNECTED,            ///< Client has disconnected from a target
    STATUS_CONNECTED                ///< Client is currently connected to a target
};

/// Role connection states
enum ConnectState_t
{
    TARGET_CONNECT,                 ///< Connecting to Target
    ROLE_GET,                       ///< Connected to Target, requesting roles
    ROLES_RECEIVED,                 ///< Received roles
    ROLE_SET,                       ///< Sending role request
    ROLE_CONNECT,                   ///< Role request confirmed, Acquiring license for Operator
    ROLE_CONNECTED,                 ///< Connected to Operator
    TARGET_AUTHORIZE                ///< Authorizing with Target
};

/// DIS parameters
typedef struct
{
    int         site;               ///< DIS Site
    int         app;                ///< DIS Application
    int         entity;             ///< DIS Entity
    int         radio_offset;       ///< DIS Radio index for first radio
    char        exercise_name[32];  ///< Name of exercise (defined in Voisus)
} DISParams_t;

/// Call invitation
typedef struct
{
    const char* call_id;            ///< Unique ID of the call
    const char* endpoint_id;        ///< Unique ID of the endpoint to invite
} CallInvitation_t;

/// Audio Encoding
enum AudioEncoding_t
{
    AUDIO_ENCODING_MULAW = 1,       ///< 8-bit Mulaw (G.711) encoding
    AUDIO_ENCODING_SPCM16 = 4       ///< 16-bit Signed PCM encoding
};

/// Audio Balance
enum Balance_t
{
    BALANCE_LEFT = 1,               ///< Audio played on left
    BALANCE_RIGHT = 2,              ///< Audio played on right
    BALANCE_STEREO = 3,             ///< Audio played on left and right (stereo)
    BALANCE_CENTER = 128            ///< Audio played on center (mono)
};

/// Radio tuning methods
enum RadioTuningMethod_t
{
    RADIO_TUNE_FREQ_BW       = 1,   ///< Frequency and Bandwidth tuning
    RADIO_TUNE_FREQ          = 2,   ///< Frequency only tuning
    RADIO_TUNE_VOIP          = 3,   ///< VOIP tuning
    RADIO_TUNE_HQ            = 4,   ///< HaveQuick tuning
    RADIO_TUNE_SG            = 5,   ///< SINCGARS tuning
    RADIO_TUNE_HFECCM        = 6,   ///< HF ECCM tuning
    RADIO_TUNE_AMBSOUND      = 7    ///< Ambient Sound tuning
};

/// @brief Auxiliary Audio Callback
/// @param left_bytes Bytes of audio received
/// @param left_len Length of bytes received
/// @param left_samples Count of samples received
/// @param right_bytes Bytes of audio received
/// @param right_len Length of bytes received
/// @param right_samples Count of samples received
/// @see AuxAudio_Register
typedef void(*AudioCallback)(char* left_bytes,
                             unsigned int left_len,
                             unsigned int left_samples,
                             char* right_bytes,
                             unsigned int right_len,
                             unsigned int right_samples);

/// License request status
enum LicenseStatus_t
{
    LICENSE_STATUS_PENDING = 1,     ///< Request pending
    LICENSE_STATUS_GRANTED = 2,     ///< Request granted
    LICENSE_STATUS_RELEASED = 3,    ///< Request released
    LICENSE_STATUS_LOST = 4         ///< Request lost
};


/// Audio Device Types
enum AudioDeviceType_t
{
    AUDIO_DEVICE_PLAYBACK = 1,      ///< Playback device (Speakers, Headsets)
    AUDIO_DEVICE_CAPTURE = 2,       ///< Capture device (Microphone)
    AUDIO_DEVICE_PLAYBACK2 = 3,     ///< Secondary playback device
    AUDIO_DEVICE_TOTAL
};

#ifdef __cplusplus
}
#endif

#endif

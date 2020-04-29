/*!
 @header SKYLINKConnectionConfig.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <Foundation/Foundation.h>

/*!
 @enum
 @abstract SKYLINKVideoDevice
 @description Front camera or back camera.
 @constant Front.
 @constant Back.
 */
typedef enum SKYLINKVideoDevice {
    SKYLINKVideoDeviceFrontCamera = 0,
    SKYLINKVideoDeviceBackCamera
} SKYLINKVideoDevice;

/*!
 @enum
 @abstract SKYLINKAudioCodec
 @constant OPUS by default
 @constant ISAC
*/
typedef enum SKYLINKAudioCodec {
    SKYLINKAudioCodecOPUS = 0,
    SKYLINKAudioCodecISAC
} SKYLINKAudioCodec;

/*!
 @enum
 @abstract SkylinkVideoCodec
 @constant SkylinkVideoCodecH264
 @constant SkylinkVideoCodecVP8
*/
typedef enum SkylinkVideoCodec {
    SkylinkVideoCodecH264 = 0,
    SkylinkVideoCodecVP8,
} SkylinkVideoCodec;

/*!
 @enum
 @abstract SKYLINKRoomSize
 @description Specify the size of the room.
 @constant SKYLINKRoomSizeSmall Very small room.
 @constant SKYLINKRoomSizeSmall Default size, if you don't specify the size.
 @constant SKYLINKRoomSizeMedium Medium.
 @constant SKYLINKRoomSizeLarge Large.
 @constant SKYLINKRoomSizeExtraLarge Extra Large.
 */
typedef enum SKYLINKRoomSize {
    SKYLINKRoomSizeExtraSmall = 0, // 2~3 peers
    SKYLINKRoomSizeSmall, // 3~4 peers
    SKYLINKRoomSizeMedium, // 5~7 peers
    SKYLINKRoomSizeLarge, // 8~10 peers
    SKYLINKRoomSizeExtraLarge // 11~15 peers
} SKYLINKRoomSize;

/*!
 @enum
 @abstract AudioVideoConfig
 @description Specify the audio and video configuration
 @constant NO_AUDIO_NO_VIDEO Default value, no audio and no video
 @constant AUDIO_ONLY Only audio.
 @constant VIDEO_ONLY Only video.
 @constant AUDIO_AND_VIDEO Both audio and video.
*/
typedef enum AudioVideoConfig {
    AudioVideoConfig_NO_AUDIO_NO_VIDEO = 0,
    AudioVideoConfig_AUDIO_ONLY,
    AudioVideoConfig_VIDEO_ONLY,
    AudioVideoConfig_AUDIO_AND_VIDEO
} AudioVideoConfig;

/*!
 @enum
 @abstract SkylinkAction
 @constant Send file request
*/
typedef enum SkylinkAction {
    SkylinkAction_FILE_SEND_REQUEST = 0,
    SkylinkAction_CONNECT_TO_ROOM,
    SkylinkAction_GET_MESSAGE_STORED
} SkylinkAction;

/*!
 @enum
 @abstract NetworkTransport
 @constant Not specified
 @constant Using UDP
 @constant Using TCP
*/
typedef enum NetworkTransport {
    NetworkTransportUDP = 0,
    NetworkTransportTCP
} NetworkTransport;

typedef enum SocketIOTransport {
    SocketIOTransportWebSocket = 0,
    SocketIOTransportPolling,
    SocketIOTransportUndefined
} SocketIOTransport;

/*!
 Preset constants
 */
extern NSInteger const DEFAULT_VIDEO_FPS; // = 30
extern NSInteger const VIDEO_RES_MS_BEFORE_CHECK; // = 275
extern NSInteger const MAX_PEERS_VIDEO; // = 4
extern NSInteger const MAX_PEERS_AUDIO_ONLY; // = 8
extern NSInteger const MAX_PEERS_NO_AUDIO_NO_VIDEO; // = 16

/*!
 @class
 @discussion The class representing the conversation configuration.
 */
@interface SKYLINKConnectionConfig : NSObject

/*!
 @property
 @abstract enable/disable sending audio.
 @discussion Default value is NO.
 */
@property (nonatomic, readonly) BOOL sendAudio;
/*!
 @property
 @abstract enable/disable receive audio.
 @discussion No default value.
 */
@property (nonatomic, readonly) BOOL receiveAudio;
/*!
 @property
 @abstract enable/disable sending video.
 @discussion Default value is NO.
 */
@property (nonatomic, readonly) BOOL sendVideo;
/*!
 @property
 @abstract enable/disable receiving video.
 @discussion No default value.
 */
@property (nonatomic, readonly) BOOL receiveVideo;
/*!
 @property
 @abstract Check if dataChennel is enabled
 @discussion If hasP2PMessaging or hasFileTransfer or hasDataTransfer, the value is true
 */
@property (nonatomic, readonly) BOOL isEnableDataChannel;
/*!
@property
@abstract enable/disable messaging.
@discussion Default value is NO.
*/
@property (nonatomic, assign) BOOL hasP2PMessaging;
/*!
 @property
 @abstract enable/disable file transfer.
 @discussion Default value is NO.
 */
@property (nonatomic, assign) BOOL hasFileTransfer;
/*!
@property
@abstract enable/disable data transfer.
@discussion Default value is NO.
*/
@property (nonatomic, assign) BOOL hasDataTransfer;
/*!
 @property
 @abstract enable/disable multitrack support for creating.
 @discussion Default value is YES.
 */
@property (nonatomic, assign) BOOL isMultiTrackCreateEnable;
/*!
 @property
 @abstract Used to limit remote peers audio media bitrate.
 @discussion Default value is 0, meaning not bitrate limit.
 */
@property (nonatomic, assign) NSInteger maxAudioBitrate;
/*!
 @property
 @abstract Used to limit remote peers video media bitrate.
 @discussion Default value is 512.
 */
@property (nonatomic, assign) NSInteger maxVideoBitrate;
/*!
 @property
 @abstract Used to limit remote peers data bitrate.
 @discussion Default value is 0, meaning not bitrate limit.
 */
@property (nonatomic, assign) NSInteger maxDataBitrate;
/*!
 @property
 @abstract Default camera device
 @description Get the default camera device, whether it's front or back
 */
@property (nonatomic, assign) SKYLINKVideoDevice defaultVideoDevice;
/*!
 @property
 @abstract Check/set if audio auto gain control by WebRTC is enabled.
 @description Enabled by default
 */
@property (nonatomic, assign) BOOL hasAudioAutoGainControl;
/*!
 @property
 @abstract Check/set if audio echo cancellation by WebRTC is enabled.
 @description Enabled by default
 */
@property (nonatomic, assign) BOOL hasAudioEchoCancellation;
/*!
 @property
 @abstract Check/set if audio high pass filter by WebRTC is enabled.
 @description Enabled by default
 */
@property (nonatomic, assign) BOOL hasAudioHighPassFilter;
/*!
 @property
 @abstract Check if audio noise suppression by WebRTC is enabled.
 @description Enabled by default
 */
@property (nonatomic, assign) BOOL hasAudioNoiseSuppression;
/*!
 @property
 @abstract Set the room size when creating a new room
 @description The size of the new room, if not specified, the default size will be small.
 */
@property (nonatomic, assign) SKYLINKRoomSize roomSize;
/*!
 @property
 @abstract Whether to allow the TURN server
 @description Default is YES
*/
@property(nonatomic, assign) BOOL isAllowTurn;
/*!
 @property
 @abstract Whether to allow the TURN server
 @description Default is YES
*/
@property(nonatomic, assign) BOOL isAllowStun;
/*!
@property
@abstract Whether to allow the HOST
@description Default is YES
*/
@property(nonatomic, assign) BOOL isAllowHost;
/*!
 @property
 @abstract Whether to apply the ICE filters
 @description Default is NO
*/
@property (nonatomic, assign) BOOL enableDNSPreSolving;
/*!
 @property
 @abstract Whether to filer out all the IPv6 servers
 @description Default is NO
*/
@property (nonatomic, assign) BOOL enableIPv6Filter;
/*!
 @property
 @abstract Mirror local front camera view
 @description Default is NO
*/
@property (nonatomic, assign) BOOL isMirrorLocalFrontCameraView;
/*!
 @property
 @abstract Default values at which to obtain camera video fps when video device is started
 @description Default is DEFAULT_VIDEO_FPS
*/
@property(nonatomic, assign) NSInteger defaultCameraVideoFps;
/*!
 @property
 @abstract Default values at which to obtain video, when video device is started
 @description Available values
              AVCaptureSessionPresetLow,
              AVCaptureSessionPreset640x480,
              AVCaptureSessionPreset352x288,
              AVCaptureSessionPreset1280x720,
              AVCaptureSessionPresetHigh,
              AVCaptureSessionPresetPhoto,
              AVCaptureSessionPreset1920x1080
              Default is AVCaptureSessionPreset640x480
*/
@property(nonatomic, copy) AVCaptureSessionPreset _Nullable captureSessionPreset;
/*!
 @property
 @abstract Automatic video resolution
 @description ms to wait before checking again
*/
@property(nonatomic, assign) NSInteger videoResNumWaitMs;
/*!
 @property
 @abstract Automatic video resolution
 @description Will report when video changes
*/
@property(nonatomic, assign) BOOL isReportVideoResolutionOnVideoChange;
/*!
 @property
 @abstract Whether to allow the ICE server restart
 @description Default is NO
*/
@property(nonatomic, assign) BOOL isAllowIceRestart;
/*!
 @property
 @abstract Custom transport values for ICE candidates
 @description If any invalid value is set, networkTransport will be set to empty
*/
@property(nonatomic, assign) NetworkTransport networkTransport;
/*!
 @property
 @abstract Preferred audio codec used
 @description Default is OPUS
*/
@property(nonatomic, assign) SKYLINKAudioCodec preferredAudioCodec;
/*!
 @property
 @abstract Preferred video codec info used
 @description Default is info with name kRTCVideoCodecVp8Name
*/
@property(nonatomic, assign) SkylinkVideoCodec preferredVideoCodec;
/*!
 @property
 @abstract xxx
 @description Default is -1 which is infinite, if you don't want to reconnect, set it to 0
*/
@property(nonatomic, assign) NSInteger reconnectAttempts;
/*!
 @property
 @abstract xxx
 @description This should be positive value, otherwise it will be set to 0
*/
@property(nonatomic, assign) CGFloat reconnectionDelay;
/*!
 @property
 @abstract xxx
 @description xxx
*/
@property(nonatomic, assign) SocketIOTransport preferredTransport;

/*!
 @property
 @abstract When start the SDK, use loudspeaker or not
 @description Default is NO
 */
@property(nonatomic, assign) BOOL useSpeaker;

/*!
 @method
 @abstract Get the timeout value for an action
 @param skylinkAction A pre-defined action like send file request action
 @return The timeout limit
*/
- (CGFloat)getTimeoutWithEventType:(SkylinkAction)skylinkAction;

/*!
 @method
 @abstract Set the timeout value for an action
 @param timeout The timeout limit
 @param skylinkAction A pre-defined action like send file request action
*/
- (void)setTimeout:(CGFloat)timeout skylinkAction:(SkylinkAction)skylinkAction;

/*!
@method
@abstract Set config for receive media
@param audioVideoConfig Configuration of receive media
*/
- (void)setAudioVideoReceiveConfig:(AudioVideoConfig)audioVideoConfig;

/*!
@method
@abstract Set config for send media
@param audioVideoConfig Configuration of send media
*/
- (void)setAudioVideoSendConfig:(AudioVideoConfig)audioVideoConfig;

/*!
 @method
 @abstract Get max allowed peers in a room by the config
 @param audioVideoConfig The config whether the room is audio or video, etc.
 @return The max peer count
*/
- (NSInteger)getMaxRemotePeersConnectedWithAudioVideoConfig:(AudioVideoConfig)audioVideoConfig;

/*!
 @method
 @abstract Set max allowed peers in a room by the config
 @param maxPeersConnected Max allowed peers in the room
 @param audioVideoConfig The config whether the room is audio or video, etc.
*/
- (void)setMaxRemotePeersConnected:(NSInteger)maxPeersConnected audioVideoConfig:(AudioVideoConfig)audioVideoConfig;

/*!
 @method
 @abstract Optional configuration for advanced users.
 @param key the key
 @param value the bool value
 @discussion The key and associated settings values which you can get from Temasys support
 */
-(void)setAdvancedOptionWithKey:(null_unspecified NSString *)key value:(null_unspecified id)value;
@end

/*!
 @class
 @abstract Class representing the handshaking peer properties.
 @discussion This class is used in the delegate method called when a peer joins the room to carry informations about the joining peer media properties.
 */
@interface SKYLINKPeerMediaProperties : NSObject

/*!
 @property
 @abstract whether the peer has audio.
 */
@property (nonatomic, assign) BOOL hasAudio;
/*!
 @property
 @abstract is audio stereo.
 @discussion if 'hasAudio' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL hasAudioStereo;
/*!
 @property
 @abstract is audio muted.
 @discussion if 'hasAudio' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL isAudioMuted;
/*!
 @property
 @abstract whether the peer has video
 */
@property (nonatomic, assign) BOOL hasVideo;
/*!
 @property
 @abstract is video muted.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) BOOL isVideoMuted;
/*!
 @property
 @abstract width of the video frame.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoWidth;
/*!
 @property
 @abstract height of the video frame.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoHeight;
/*!
 @property
 @abstract frame rate of the video.
 @discussion if 'hasVideo' returns false then this property is insignificant.
 */
@property (nonatomic, assign) NSInteger videoFrameRate;
@end

/*!
 @header SKYLINKConnection.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "SKYLINKConnectionConfig.h"
#import "SKYLINKProtocol.h"
#import "SKYLINKMedia.h"

 /*!
 @enum
 @abstract SKYLINKAssetType
 @description Asset types to help the framework read the files.
 @constant SKYLINKAssetTypeFile Files within the app sandbox.
 @constant SKYLINKAssetTypeMusic Files from the music library.
 @constant SKYLINKAssetTypePhoto Photo and Video content from the Photo Library.
 */
typedef enum SKYLINKAssetType {
    SKYLINKAssetTypeFile = 1,
    SKYLINKAssetTypeMusic,
    SKYLINKAssetTypePhoto
} SKYLINKAssetType;

extern NSString * _Nonnull const SKYLINKRequiresPermissionNotification;

/*!
 @type
 @abstract The callback block for general usage which contains an NSError.
*/
typedef void (^ErrorBlock)(NSError * _Nullable error);
/*!
 @type
 @abstract The callback block for video resolution which contains three NSInteger values and an NSError.
*/
typedef void (^ResolutionResultBlock)(NSInteger width, NSInteger height, NSInteger fps, NSError * _Nullable error);

/*!
 @class
 @abstract The class representing the connection to the room.
 @discussion You should make sure this objects does not get released as long as you need it, for example by storing it as a strong property.
 */
@interface SKYLINKConnection : NSObject

#pragma mark - Delegates
/*!
 @name Delegates
 */

/*!
 @property
 @abstract delegate related to life cycle, implementing the SKYLINKConnectionLifeCycleDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionLifeCycleDelegate> _Null_unspecified lifeCycleDelegate;
/*!
 @property
 @abstract delegate related to remote peer activities, implementing the SKYLINKConnectionRemotePeerDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionRemotePeerDelegate> _Null_unspecified remotePeerDelegate;
/*!
 @property
 @abstract delegate related to audio/video media, implementing the SKYLINKConnectionMediaDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMediaDelegate> _Null_unspecified mediaDelegate;
/*!
 @property
 @abstract delegate related to various type of custom messages, implementing the SKYLINKConnectionMessagesDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMessagesDelegate> _Null_unspecified messagesDelegate;
/*!
 @property
 @abstract delegate related to file transfer, implementing the SKYLINKConnectionFileTransferDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionFileTransferDelegate> _Null_unspecified fileTransferDelegate;
/*!
 @property
 @abstract delegate related to room recording, implementing the SKYLINKConnectionRecordingDelegate protocol.
 */
@property(nonatomic, weak) id<SKYLINKConnectionRecordingDelegate> _Null_unspecified recordingDelegate;

#pragma mark - Properties Peer
/*!
 @name Peer
 */

/*!
 @property
 @abstract peer id of the current local user
 */
@property(nonatomic, copy, readonly) NSString * _Null_unspecified localPeerId;

/*!
 @property
 @abstract Maximun number of peers.
 @discussion The default value depends on the configuration.
 */
@property(nonatomic, assign) NSInteger maxPeerCount;

/*!
 @property
 @abstract The use name of the peer.
 @discussion This is obtained from the server.
*/
@property(nonatomic, copy, readonly) NSString * _Null_unspecified userName;

/*!
 @property
 @abstract Wether enable the logs.
 @discussion Set the debugging mode for tracing etc.
*/
@property(nonatomic, assign) BOOL enableLogs;

/*!
 @property
 @abstract Map of secretId and encryption secret for generating key for SDK encryption.
 @discussion SDK now allows AES encryption/decryption of certain user provided information.
*/
@property(nonatomic, copy) NSDictionary * _Nullable encryptSecrets;

/*!
 @property
 @abstract Selected secretId of the secret to use when SDK needs to perform encryption.
 @discussion SDK now allows AES encryption/decryption of certain user provided information.
*/
@property(nonatomic, copy) NSString * _Nullable selectedSecretId;

/*!
 @property
 @abstract whether the next public server message sent should be persisted.
 
*/
@property(nonatomic, assign) BOOL messagePersist;

#pragma mark - Lifecycle
/*!
 @name Lifecycle
 */

/*!
 @method
 @abstract Initialize and return a newly allocated connection object
 @discussion Changes in config after creating the object won't affect the connection
 @param config The connection configuration object
 @param callback Skylink callback with an error message
 */
- (null_unspecified instancetype)initWithConfig:(null_unspecified SKYLINKConnectionConfig *)config callback:(nullable ErrorBlock)callback;


#pragma mark - Room connection
/*!
@name Room connection
*/

/*!
 @method
 @abstract Join the room specifiying the shared secret, room name and user info
 @discussion It is recommended to use connectToRoomWithCredentials:roomName:userInfo: after calculating the credentials on a server, but if the client application has no server implementation then this one should be used
 @param appKey Shared appKey
 @param secret Shared secret
 @param roomName Name of the room to join
 @param userData User defined information (relating to oneself). May be an NSString, NSDictionary or NSArray
 @param callback Skylink callback with an error message
*/
- (void)connectToRoomWithAppKey:(null_unspecified NSString *)appKey secret:(null_unspecified NSString *)secret roomName:(null_unspecified NSString *)roomName userData:(null_unspecified id)userData callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Join the room specifiying the calculated string URL and user info.
 @discussion Use this method when you calculate the URL on your server with your API key, secret and room name. Allows you to avoid having those parameters in the iOS app code.
 @param stringURL Generated with room name, appKey, secret, startTime and duration. Typed NSString (not NSURL).
 @param userData User defined information (relating to oneself). May be an NSString, NSDictionary or NSArray.
 @param callback Skylink callback with an error message.
 */
- (void)connectToRoomWithStringURL:(null_unspecified NSString *)stringURL userData:(null_unspecified id)userData callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Leave the room
 @discussion Leave the room and remove any video renderers and PeerConnections
 @param callback Skylink callback with an error message
 */
- (void)disconnect:(nullable ErrorBlock)callback;


#pragma mark - Media create remove
/*!
@name Media create remove
*/

/*!
 @method
 @abstract Start a local media with a media device
 @param mediaDevice The type of Skylink media device you want to start
 @param mediaMetadata Some label associated with the new media, can be NSString, NSDictionary, NSArray
 @param callback Skylink callback with an error message
 */
- (void)createLocalMediaWithMediaDevice:(SKYLINKMediaDevice)mediaDevice mediaMetadata:(id _Nullable)mediaMetadata callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Start a custom local media with a media device, customVideoCapturer, captureSessionPreset, and fps
 @param mediaDevice The type of Skylink media device you want to start
 @param mediaMetadata Some label associated with the new media, can be NSString, NSDictionary, NSArray
 @param customVideoCapturer Using custom videoCapturer
 @param captureSessionPreset AVCaptureSessionPreset will be accepted
 @param fps The framerate using by the custom video capturer
 @param callback Skylink callback with an error message
 @discussion Available values for captureSessionPreset
             AVCaptureSessionPresetLow, AVCaptureSessionPreset640x480, AVCaptureSessionPreset352x288, AVCaptureSessionPreset1280x720, AVCaptureSessionPresetHigh, AVCaptureSessionPresetPhoto, AVCaptureSessionPreset1920x1080
*/
- (void)createLocalMediaWithMediaDevice:(SKYLINKMediaDevice)mediaDevice mediaMetadata:(id _Nullable)mediaMetadata customVideoCapturer:(RTCCameraVideoCapturer * _Nonnull)customVideoCapturer captureSessionPreset:(AVCaptureSessionPreset _Null_unspecified)captureSessionPreset fps:(NSInteger)fps callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Start a local media with a media device, custom captureSessionPreset and fps
 @param mediaDevice The type of Skylink media device you want to start
 @param mediaMetadata Some label associated with the new media, can be NSString, NSDictionary, NSArray
 @param captureSessionPreset AVCaptureSessionPreset will be accepted
 @param fps The framerate using by the custom video capturer
 @param callback Skylink callback with an error message
 @discussion Available values for captureSessionPreset
             AVCaptureSessionPresetLow, AVCaptureSessionPreset640x480, AVCaptureSessionPreset352x288, AVCaptureSessionPreset1280x720, AVCaptureSessionPresetHigh, AVCaptureSessionPresetPhoto, AVCaptureSessionPreset1920x1080
 */
- (void)createLocalMediaWithMediaDevice:(SKYLINKMediaDevice)mediaDevice mediaMetadata:(id _Nullable)mediaMetadata captureSessionPreset:(AVCaptureSessionPreset _Null_unspecified)captureSessionPreset fps:(NSInteger)fps callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Start a local media with a media device and a custom view controller
 @param mediaDevice The type of Skylink media device you want to start
 @param mediaMetadata Some label associated with the new media, can be NSString, NSDictionary, NSArray
 @param viewController Screenshare with specific ViewController, if you don't provide a view controller, the top view controller will be used
 @param callback Skylink callback with an error message
*/
- (void)createLocalMediaWithMediaDevice:(SKYLINKMediaDevice)mediaDevice mediaMetadata:(id _Nullable)mediaMetadata fromViewController:(UIViewController * _Null_unspecified)viewController callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Change a local media state by the mediaId
 @param mediaId The unique mediaId of a Skylink media object
 @param mediaState The SkyinkMediaState you want to change to
 @param callback Skylink callback with an error message
*/
- (void)changeLocalMediaStateWithMediaId:(NSString * _Nonnull)mediaId mediaState:(SKYLINKMediaState)mediaState callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Stop and remove a local media by the mediaId
 @param mediaId The unique mediaId of a Skylink media object
 @param callback Skylink callback with an error message
 */
- (void)destroyLocalMediaWithMediaId:(NSString * _Nonnull)mediaId callback:(nullable ErrorBlock)callback;


#pragma mark - Media get
/*!
@name Media get
*/

/*!
 @method
 @abstract Get specific SkylinkMedia via MediaId
 @param mediaId The unique mediaId of a Skylink media object
 @return The required media, if cannot find, nil will be returned
*/
- (nullable SKYLINKMedia *)getSkylinkMediaWithMediaId:(nonnull NSString *)mediaId;

/*!
 @method
 @abstract Get list of SkylinkMedia via MediaType
 @param mediaType The SkylinkMediaType you want to get
 @param peerId The peerId you want to get from
 @return The array of the required media, if cannot find, nil will be returned
 @discussion If mediaType is NOT in the SKYLINKMediaType enum, all SM of peerId will be returned.
             If peerId is nil, all SM of mediaType will be returned.
             If peerId is null and mediaType is NOT in the SKYLINKMediaType enum all SM will be returned
*/
- (nullable NSArray<SKYLINKMedia *> *)getSkylinkMediaListWithMediaType:(SKYLINKMediaType)mediaType peerId:(NSString * _Nullable)peerId;


#pragma mark - Media video devices
/*!
@name Media video devices
*/

/*!
 @method
 @abstract Switches between front and back camera. By default the front camera input is captured.
 */
- (void)switchCamera:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Get the current camera captured format
 @return The current capturer format
 */
- (nullable AVCaptureDeviceFormat *)getCurrentCaptureFormat;

/*!
 @method
 @abstract Get all the supported camera capture formats
 @return All the supported capturer formats
 */
- (nullable NSArray<AVCaptureDeviceFormat *> *)getAllCaptureFormats;

/*!
 @method
 @abstract Get the current video device
 @return The current video device
 */
- (nullable AVCaptureDevice *)getCurrentVideoDevice;

/*!
 @method
 @abstract Get all available video devices
 @return The array of all video devices
*/
- (nullable NSArray<AVCaptureDevice *> *)getAllVideoDevices;

/*!
 @method
 @abstract Get the current camera name
 @return The current camera name
 */
- (nullable NSString *)getCurrentCameraName;

/*!
 @method
 @abstract Get all the available camera names
 @return The array of all camera names
*/
- (nullable NSArray<NSString *> *)getAllCameraNames;


#pragma mark - Media video resolutions
/*!
@name Media video resolutions
*/

/*!
 @method
 @abstract You may use this to set your local input stats
 @param mediaId The unique mediaId of a Skylink media object
 @param width Width you want to set
 @param height Height you want to set
 @param fps Frame rate you want to set
 @param callback Skylink callback with an error message
 */
- (void)setInputVideoResolutionOfMedia:(nonnull NSString *)mediaId toWidth:(NSUInteger)width height:(NSUInteger)height fps:(NSUInteger)fps callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Get all the stats for your local input video
 @param mediaId The unique mediaId of a Skylink media object
 @param callback Skylink callback contains the width height frame rate and an error message, if everything is fine, the error can be nil
 */
- (void)getInputVideoResolutionWithMediaId:(nonnull NSString *)mediaId callback:(ResolutionResultBlock _Null_unspecified)callback;

/*!
 @method
 @abstract Get all the stats of your received remote video
 @param mediaId The unique mediaId of a Skylink media object
 @param callback Skylink callback contains the width height frame rate and an error message, if everything is fine, the error can be nil
 */
- (void)getReceivedVideoResolutionWithMediaId:(nonnull NSString *)mediaId callback:(ResolutionResultBlock _Null_unspecified)callback;

/*!
 @method
 @abstract Get all the stats you sent to the remote peer
 @param remotePeerId The remote peer id
 @param mediaId The unique mediaId of a Skylink media object
 @param callback Skylink callback contains the width height frame rate and an error message, if everything is fine, the error can be nil
 */
- (void)getSentVideoResolutionOfRemotePeerId:(nonnull NSString *)remotePeerId mediaId:(nonnull NSString *)mediaId callback:(ResolutionResultBlock _Null_unspecified)callback;


#pragma mark - Media others
/*!
 @name Media others
 */

/*!
 @method
 @abstract Mute/unmute own audio and trigger mute/unmute audio call back for all other peers.
 @param isMuted Flag to set if audio should be muted. Set to true to mute and false to unmute.
 */
- (void)muteAudio:(BOOL)isMuted;

/*!
 @method
 @abstract Mute/unmute own video and trigger mute/unmute video call back for all other peers.
 @param isMuted Flag to set if video should be muted. Set to true to mute and false to unmute.
 */
- (void)muteVideo:(BOOL)isMuted;

/*!
 @method
 @abstract Checks if own audio is currently muted.
 @return true if audio is muted and false otherwise.
 */
- (BOOL)isAudioMuted;

/*!
 @method
 @abstract Checks if own video is currently muted.
 @return true if video is muted and false otherwise.
 */
- (BOOL)isVideoMuted;

/*!
 @method
 @abstract Checks the value in the SDK, which was set by the SkylinkConfig in SDK's init
 @return Whethe enabled or not
 @discussion This value does not change once set
*/
- (BOOL)isMultiTrackEnable;


#pragma mark - Statistics
/*!
@name Statistics
*/

/*!
 @method
 @abstract Get the full WebRTC stats
 @param mediaId The unique mediaId of a Skylink media object
 @param remotePeerId The remote peer id
 @param callback Skylink callback with an object containing the transfer speed (Kbps) and an error, the error can be nil if everything is fine
*/
- (void)getSentTransferSpeedByMediaId:(nonnull NSString *)mediaId remotePeerId:(null_unspecified NSString *)remotePeerId callback:(void (^ _Null_unspecified) (CGFloat speed, NSError * _Nullable error))callback;

/*!
 @method
 @abstract Get the full WebRTC stats
 @param mediaId The unique mediaId of a Skylink media object
 @param callback Skylink callback with an object containing the transfer speed (Kbps) and an error, the error can be nil if everything is fine
*/
- (void)getReceivedTransferSpeedByMediaId:(nonnull NSString *)mediaId callback:(void (^ _Null_unspecified) (CGFloat speed, NSError * _Nullable error))callback;

/*!
 @method
 @abstract Get the full WebRTC stats for sent
 @param mediaId The unique mediaId of a Skylink media object
 @param remotePeerId The remote peer id
 @param callback Skylink callback with an object containing all the WebRTC stats
 */
- (void)getSentWebRtcStatsWithMediaId:(nonnull NSString *)mediaId remotePeerId:(null_unspecified NSString *)remotePeerId callback:(void (^_Nullable) (id _Nullable responseObject, NSError * _Nullable error))callback;

/*!
@method
@abstract Get the full WebRTC stats for receive
@param mediaId The unique mediaId of a Skylink media object
@param callback Skylink callback with an object containing all the WebRTC stats
*/
- (void)getReceivedWebRtcStatsWithMediaId:(nonnull NSString *)mediaId callback:(void (^_Nullable) (id _Nullable responseObject, NSError * _Nullable error))callback;

#pragma mark - Recording 
/*!
 @name Recording
 */

/*!
 @method
 @abstract Start the recording of the room
 @warning This feature is in BETA
 @discussion This is a Skylink Media Relay only feature, it needs to be enable for the API Key in Temasys developer console
 @param callback Skylink callback with an error message
 */
- (void)startRecording:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Stop the recording of the room
 @warning This feature is in BETA
 @discussion This is a Skylink Media Relay only feature, it needs to be enable for the API Key in Temasys developer console
 @param callback Skylink callback with an error message
 */
- (void)stopRecording:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Check recording status.
 @discussion This is a Skylink Media Relay only feature
 @return The recording status bool value
 */
- (BOOL)isRecording;


#pragma mark - Messaging
/*!
 @name Messaging
 */

/*!
 @method
 @abstract Send a server message (dictionary, array or string) to a peer via signaling server
 @discussion If the 'peerId' is not given then the message is broadcasted to all the peers
 @param message User defined message to be sent. May be an NSString, NSDictionary or NSArray
 @param remotePeerId The unique id of the peer to whom the message is sent
 @param callback Skylink callback with an error message
 */
-(void)sendServerMessage:(null_unspecified id)message toRemotePeerId:(nullable NSString *)remotePeerId callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Send a peer to peer message (dictionary, array or string) to a peer via data channel
 @discussion If the 'peerId' is not given then the message is broadcasted to all the peers
 @param message User defined message to be sent. May be an NSString, NSDictionary, NSArray
 @param remotePeerId The unique id of the peer to whom the message is sent
 @param callback Skylink callback with an error message
 */
- (void)sendP2PMessage:(null_unspecified id)message toRemotePeerId:(nullable NSString *)remotePeerId callback:(nullable ErrorBlock)callback;

/*!
@method
@abstract The sending Peer sends this to get storedMessages of the room
@discussion Can only get all public messages
*/
- (void)getStoredMessages:(void (^ _Null_unspecified) (NSArray * _Nullable storedMessages, NSDictionary * _Nullable errors))callback;
#pragma mark - Data transfer
/*!
@name Data transfer
*/

/*!
 @method
 @abstract Send binary data to a peer via data channel
 @discussion If the 'peerId' is not given then the data is sent to all the peers. If the caller passes data object exceeding the maximum length i.e. 65456, excess bytes are truncated to the limit before sending the data on to the channel
 @param data Binary data to be sent to the peer. The maximum size the method expects is 65456 bytes
 @param remotePeerId The unique id of the peer to whom the data is sent
 @param callback Skylink callback with an error message
 */
- (void)sendData:(null_unspecified NSData *)data toRemotePeerId:(null_unspecified NSString *)remotePeerId callback:(nullable ErrorBlock)callback;


#pragma mark - File Transfer
/*!
 @name File Transfer
 */

/*!
 @method
 @abstract This will trigger a file permission event at a peer
 @param fileURL The url of the file to send
 @param assetType The type of the asset to send
 @param fileName The unique id of the peer to whom the file would be sent
 @param remotePeerId The unique id of the peer to whom the file would be sent, if it is nil, broadcast the sending
 @param callback Skylink callback with an error message
 @exception exception An exception will be raised if there is already a file transfer being done with the same peer
 */
- (void)sendFileTransferWithFileURL:(null_unspecified NSURL *)fileURL assetType:(SKYLINKAssetType)assetType fileName:(NSString * _Nullable)fileName remotePeerId:(null_unspecified NSString *)remotePeerId callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Accept the file transfer request from a peer
 @param fileName The name of the file in request, you can specify a file name, if it is nil, then then file name will be the original file name
 @param remotePeerId The unique id of the peer from whom the file would be received
 @param callback Skylink callback with an error message
 @discussion You can specify a local file name, for the file receiving from the remote peer, if don't want to specify a local name, just send a nil, then the original file name will be used to save to your local disk
 */
- (void)acceptFileTransferWithFileName:(null_unspecified NSString *)fileName fromRemotePeerId:(null_unspecified NSString *)remotePeerId callback:(nullable ErrorBlock)callback;

/*!
@method
@abstract Reject a File (uses WRQ) from remote user
@param remotePeerId The unique id of the peer from whom the file would be received
@param callback Skylink callback with an error message
*/
- (void)rejectFileTransferFromRemotePeerId:(null_unspecified NSString *)remotePeerId callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Cancel the existing on going transfer at anytime
 @param forSending The BOOL value indicates if you are to send the file
 @param callback Skylink callback with an error message
 @discussion If you are the sender, this is true, you can cancel the sending anytime(before or after it starts), if you are the receiver, this is false, you may also cancel the receiving anytime
 */
- (void)cancelFileTransferWithRemotePeerId:(null_unspecified NSString *)remotePeerId forSending:(BOOL)forSending callback:(nullable ErrorBlock)callback;

 
#pragma mark - Room state
/*!
 @name Room state
 */

/*!
 @method
 @abstract Lock the room
 @param callback Skylink callback with an error message
 */
- (void)lockTheRoom:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Unlock the room
 @param callback Skylink callback with an error message
 */
- (void)unlockTheRoom:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Check if room is locked
 */
- (BOOL)isRoomLocked;


#pragma mark - Room related
/*!
@name Room related
*/

/*!
 @method
 @abstract Get roomId
 @return RoomId
 @discussion This is generally not needed
 */
- (nonnull NSString *)getRoomId;


#pragma mark - User
/*!
 @name User
 */

/*!
 @method
 @abstract Get list of Peers connected
 @return The array of connected remote peers
 */
- (nullable NSArray<NSString *> *)getPeerIdList;

/*!
 @method
 @abstract Update user information for every other peer and triggers user info call back at all the other peer's end
 @param localUserData User defined information. May be an NSString, NSDictionary or NSArray
 @param callback Skylink callback with an error message
 */
- (void)sendLocalUserData:(null_unspecified id)localUserData callback:(nullable ErrorBlock)callback;

/*!
 @method
 @abstract Get the cached user info for a particular peer
 @param peerId The unique id of the peer, if the peerId is inl, then get self userInfo
 @return User defined information. May be an NSString, NSDictionary or NSArray
 */
- (nonnull id)getUserInfo:(nullable NSString *)peerId;

/*!
 @method
 @abstract Refresh peer connection with a specified peer
 @discussion This method is provided as a convenience method. So that one can call if a peer streams are not behaving correctly
 @param remotePeerId The unique id of the peer with whom the connection is being refreshed
 @param doIceRestart Is this restart an ICE restart
 @param callback Skylink callback with an error message
*/
- (void)refreshConnectionWithRemotePeerId:(nullable NSString *)remotePeerId doIceRestart:(BOOL)doIceRestart callback:(nullable ErrorBlock)callback;


#pragma mark - Utility
/*!
 @name Utility
 */

/*!
 @method
 @abstract Get the version string of this Skylink SDK for iOS
 @return Version string of this Skylink SDK for iOS
 */
+ (nonnull NSString *)getSkylinkVersion;

/*!
 @method
 @abstract Calculate credentials to be used by the connection
 @param roomName Name of the room
 @param duration Duration of the call in hours
 @param startTime Start time of the call as per client application time zone
 @param secret The shared secret
 @return The calculated credential string
 */
+ (nonnull NSString *)calculateCredentials:(null_unspecified NSString *)roomName duration:(null_unspecified NSNumber *)duration startTime:(null_unspecified NSDate *)startTime secret:(null_unspecified NSString *)secret;
/*!
@method
@abstract Get NSError of SDK error list from Error code
@param errorCode code of error
@return The NSError
*/
+(null_unspecified NSError*)getErrorFrom:(int)errorCode;
@end

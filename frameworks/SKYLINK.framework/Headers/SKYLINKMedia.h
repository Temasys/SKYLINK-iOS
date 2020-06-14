/*!
 @header SKYLINKMedia.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#import <Foundation/Foundation.h>
#import <WebRTC/WebRTC.h>

/*!
 @enum
 @abstract SKYLINKMediaType
 @description One media track(either audio or video) one SKYLINKMedia object.
 @constant SKYLINKMediaTypeAudio Audio.
 @constant SKYLINKMediaTypeVideoCamera Camera video.
 @constant SKYLINKMediaTypeVideoScreen Screen video.
 @constant SKYLINKMediaTypeVideoCustom If you implement the video capturing in your app, please use this option for the media type.
 @constant SKYLINKMediaTypeVideo This option is read only, please don't send this in.
 */
typedef enum SKYLINKMediaType {
    SKYLINKMediaTypeAudio = 0,
    SKYLINKMediaTypeVideoCamera,
    SKYLINKMediaTypeVideoScreen,
    SKYLINKMediaTypeVideoCustom,
    SKYLINKMediaTypeVideo
} SKYLINKMediaType;

/*!
 @enum
 @abstract SKYLINKMediaState
 @description The state of the SkylinkMedia object.
 @constant SKYLINKMediaStateUnavailable Unavailable.
 @constant SKYLINKMediaStateActive Cuurently active.
 @constant SKYLINKMediaStateMuted The media is muted.
 @constant SKYLINKMediaStateStopped The media stopped.
 @warning SKYLINKMediaStateUnavailable is only provided from SDK to the user, it is NOT valid for user to supply as an SDK API parameter
 */
typedef enum SKYLINKMediaState {
    SKYLINKMediaStateUnavailable = 0,
    SKYLINKMediaStateActive,
    SKYLINKMediaStateMuted,
    SKYLINKMediaStateStopped
} SKYLINKMediaState;

/*!
@enum
@abstract SKYLINKMediaDevice
@description The device type when you create a new media
@constant Microphone
@constant Front camera
@constant Back camera
@constant Screen
@constant Custom camera
*/
typedef enum SKYLINKMediaDevice {
    SKYLINKMediaDeviceMicrophone = 0,
    SKYLINKMediaDeviceCameraFront,
    SKYLINKMediaDeviceCameraBack,
    SKYLINKMediaDeviceScreen,
    SKYLINKMediaDeviceCustom
} SKYLINKMediaDevice;

@interface SKYLINKMedia : NSObject

/*!
 @method
 @abstract Get the mediaID of the SkylinkMedia object.
 @discussion NoDis.
 @return The mediaID
 */
- (nonnull NSString *)skylinkMediaID;

/*!
 @method
 @abstract Get the media type.
 @discussion NoDis.
 @return The media type
 */
- (SKYLINKMediaType)skylinkMediaType;

/*!
 @method
 @abstract Gte the current media state.
 @discussion NoDis.
 @return The media state
 */
- (SKYLINKMediaState)skylinkMediaState;

/*!
 @method
 @abstract Get the previous media state.
 @discussion NoDis.
 @return The previous media state
 */
- (SKYLINKMediaState)skylinkPreviousMediaState;

/*!
 @method
 @abstract Get the video track if this media is an video.
 @discussion NoDis.
 @return The video track, if this is media is a video
 */
- (nullable RTCVideoTrack *)skylinkVideoTrack;

/*!
 @method
 @abstract Get the audio track if this media is an audio.
 @discussion NoDis.
 @return The audio track, if this is media is an audio
 */
- (nullable RTCAudioTrack *)skylinkAudioTrack;

/*!
 @method
 @abstract The video view contained in the media.
 @discussion NoDis.
 @return The video view
 */
- (nullable UIView *)skylinkVideoView;

/*!
 @method
 @abstract Check if this SkylinkMedia represents a video.
 @discussion NoDis.
 @return If this media is a video
 */
- (BOOL)isVideo;

/*!
 @method
 @abstract Check if this SkylinkMedia is a custom video.
 @discussion NoDis.
 @return If this media is a custom video
 */
- (BOOL)isCustom;

/*!
 @method
 @abstract This is a decription of the local media.
 @discussion Such as camera 1, USB camera, etc.
 @return The label string
 */
- (nullable id)skylinkMediaMetaData;

/*!
 @method
 @abstract Get the custom video capturer.
 @discussion NoDis.
 @return The custom video capturer or nil
 */
- (nullable RTCCameraVideoCapturer *)getCustomVideoCapturer;
@end


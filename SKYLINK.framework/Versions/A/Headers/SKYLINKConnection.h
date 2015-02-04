//
//  TEMAConnectionManager.h
//
//  Created by TemaSys on 01/02/2015.
//  Copyright (c) 2015 TemaSys. All rights reserved.
//

/**
 @typedef SKYLINKAssetType
 @brief Asset types to help the framework read the the files.
 @constant SKYLINKAssetTypeFile Files within the app sandbox.
 @constant SKYLINKAssetTypeMusic Files from the music library.
 @constant SKYLINKAssetTypePhoto Photo and Video content from the Photo Library.
 */
typedef enum SKYLINKAssetType {
    SKYLINKAssetTypeFile = 1,
    SKYLINKAssetTypeMusic,
    SKYLINKAssetTypePhoto
} SKYLINKAssetType;

@class UIView;
@class SKYLINKConnection;

// All the messages of the following protocols are sent on the main thread

/**
 @discussion The delegate to receive events related to the lifecycle of the connection.
 */
@protocol SKYLINKConnectionLifeCycleDelegate <NSObject>

@optional

/** First message sent to the delegate upon successful or unsuccessful connection.
 @param connection The underlying connection object.
 @param errorMessage Error message in case the connection is unsuccessful.
 @param isSuccess Flag to specify whether the connection was successful.
 */
- (void)connection:(SKYLINKConnection*)connection didConnectWithMessage:(NSString*)errorMessage success:(BOOL)isSuccess;

/** Upon successful capturing and rendering of the local front camera.
 @param connection The underlying connection object.
 @param userVideoView The video view of the connecting client.
 */
- (void)connection:(SKYLINKConnection*)connection didRenderUserVideo:(UIView*)userVideoView;

/** When a peer receives a warning from the underlying system.
 @param connection The underlying connection object.
 @param message Warning message from the underlying system.
 */
- (void)connection:(SKYLINKConnection*)connection didReceiveWarning:(NSString*)message;

/** When the client is disconnected from the server.
 @param connection The underlying connection object.
 @param errorMessage Message specifying the reason of disconnection.
 */
- (void)connection:(SKYLINKConnection*)connection didDisconnectWithMessage:(NSString*)errorMessage;

@end

/**
 @discussion The delegate to receive events related to remote peers.
 */
@protocol SKYLINKConnectionRemotePeerDelegate <NSObject>

@optional

/** When a remote peer joins the room.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param peerId The unique id of the joining peer.
 */
- (void)connection:(SKYLINKConnection*)connection didJoinPeer:(id)userInfo peerId:(NSString*)peerId;

/** Upon receiving a remote video stream.
 @param connection The underlying connection object.
 @param peerVideoView The video view of the joining peer.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didRenderPeerVideo:(UIView*)peerVideoView peerId:(NSString*)peerId;

/** Upon receiving an update about a user info.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didReceiveUserInfo:(id)userInfo peerId:(NSString*)peerId;

/** When a peer has left the room implictly or explicitly.
 @param connection The underlying connection object.
 @param errorMessage Error message in case the peer is left due to some error.
 @param peerId The unique id of the leaving peer.
 */
- (void)connection:(SKYLINKConnection*)connection didLeavePeerWithMessage:(NSString*)errorMessage peerId:(NSString*)peerId;

@end

/**
 @discussion The delegate to receive events related to media i.e. audio/video.
 */
@protocol SKYLINKConnectionMediaDelegate <NSObject>

@optional

/** When the dimension of the video view are changed.
 @param connection The underlying connection object.
 @param videoSize The size of the respective video.
 @param videoView The video view for which the size was sent.
 */
- (void)connection:(SKYLINKConnection*)connection didChangeVideoSize:(CGSize)videoSize videoView:(UIView*)videoView;

/** When a peer mutes/unmutes its audio.
 @param connection The underlying connection object.
 @param isMuted Flag to specify whether the audio is muted.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didToggleAudio:(BOOL)isMuted peerId:(NSString*)peerId;

/** When a peer mutes/unmutes its video.
 @param connection The underlying connection object.
 @param isMuted Flat to specify whether the video is muted.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didToggleVideo:(BOOL)isMuted peerId:(NSString*)peerId;

@end

/**
 @discussion The delegate to receive events related to remote peer messages.
 */
@protocol SKYLINKConnectionMessagesDelegate <NSObject>

@optional

/** Upon receiving a private or public message.
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didReceiveCustomMessage:(id)message public:(BOOL)isPublic peerId:(NSString*)peerId;

/** Upon receiving a data channel chat message.
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didReceiveDCMessage:(id)message public:(BOOL)isPublic peerId:(NSString*)peerId;

@end

/**
 @discussion The delegate to receive events related to file transfer.
 */
@protocol SKYLINKConnectionFileTransferDelegate <NSObject>

@optional

/** Upon receiving a file transfer request from the peer.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didReceiveRequest:(NSString*)filename peerId:(NSString*)peerId;

/** Upon receiving a file transfer permission from the peer.
 @param connection The underlying connection object.
 @param isPermitted Flag to specify whether the the request was accepted.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didReceivePermission:(BOOL)isPermitted filename:(NSString*)filename peerId:(NSString*)peerId;

/** When the file being transferred is halted.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param message The message specifying reason for the file transfer drop.
 @param isExplicit Flag to specify whether the transfer was halted explicity by the sender.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didDropTransfer:(NSString*)filename reason:(NSString*)message isExplicit:(BOOL)isExplicit peerId:(NSString*)peerId;

/** Upon file transfer completion.
 @param connection The underlying connection object.
 @param filename The name of the file in request.
 @param fileData NSData object holding the data transferred.
 @param peerId The unique id of the peer.
 */
- (void)connection:(SKYLINKConnection*)connection didCompleteTransfer:(NSString*)filename fileData:(NSData*)fileData peerId:(NSString*)peerId;

@end

/**
 @discussion The class representing the conversation configuration.
 */
@interface SKYLINKConnectionConfig : NSObject

/**
 @brief enable/disable audio.
 */
@property (nonatomic, unsafe_unretained) BOOL audio;
/**
 @brief enable/disable video.
 */
@property (nonatomic, unsafe_unretained) BOOL video;
/**
 @brief enable/disable dataChannel.
 */
@property (nonatomic, unsafe_unretained) BOOL dataChannel;
/**
 @brief enable/disable file transfer.
 */
@property (nonatomic, unsafe_unretained) BOOL fileTransfer;
/**
 @brief Number of seconds for file transfer timeout.
 */
@property (nonatomic, unsafe_unretained) NSInteger timeout;
/**
 @brief Configuration for advanced users.
 @discussion For now the system accepts turning on/off STUN and TURN servers via STUN=true/false and TURN=true/false. Transport can be set as transport=TCP/UDP.
 */
@property (nonatomic, weak) NSDictionary *userInfo;

@end

/**
 @discussion The class representing the connection to the room.
 */
@interface SKYLINKConnection : NSObject

/**
 @name Delegates
 */

/**
 @brief delegate related to life cycle.
 */
@property(nonatomic, weak) id<SKYLINKConnectionLifeCycleDelegate> lifeCycleDelegate;
/**
 @brief delegate related to remote peer activities.
 */
@property(nonatomic, weak) id<SKYLINKConnectionRemotePeerDelegate> remotePeerDelegate;
/**
 @brief delegate related to audio/video media.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMediaDelegate> mediaDelegate;
/**
 @brief delegate related to various type of custom messages.
 */
@property(nonatomic, weak) id<SKYLINKConnectionMessagesDelegate> messagesDelegate;
/**
 @brief delegate related to file transfer.
 */
@property(nonatomic, weak) id<SKYLINKConnectionFileTransferDelegate> fileTransferDelegate;

/**
 @name Lifecycle
 */

/** Initialize and return a newly allocated connection object.
 @discussion Changes in config after creating the object won't effect the connection itself.
 @param config The connection configuration object.
 @param apiKey API key.
 @param secret API secret.
 */
- (id)initWithConfig:(SKYLINKConnectionConfig*)config apiKey:(NSString*)apiKey secret:(NSString*)secret;

/** Join the room specifiying the name, starting time of the call and its duration in hours.
 @discussion Future meating support is coming soon. For now we encourage to pass any arbitrary NSDate object and any arbitrary positive value for 'startTime' and 'duration' respectively.
 @param roomName Name of the room to join.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param startTime Start time of the conversation, it will impact only if the user is the initiator of the conversation.
 @param duration Duration of the call, it will impact only if the user is the initiator of the conversation.
 @return NO if a connection is already established.
 */
- (BOOL)connectToRoom:(NSString*)roomName userInfo:(id)userInfo startTime:(NSDate*)startTime duration:(CGFloat)duration;

/** Leave the room.
 */
- (void)disconnect;

/**
 @name Media
 */

/** Mutes own audio and triggers mute audio call back at all participants.
 @param isMuted Flag to impare muted audio condition.
 */
- (void)muteAudio:(BOOL)isMuted;

/** Mutes own video and triggers mute video call back at all participants.
 @param isMuted Flag to impare muted video condition.
 */
- (void)muteVideo:(BOOL)isMuted;

/**
 @name Messaging
 */

/** Send a custom message (dictionary, array or string) to a remotePeer.
 @discussion If the 'remotePeerId' is not given it will be assumed as a broadcast message to all users.
 @param message User defined message to be sent to the peer. May be an NSString, NSDictionary or NSArray.
 @param peerId The unique id of the peer to whom the message would be sent.
 */
- (void)sendCustomMessage:(id)message peerId:(NSString*)peerId;

/** Send a message via data channel. 
 @discussion The message will be broadcasted to all the users if the remotePeerId is sent as 'nil'.
 @param message User defined message to be sent to the peer. May be an NSString, NSDictionary, NSArray.
 @param peerId The unique id of the peer to whome the message would be sent.
 */
- (void)sendDCMessage:(id)message peerId:(NSString*)peerId;

/**
 @name File Transfer
 */

/** This will trigger a file permission event on the remote peer.
 @param fileURL The url of the file to send.
 @param assetType The type of the asset to send.
 @param peerId The unique id of the peer to whom the file would be sent.
 @exception exception An exception will be raised if there is already a file transfer being done with the same peer.
 */
- (void)sendFileTransferRequest:(NSURL*)fileURL assetType:(SKYLINKAssetType)assetType peerId:(NSString*)peerId;

/** This will trigger a broadcast file permission event on the remote peer.
 @discussion If all the data channel connections are busy in some file transfer then this message will be ignored. If one or more data channel connections are not busy in some file transfer then this will trigger a broadcast file permission event on the available remote peers.
 @param fileURL The url of the file to send.
 @param assetType The type of the asset to send.
 */
- (void)sendFileTransferRequest:(NSURL*)fileURL assetType:(SKYLINKAssetType)assetType;

/** Accept or reject the file transfer request from the peer.
 @param accept Flag to specify whether the request is accepted.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer from whom the file data would be coming.
 */
- (void)acceptFileTransfer:(BOOL)accept filename:(NSString*)filename peerId:(NSString*)peerId;

/** Cancel the existing on going transfer at anytime.
 @param filename The name of the file in request.
 @param peerId The unique id of the peer from whom the file data is coming.
 */
- (void)cancelFileTransfer:(NSString*)filename peerId:(NSString*)peerId;

/**
 @name Miscellaneous
 */

/** Updates user information for every peer and triggers user info call back at remote peer's end.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 */
- (void)sendUserInfo:(id)userInfo;

/** Let the SDK know that the interface orientation of the application has been changed.
 @discussion One should call this function to let the SDK know about the interface rotation changes so that the SDK can adjust the self video capturing accordingly.
 */
- (void)reportRotation;

/** Get the cached user info for a particular peer.
 @param peerId The unique id of the peer.
 @return User defined information. May be an NSString, NSDictionary or NSArray.
 */
- (id)getUserInfo:(NSString*)peerId;

@end

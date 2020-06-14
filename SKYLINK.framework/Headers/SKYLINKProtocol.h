/*!
 @header SKYLINKProtocol.h
 @abstract Copyright (c) 2015 Temasys. All rights reserved.
 @author Temasys
 */
#ifndef SKYLINKProtocol_h
#define SKYLINKProtocol_h

@class SKYLINKConnection, SKYLINKMedia;
// All the messages of the following protocols are sent on the main thread

/*!
 @protocol
 @abstract Protocol to receive events related to the lifecycle of the connection.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionLifeCycleDelegate <NSObject>

@optional

/*!
 @method
 @abstract First delegate method called on the delegate upon successful connection.
 @discussion If the connection is successfull, this method gets called just before the connection notifies the other peers in the room that the local user entered it.
 @param connection The underlying connection object.
 */
- (void)connectionDidConnectToRoomSuccessful:(nonnull SKYLINKConnection *)connection;

/*!
 @method
 @abstract First delegate method called on the delegate upon unsuccessful connection.
 @discussion If the connection is successfull, this method gets called just before the connection notifies the other peers in the room that the local user entered it.
 @param connection The underlying connection object.
 @param errorMessage Error message in case the connection is unsuccessful.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didConnectToRoomFailed:(null_unspecified NSString *)errorMessage;

/*!
 @method
 @abstract Called when a remote peer locks/unlocks the room.
 @param connection The underlying connection object.
 @param lockStatus The status of the lock.
 @param remotePeerId The unique id of the peer who originated the action.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didLockTheRoom:(BOOL)lockStatus remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called when an info is received from the underlying system.
 @param connection The underlying connection object.
 @param skylinkInfo SkylinkInfo dictionary contains a code and a message from the underlying system.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveInfoWithSkylinkInfo:(null_unspecified NSDictionary *)skylinkInfo;

/*!
 @method
 @abstract Called when a warning is received from the underlying system.
 @param connection The underlying connection object.
 @param error Error which contain warning message inside userInfo.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveWarningWithError:(null_unspecified NSError *)error;

/*!
 @method
 @abstract Called when a error is received from the underlying system.
 @param connection The underlying connection object.
 @param error Error from the underlying system.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveError:(null_unspecified NSError *)error;

/*!
 @method
 @abstract Called when the client is disconnected from the server.
 @param connection The underlying connection object.
 @param skylinkEvent Is Error/Info.
 @param contextDescription Extra description.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didDisconnectFromRoomWithSkylinkEvent:(nullable NSDictionary *)skylinkEvent contextDescription:(nullable NSString*)contextDescription;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to remote peers.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionRemotePeerDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called when receive info about remote Peer that just joined the room.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param remotePeerId The unique id of the joining peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRemotePeerInRoomWithRemotePeerId:(nonnull NSString *)remotePeerId userInfo:(null_unspecified id)userInfo;

/*!
 @method
 @abstract Called when a remote peer joins the room.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param remotePeerId The unique id of the joining peer.
 @param hasDataChannel In case the peer enable data channel?
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didConnectWithRemotePeer:(null_unspecified NSString *)remotePeerId userInfo:(null_unspecified id)userInfo hasDataChannel:(BOOL)hasDataChannel;

/*!
 @method
 @abstract Called when receive info about a remote Peer that just refreshed its connection with us.
 @param connection The underlying connection object.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param remotePeerId The unique id of the joining peer.
 @param isIceRestarted Inccase the peer enable iceRestart?
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didRefreshRemotePeerConnection:(null_unspecified NSString *)remotePeerId userInfo:(null_unspecified id)userInfo hasDataChannel:(BOOL)hasDataChannel isIceRestarted:(BOOL)isIceRestarted;

/*!
 @method
 @abstract Called upon receiving an update about a user Data.
 @param connection The underlying connection object.
 @param userData User data. May be user name.
 @param remotePeerId The unique id of the remote peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRemotePeerUserData:(null_unspecified id)userData remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon receiving an update about a user info.
 @param connection The underlying connection object.
 @param remotePeerId The unique id of the remote peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didOpenRemotePeerDataConnection:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Receive info about remote Peer that just disconnected with us.
 @param connection The underlying connection object.
 @param remotePeerId The unique id of the peer.
 @param userInfo User defined information. May be an NSString, NSDictionary or NSArray.
 @param hasDataChannel In case the peer enable data channel?
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didDisconnectWithRemotePeer:(nonnull NSString *)remotePeerId userInfo:(null_unspecified id)userInfo hasDataChannel:(BOOL)hasDataChannel;

/*!
 @method
 @abstract Receive info about remote Peer that just left the room.
 @param connection The underlying connection object.
 @param remotePeerId The unique id of the remote peer.
 @param userInfo User info.
 @param skylinkInfo SkylinkInfo dictionary contains a code and a message from the underlying system.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRemotePeerLeaveRoom:(null_unspecified NSString *)remotePeerId userInfo:(null_unspecified id)userInfo skylinkInfo:(nullable NSDictionary *)skylinkInfo;

/*!
 @method
 @abstract Called when receive info about remote Peer whose connection with us has broken. This allows user the opportunity to decide how to respond, for e.g. user could choose to reconnect to room or refresh connection with remote Peer.
 @param connection The underlying connection object.
 @param error Error in case the connection is unsuccessful.
 @param remotePeerId The unique id of the remote peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didErrorForRemotePeerConnection:(nullable NSError *)error remotePeerId:(null_unspecified NSString *)remotePeerId;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to media i.e. audio/video.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionMediaDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called when receive a local Media. Applies for all media type. Including audio and video.
 @param connection The underlying connection object.
 @param localMedia The newly created local Skylink media object.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didCreateLocalMedia:(nonnull SKYLINKMedia *)localMedia;

/*!
 @method
 @abstract Called when receive a Media from remote peer. Applies for all media type. Including audio and video.
 @param connection The underlying connection object.
 @param remoteMedia The received remote Skylink media object.
 @param remotePeerId The received remote peerId.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRemoteMedia:(nonnull SKYLINKMedia *)remoteMedia remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called when local media changed.
 @param connection The underlying connection object.
 @param localMedia The Skylink local media object that is changed.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeLocalMedia:(nonnull SKYLINKMedia *)localMedia;

/*!
 @method
 @abstract Called when remote media changed.
 @param connection The underlying connection object.
 @param remoteMedia The Skylink remote media object that is changed.
 @param remotePeerId The unique id of the remote peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeRemoteMedia:(nonnull SKYLINKMedia *)remoteMedia remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called when the dimensions of the video view are changed.
 @param connection The underlying connection object.
 @param videoSize The size of the respective video.
 @param videoView The video view for which the size was sent.
 @param peerId The unique id of peer.
 @param mediaId The unique id of video media.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didChangeVideoSize:(CGSize)videoSize videoView:(null_unspecified UIView *)videoView peerId:(null_unspecified NSString *)peerId mediaId:(null_unspecified NSString *)mediaId;

/*!
 @method
 @abstract Called when the local peer's input stats are changed
 @param connection The underlying connection object.
 @param captureFormatDict The stats dictionary
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param mediaId The id of media
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didObtainInputVideoResolutionWidth:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps captureFormatDict:(nonnull NSDictionary<NSString *, id> *)captureFormatDict mediaId:(nonnull NSString*)mediaId;

/*!
 @method
 @abstract Called when the received stats are changed from a remote peer
 @param connection The underlying connection object.
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param remotePeerID The peer id for the input stats
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didObtainReceivedVideoResolutionWidth:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps remotePeerID:(nonnull NSString *)remotePeerID;

/*!
 @method
 @abstract Called when the sent stats are changed to a remote peer
 @param connection The underlying connection object.
 @param width The video width
 @param height The video height
 @param fps The video frame rate
 @param remotePeerId The peer id for the input stats
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didObtainSentVideoResolutionWidth:(NSInteger)width height:(NSInteger)height fps:(NSInteger)fps mediaId:(nonnull)mediaId remotePeerId:(nonnull NSString *)remotePeerId;

/*!
@method
@abstract Called when local Media was destroyed.
@param connection The underlying connection object.
@param localMedia The newly created local Skylink media object.
*/
- (void)connection:(nonnull SKYLINKConnection *)connection didDestroyLocalMedia:(nonnull SKYLINKMedia *)localMedia;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to remote peer messages.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionMessagesDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon receiving a socket message (Signalling).
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveServerMessage:(null_unspecified id)message isPublic:(BOOL)isPublic timeStamp:(long long)timeStamp remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon receiving a P2P message (DataChannel).
 @param connection The underlying connection object.
 @param message User defined message. May be an NSString, NSDictionary or NSArray.
 @param isPublic Flag to specify whether the message was a broadcast.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveP2PMessage:(null_unspecified id)message isPublic:(BOOL)isPublic timeStamp:(long long)timeStamp remotePeerId:(null_unspecified NSString *)remotePeerId;


/*!
 @method
 @abstract Called upon receiving binary data on data channel.
 @param connection The underlying connection object.
 @param data Binary data.
 @param remotePeerId The unique id of the remote peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveData:(null_unspecified NSData *)data remotePeerId:(null_unspecified NSString *)remotePeerId;

@end

/*!
 @protocol
 @abstract Protocol to receive events related to file transfer.
 @discussion Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionFileTransferDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon receiving a request to accept a File from remote Peer.
 @param connection The underlying connection object.
 @param fileName The name of the file in request.
 @param isPublic accessibility of file.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveFileTransferRequest:(null_unspecified NSString *)fileName isPublic:(BOOL)isPublic remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon receiving a response to our request to send a File to remote Peer.
 @param connection The underlying connection object.
 @param wasAccepted Flag to specify whether the request was accepted.
 @param fileName The name of the file in request.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveFileTransferResponse:(BOOL)wasAccepted fileName:(null_unspecified NSString *)fileName remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called when receive signal that File transfer was stopped before completing.
 @param connection The underlying connection object.
 @param fileName The name of the file in request.
 @param message The message specifying reason for the file transfer drop.
 @param isExplicit Flag to specify whether the transfer was halted explicity by the sender.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didDropFileTransfer:(null_unspecified NSString *)fileName message:(null_unspecified NSString *)message isExplicit:(BOOL)isExplicit remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon every file transfer progress update.
 @param connection The underlying connection object.
 @param percentage The perccentage representing the progress of the transfer (CGFloat from 0 to 1).
 @param fileName The name of the file in transmission.
 @param remotePeerId The unique id of the peer thie file is sent to or received from.
 @discussion Alternatively, if many of your objects need to get these informations, it can register to the notification with identifier: @"SKYLINKFileProgress".
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didUpdateFileTransferSendingProgress:(CGFloat)percentage fileName:(null_unspecified NSString *)fileName remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon every file transfer progress update.
 @param connection The underlying connection object.
 @param percentage The perccentage representing the progress of the transfer (CGFloat from 0 to 1).
 @param fileName The name of the file in transmission.
 @param remotePeerId The unique id of the peer thie file is sent to or received from.
 @discussion Alternatively, if many of your objects need to get these informations, it can register to the notification with identifier: @"SKYLINKFileProgress".
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didUpdateFileTransferReceivingProgress:(CGFloat)percentage fileName:(null_unspecified NSString *)fileName remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
 @method
 @abstract Called upon receiving signal that our sending of a File to remote Peer is complete.
 @param connection The underlying connection object.
 @param fileName The name of the file in request.
 @param remotePeerId The unique id of the peer.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didCompleteFileTransferSending:(null_unspecified NSString *)fileName remotePeerId:(null_unspecified NSString *)remotePeerId;

/*!
@method
@abstract Called upon receiving signal that our receipt of a File from remote Peer is complete
@param connection The underlying connection object
@param fileName The name of the file in request
@param fileData The data of the received file
@param fileSavePath The path where the file is saved, it is in the sandbox /tmp folder
@param remotePeerId The unique id of the peer
*/
- (void)connection:(nonnull SKYLINKConnection *)connection didCompleteFileTransferReceiving:(null_unspecified NSString *)fileName fileData:(null_unspecified NSData *)fileData fileSavePath:(null_unspecified NSString *)fileSavePath remotePeerId:(null_unspecified NSString *)remotePeerId;

@end

/*!
 @protocol
 @abstract Protocol to receive backend events related to room recording (BETA).
 @discussion This works only on Skylink Media Relay enabled App Keys. Delegate methods are called on the main thread.
 */
@protocol SKYLINKConnectionRecordingDelegate <NSObject>

@optional

/*!
 @method
 @abstract Called upon recording start event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingID The id of the generated recording.
 @discussion This will be triggered after you call startRecording successfully.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didStartRecordingWithID:(null_unspecified NSString *)recordingID;

/*!
 @method
 @abstract Called upon recording stop event.
 @discussion This will be triggered after you call stopRecording successfully or if the backend notifies of recording stoped.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingID The id of the recording.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didStopRecordingWithID:(null_unspecified NSString *)recordingID;

/*!
 @method
 @abstract Called upon recording error event.
 @warning This feature is in BETA.
 @param connection The underlying connection object.
 @param recordingId The id of the recording (might be nil if unknown).
 @param error Error in case the connection is unsuccessful.
 */
- (void)connection:(nonnull SKYLINKConnection *)connection didReceiveRecordingError:(nullable NSError *)error recordingId:(null_unspecified NSString *)recordingId;

@end

#endif /* SKYLINKProtocol_h */

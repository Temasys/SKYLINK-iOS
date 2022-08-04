//
//  SkylinkMessageCache.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Lakindu Boteju on 2022-07-30.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "WritableCacheSession.h"
#import "ReadableCacheSession.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Interfacing class that user needs to use the Skylink message caching feature.
 A singleton class.
 */
@interface SkylinkMessageCache : NSObject {
    NSPersistentContainer * persistentContainer;
    NSMutableDictionary * writableCacheSessions;
    NSMutableDictionary * readableCacheSessions;
}

/**
 Is message caching feature is enabled?
 Message caching can be enabled using SKYLINKConnectionConfig.isMessageCacheEnabled property.
 Message caching enabled SKYLINKConnectionConfig object should be provided
 during SKYLINKConnection.initWithConfig:(SKYLINKConnectionConfig *) callback:(ErrorBlock) call to successfully the feature.
 */
@property (nonatomic, readonly) BOOL isEnabled;

/**
 Maximum number of messages to store in cache per Skylink room.
 */
@property (nonatomic, readonly) NSInteger cacheLimit;

/**
 Class method to get singleton instance of the SkylinkMessageCache class.
 */
+ (instancetype) instance;

/**
 Initializes and enables SkylinkMessageCache.
 enable must be called before user use SkylinkMessageCache instance to cache messages or get cached messages.
 This method will be invoked by the SKYLINK SDK during SKYLINKConnection.initWithConfig:(SKYLINKConnectionConfig *) callback:(ErrorBlock).
 @param maxNumbOfMessagesToCachePerRoom The maximum number of messages to store in cache per Skylink room.
 */
- (void) enableWithMaxNumbOfMessagesToCachePerRoom:(NSInteger)maxNumbOfMessagesToCachePerRoom;

/**
 Gets writable cache session that user can use to write to cache or delete from cache.
 @param roomName Skylink room name
 @return WritableCacheSession object that user can use to write to cache or delete from cache.
 */
- (WritableCacheSession *) getWritableCacheSessionForRoomName:(NSString *)roomName;

/**
 Gets readable cache session that user can use to read from cache.
 @param roomName Skylink Room name
 @return ReadableCacheSession object that user can use to read cached messages.
 */
- (ReadableCacheSession *) getReadableCacheSessionForRoomName:(NSString *)roomName;

/**
 Clears the cached room information and the cached messages of the room.
 Presence of the entire room will be removed from the local cache.
 @param roomName Skylink Room name
 */
- (void) clearRoomWithRoomName:(NSString *)roomName;

/**
 Clears full local cache.
 Deletes all caches messages and room information.
 */
- (void) clearAll;

@end

NS_ASSUME_NONNULL_END

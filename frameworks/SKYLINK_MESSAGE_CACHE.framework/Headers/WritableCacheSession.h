//
//  WritableCacheSession.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Lakindu Boteju on 2022-07-31.
//

#import "CacheSession.h"

NS_ASSUME_NONNULL_BEGIN

@interface WritableCacheSession : CacheSession

- (id) initWithRoomName:(NSString *)roomName
   managedObjectContext:(NSManagedObjectContext *)context
    maxNumbOfMessagesToCachePerRoom:(NSInteger)maxNumbOfMessagesToCachePerRoom;

- (void) cacheMessageWithMsgId:(NSString *)msgId data:(NSString *)data timestamp:(long)timestamp;
- (void) saveIfHasChanges;

/**
 Clears cached messages of the room.
 Cached room information will remain.
 To clear both cached room information and cached messages SkylinkMessageCache.clearRoomWithRoomName:(NSString *) method can be used.
 To clear full local cache (all cached room information and all cached messages) SkylinkMessageCache.clearAll method can be used.
 */
- (void) clearCachedMessages;

@end

NS_ASSUME_NONNULL_END

//
//  WritableCacheSession.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Temasys on 2022-08-16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WritableCacheSession

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

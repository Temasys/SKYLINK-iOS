//
//  ReadableCacheSession.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Lakindu Boteju on 2022-08-01.
//

#import "CacheSession.h"

NS_ASSUME_NONNULL_BEGIN

@interface ReadableCacheSession : CacheSession

- (id) initWithRoomName:(NSString *)roomName managedObjectContext:(NSManagedObjectContext *)context;

/**
 Gets cached messages in a NSArray object.
 @return NSArray object contains cached messages (as NSDictionary objects).
 */
- (NSArray *) cachedMessages;

@end

NS_ASSUME_NONNULL_END

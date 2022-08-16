//
//  ReadableCacheSession.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Temasys on 2022-08-16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ReadableCacheSession

/**
 Gets cached messages in a NSArray object.
 @return NSArray object contains cached messages (as NSDictionary objects).
 */
- (NSArray *) cachedMessages;

@end

NS_ASSUME_NONNULL_END

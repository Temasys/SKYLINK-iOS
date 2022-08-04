//
//  Session.h
//  SKYLINK-MESSAGE-CACHE
//
//  Created by Lakindu Boteju on 2022-07-31.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

NS_ASSUME_NONNULL_BEGIN

@interface CacheSession : NSObject {
}

- (id) initWithRoomName:(NSString *)roomName managedObjectContext:(NSManagedObjectContext *)context;

@end

NS_ASSUME_NONNULL_END

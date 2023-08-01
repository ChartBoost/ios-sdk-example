//
//  Chartboost.h
//  Chartboost
//
//  Copyright 2021 Chartboost. All rights reserved.
//

#import <ChartboostSDK/CHBAd.h>

NS_ASSUME_NONNULL_BEGIN

/*!
CHBAdEvent is a NSObject subclass, it contains information about a specific event and is related to an ad.
# Discussion #
In the SDK exists various types of CHBAdEvent are related to the Ad Delegate callbacks.
- CHBCacheEvent
- CHBShowEvent
- CHBImpressionEvent
- CHBClickEvent
- CHBDismissEvent
- CHBRewardEvent
*/
@interface CHBAdEvent : NSObject

/*!
The ad related to the event.
*/
@property (nonatomic, readonly) id<CHBAd> ad;

/*!
A string that uniquely identifies the cached ad, updated when a cache operation ends.
*/
@property (nonatomic, readonly, nullable) NSString *adID;
@end

/*!
A CHBAdEvent subclass passed on cache-related delegate methods.
*/
@interface CHBCacheEvent : CHBAdEvent
@end

/*!
A CHBAdEvent subclass passed on show-related delegate methods.
*/
@interface CHBShowEvent : CHBAdEvent
@end

/*!
A CHBAdEvent subclass passed on impression-related delegate methods.
*/
@interface CHBImpressionEvent : CHBAdEvent
@end

/*!
A CHBAdEvent subclass passed on click-related delegate methods.
*/
@interface CHBClickEvent : CHBAdEvent
@end

/*!
A CHBAdEvent subclass passed on dismiss-related delegate methods.
*/
@interface CHBDismissEvent : CHBAdEvent

/*!
The error that forced the ad dismissal, or nil if the user (or the ad itself) chose to dismiss the ad.
*/
@property (nonatomic, readonly, nullable) NSError *error;
@end

/*!
A CHBAdEvent subclass passed on reward-related delegate methods.
*/
@interface CHBRewardEvent : CHBAdEvent

/*!
The earned reward.
*/
@property (nonatomic, readonly) NSInteger reward;
@end

NS_ASSUME_NONNULL_END

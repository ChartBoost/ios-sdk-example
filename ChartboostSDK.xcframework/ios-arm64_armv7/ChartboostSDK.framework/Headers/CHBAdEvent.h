//
//  Chartboost.h
//  Chartboost
//
//  Copyright 2021 Chartboost. All rights reserved.
//

#import <ChartboostSDK/CHBAd.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class CHBAdEvent
 @brief The base class from which all delegate events inherit from.
 @discussion Event objects are passed as parameters to all ad delegate methods to provide useful context.
 */
@interface CHBAdEvent : NSObject
/*!
 @brief The ad related to the event.
 */
@property (nonatomic, readonly) id<CHBAd> ad;
/*!
 @brief A string that uniquely identifies the cached ad, updated when a cache operation ends.
 */
@property (nonatomic, readonly, nullable) NSString *adID;
@end

/*!
 @class CHBCacheEvent
 @brief A CHBAdEvent subclass passed on cache-related delegate methods.
 */
@interface CHBCacheEvent : CHBAdEvent
@end

/*!
 @class CHBShowEvent
 @brief A CHBAdEvent subclass passed on show-related delegate methods.
 */
@interface CHBShowEvent : CHBAdEvent
@end


/*!
 @class CHBImpressionEvent
 @brief A CHBAdEvent subclass passed on impression-related delegate methods.
 */
@interface CHBImpressionEvent : CHBAdEvent
@end

/*!
 @class CHBClickEvent
 @brief A CHBAdEvent subclass passed on click-related delegate methods.
 */
@interface CHBClickEvent : CHBAdEvent
@end

/*!
 @class CHBDismissEvent
 @brief A CHBAdEvent subclass passed on dismiss-related delegate methods.
 */
@interface CHBDismissEvent : CHBAdEvent
/*!
@brief The error that forced the ad dismissal, or nil if the user (or the ad itself) chose to dismiss the ad.
*/
@property (nonatomic, readonly, nullable) NSError *error;
@end

/*!
 @class CHBRewardEvent
 @brief A CHBAdEvent subclass passed on reward-related delegate methods.
 */
@interface CHBRewardEvent : CHBAdEvent
/*!
 @brief The earned reward.
 */
@property (nonatomic, readonly) NSInteger reward;
@end

NS_ASSUME_NONNULL_END

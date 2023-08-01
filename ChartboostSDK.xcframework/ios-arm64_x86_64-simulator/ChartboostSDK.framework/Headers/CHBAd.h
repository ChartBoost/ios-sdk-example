/*
 * CHBAd.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <UIKit/UIKit.h>

@protocol CHBAdDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
The protocol to which all Chartboost ads conform to.
# Discussion #
Provides an interface for basic functionalities common to all ads.
*/
@protocol CHBAd <NSObject>

/*!
The delegate instance to receive ad callbacks.
 */
@property (nonatomic, weak, nullable) id<CHBAdDelegate> delegate;

/*!
Chartboost location for the ad.
# Discussion #
Used to obtain ads with increased performance.
 */
@property (nonatomic, readonly) NSString *location;

/*!
Determines if a cached ad exists.
- returns: YES if there is a cached ad, and NO if not.
*/
@property (nonatomic, readonly) BOOL isCached;

/*!
Caches an ad.
# Discussion #
- This method will first check if there is a cached ad and, if found, will do nothing.
- If no cached ad exists the method will attempt to fetch it from the Chartboost server.
- Implement didCacheAd:error: in your ad delegate to be notified of a cache request result.
*/
- (void)cache;

/*!
Caches an ad using an OpenRTB bid response.
# Discussion #
- Use this method if you want to cache an ad using a winning bid obtained from the Chartboost bidder.
- Use the isCached property or implement didCacheAd:error: in your ad delegate to be notified of a cache request result.
- parameter bidResponse: A bid response containing information about the ad to cache in OpenRTB format.
*/
- (void)cacheBidResponse:(NSString *)bidResponse NS_SWIFT_NAME(cache(bidResponse:));

/*!
Clears the ad cache.
# Discussion #
 - This will do nothing if there's no cached ad. Otherwise it will remove any data
 related to the ad, bringing the ad instance back to a non-cached state.
 After calling this method you may call `cache` again and a new ad will be fetched.
 */
- (void)clearCache;

/*!
Shows an ad.
# Discussion #
- This method will first check if there is a cached ad, if found it will present it.
- Passing a non-nil view controller is required.
- parameter viewController: The view controller to present the ad on.
*/
- (void)showFromViewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END

//
//  CHBRewarded.h
//  Chartboost
//
//  Copyright 2021 Chartboost. All rights reserved.
//

#import <ChartboostSDK/CHBAd.h>
#import <ChartboostSDK/CHBAdDelegate.h>
#import <ChartboostSDK/CHBMediation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class CHBRewarded
 
 @brief CHBRewarded is a full-screen ad that provides some reward to the user.
 
 @discussion To show a rewarded ad it first needs to be cached. Trying to show an uncached rewarded ad will always fail, thus it is recommended to always check if the ad is cached first.
 
 You can create and cache as many rewarded ads as you want, but only one can be presented at the same time.
 
 A basic implementation would look like this:
 @code
 - (void)createAndCacheRewarded {
    self.rewarded = [[CHBRewarded alloc] initWithLocation:@"YOUR_LOCATION_NAME" delegate:self];
    [self.rewarded cache];
 }
 
 - (void)showRewarded {
    if (self.rewarded.isCached) {
        [self.rewarded showFromViewController:self];
    }
 }
 
 // Delegate methods
 
 - (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    if (error) {
        // Handle error, possibly scheduling a retry
    }
 }
 
 - (void)willShowAd:(CHBShowEvent *)event {
    // Pause ongoing processes
 }
 
 - (void)didShowAd:(CHBShowEvent *)event error:(CHBShowError *)error {
    if (error) {
        // Resume paused processes. Note that if showing the ad fails didEarnReward: will not be called.
    }
 }

 - (void)didDismissAd:(CHBDismissEvent *)event {
    // Resume paused processes
 }
 
 - (void)didEarnReward:(CHBRewardEvent *)event {
    // Update app state with event.reward
 }
 @endcode
 
 If your application uses a View controller-based status bar appearance (usually the default), an ad shown with a valid view controller will hide the status bar. Otherwise it is your responsibility to hide it or not.

 For more information on integrating and using the Chartboost SDK please visit our help site documentation at https://help.chartboost.com
 */
@interface CHBRewarded : NSObject <CHBAd>

/*!
 @brief Chartboost location for the ad.
 @discussion Used to obtain ads with increased performance.
 */
@property (nonatomic, readonly) NSString *location;

/*!
 @brief The delegate instance to receive rewarded ad callbacks.
 See CHBAdDelegate.h for more info.
 */
@property (nonatomic, weak, nullable) id<CHBRewardedDelegate> delegate;

/*!
 @brief Determines if a cached ad exists.
 @return YES if there is a cached ad, and NO if not.
 @discussion A return value of YES here indicates that it is safe to call the showFromViewController: method.
 Calling this method when this value is NO will cause the show request to fail with a CHBShowErrorCodeNoCachedAd error.
 */
@property (nonatomic, readonly) BOOL isCached;

/*!
 @brief The initializer for the rewarded ad object.
 @param location Location for the rewarded ad. See the location property documentation.
 @param delegate Delegate for the rewarded ad. See the delegate property documentation.
 */
- (instancetype)initWithLocation:(NSString *)location
                        delegate:(nullable id<CHBRewardedDelegate>)delegate;

/*!
 @brief The initializer for rewarded ads intended to be mediated by another SDK.
 @param location Location for the rewarded ad. See the location property documentation.
 @param mediation Information about the mediation SDK that is requesting this ad.
 @param delegate Delegate for the rewarded ad. See the delegate property documentation.
 @discussion Use this initializer only if you are writing an adapter to use Chartboost with another mediation solution.
 */
- (instancetype)initWithLocation:(NSString *)location
                       mediation:(nullable CHBMediation *)mediation
                        delegate:(nullable id<CHBRewardedDelegate>)delegate;

/*!
 @brief Please use -[CHBRewarded initWithLocation:delegate:] instead.
*/
- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Caches an ad.
 @discussion This method will first check if there is a cached ad and, if found, will do nothing.
 If no cached ad exists the method will attempt to fetch it from the Chartboost server.
 Implement didCacheAd:error: in your ad delegate to be notified of a cache request result.
 */
- (void)cache;

/*!
 @brief Caches an ad using an OpenRTB bid response.
 @param bidResponse A bid response containing information about the ad to cache in OpenRTB format.
 @discussion Use this method if you want to cache an ad using a winning bid obtained from the Chartboost bidder.
 Use the isCached property or implement didCacheAd:error: in your ad delegate to be notified of a cache request result.
*/
- (void)cacheBidResponse:(NSString *)bidResponse NS_SWIFT_NAME(cache(bidResponse:));

/*!
 @brief Clears the ad cache.
 @discussion This will do nothing if there's no cached ad. Otherwise it will remove any data
 related to the ad, bringing the ad instance back to a non-cached state. After calling this
 method you may call `cache` again and a new ad will be fetched.
 */
- (void)clearCache;

/*!
 @brief Shows an ad.
 @param viewController The view controller to present the ad on.
 @discussion This method will first check if there is a cached ad, if found it will present it.
 If no cached ad exists the request will fail with a CHBShowErrorCodeNoCachedAd error.
 Passing a non-nil view controller is required.
 Implement didShowAd:error: in your ad delegate to be notified of a show request result.
 */
- (void)showFromViewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END


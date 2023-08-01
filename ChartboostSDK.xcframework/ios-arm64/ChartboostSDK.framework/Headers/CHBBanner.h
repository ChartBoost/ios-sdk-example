/*
 * CHBBanner.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <ChartboostSDK/CHBAd.h>
#import <ChartboostSDK/CHBAdDelegate.h>
#import <ChartboostSDK/CHBMediation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
Defines standard sizes for CHBBanner objects.
# Discussion #
Standard sizes used to describe default banner bounds.
*/
typedef CGSize const CHBBannerSize;
/*! "Banner" - Standard banner size on phones. */
FOUNDATION_EXPORT CHBBannerSize const CHBBannerSizeStandard;
/*! "Medium Rect" - Medium banner size on phones. */
FOUNDATION_EXPORT CHBBannerSize const CHBBannerSizeMedium;
/*! "Tablet" - Leaderboard banner size on tablets. */
FOUNDATION_EXPORT CHBBannerSize const CHBBannerSizeLeaderboard;

/*!
CHBBanner is a UIView subclass able to show banner ads. Once obtained via the provided initializer, the
developer is responsible of adding it to the app's view hierarchy and laying it out properly.

A banner ad has a CHBBannerSize which corresponds to the view's intrinsicContentSize.
The developer should not give the banner view object a frame size different than its CHBBannerSize property.
If you are using AutoLayout just give the banner an X and Y position constraint and it will be automatically sized.

You can create and present as many banners as you want at the same time.
For more information on integrating and using the Chartboost SDK please visit our help site documentation at [Chartboost Helpsite](https://help.chartboost.com)
 
A typical implementation would look like this:
```objc
- (void)createAndShowBanner {
   CHBBanner *banner = [[CHBBanner alloc] initWithSize:CHBBannerSizeStandard location:@"YOUR_LOCATION_NAME" delegate:self];
   banner.translatesAutoresizingMaskIntoConstraints = NO;
   [self.view addSubview:banner];
   [NSLayoutConstraint activateConstraints:@[[banner.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor],
                                            [banner.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor]]];
   [banner showFromViewController:self];
}
```
*/
@interface CHBBanner : UIView <CHBAd>

/*!
Chartboost location for the ad.
# Discussion #
Used to obtain ads with increased performance.
*/
@property (nonatomic, readonly) NSString *location;

/*!
Size for the banner ad.
# Discussion #
- You should provide one of the predefined values.
- The `intrinsicContentSize` of the banner view will depend on this value.
*/
@property (nonatomic, readonly) CHBBannerSize size;

/*!
The delegate instance to receive banner callbacks.
# Discussion #
See CHBAdDelegate.h for more info.
*/
@property (nonatomic, weak, nullable) id<CHBBannerDelegate> delegate;

/*!
Determines if a cached ad exists.
# Discussion #
A return value of YES here indicates that a call to showFromViewController: will present without making additional Chartboost server requests to fetch data.
- returns: YES if there is a cached ad, and NO if not.
*/
@property (nonatomic, readonly) BOOL isCached;

/*!
The initializer for the banner object. Default UIView initializers should not be used!
- parameter size: Size for the banner. See the size property documentation.
- parameter location: Location for the banner. See the location property documentation.
- parameter delegate: Delegate for the banner. See the delegate property documentation.
*/
- (instancetype)initWithSize:(CHBBannerSize)size
                    location:(NSString *)location
                    delegate:(nullable id<CHBBannerDelegate>)delegate;

/*!
The initializer for banner ads intended to be mediated by another SDK.
# Discussion #
 Use this initializer only if you are writing an adapter to use Chartboost with another mediation solution.
- parameter size: Size for the banner. See the size property documentation.
- parameter location: Location for the banner ad. See the location property documentation.
- parameter mediation: Information about the mediation SDK that is requesting this ad.
- parameter delegate: Delegate for the banner ad. See the delegate property documentation.
*/
- (instancetype)initWithSize:(CHBBannerSize)size
                    location:(NSString *)location
                   mediation:(nullable CHBMediation *)mediation
                    delegate:(nullable id<CHBBannerDelegate>)delegate;

/*!
# Discussion #
Please use -[CHBBanner initWithLocation:size:delegate:] instead.
*/
- (instancetype)init NS_UNAVAILABLE;

/*!
Caches an ad.
# Discussion #
- This method will first check if there is a cached ad and, if found, will do nothing.
-  If no cached ad exists the method will attempt to fetch it from the Chartboost server.
-  Implement didCacheAd:error: in your ad delegate to be notified of a cache request result.
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
- related to the ad, bringing the ad instance back to a non-cached state. After calling this
- method you may call `cache` again and a new ad will be fetched.
*/
- (void)clearCache;

/*!
Shows an ad.
# Discussion #
- This method will first check if there is a cached ad, if found it will present it.
- If no cached ad exists the method will attempt to fetch it from the Chartboost server first.
- Passing a non-nil view controller is required.
- Implement ``(didShowAd:error:)`` in your ad delegate to be notified of a show request result, and ``(didCacheAd:error:)``  to be notified of the result of a cache request triggered by showing a non-cached banner.
- parameter viewController: The view controller to present the ad on.
*/
- (void)showFromViewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END

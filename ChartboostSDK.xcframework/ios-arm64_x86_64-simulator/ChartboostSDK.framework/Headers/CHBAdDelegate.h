/*
 * CHBAdDelegate.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <ChartboostSDK/CHBAdEvent.h>

NS_ASSUME_NONNULL_BEGIN
@class CHBCacheError;
@class CHBShowError;
@class CHBClickError;

/*!
The protocol which all Chartboost ad delegates inherit from.
# Discussion #
Provides methods to receive notifications related to an ad's actions and to control its behavior.
*/
@protocol CHBAdDelegate <NSObject>

@optional

/*!
Called after a cache call, either if an ad has been loaded from the Chartboost servers and cached, or tried to but failed.
# Discussion #
Implement to be notified of when an ad is ready to be shown after the cache method has been called.
- parameter event: A cache event with info related to the cached ad.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.
 
 A typical implementation would look like this:
 ```objc
 - (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    if (error) {
        // Handle error
    } else {
        // At this point event.ad.isCached will be true, and the ad is ready to be shown.
    }
 }
 ```
 */
- (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error;

/*!
Called after a showFromViewController: call, right before an ad is presented.
# Discussion #
Implement to be notified of when an ad is about to be presented.
- parameter event: A show event with info related to the ad to be shown.
A typical implementation would look like this:
```objc
- (void)willShowAd:(CHBShowEvent *)event {
   // Pause ongoing processes like video or gameplay.
}
```
*/
- (void)willShowAd:(CHBShowEvent *)event;

/*!
Called after a showFromViewController: call, either if the ad has been presented and an ad impression logged, or if the operation failed.
# Discussion #
- Implement to be notified of when the ad presentation process has finished.
- This method will be called once for each call to showFromViewController: on an interstitial or rewarded ad.
- In contrast, this may be called up to two times after showing a banner, if some error occurs after the ad has been successfully shown.

- parameter event: A show event with info related to the ad shown.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.

A common practice consists of caching an ad here so there's an ad ready for the next time you need to show it.
 ```objc
 - (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error {
    if (error) {
        // Handle error, possibly resuming processes paused in willShowAd:
    } else {
        [event.ad cache];
    }
 }
```
*/
- (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error;

/*!
Called after an ad has been clicked.
# Discussion #
- Implement to be notified of when an ad has been clicked.
- If the click does not result into the opening of a link an error will be provided explaning why.
 
- parameter event: A click event with info related to the ad clicked.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.
 
 A typical implementation would look like this:
 ```objc
 - (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    if (error) {
        // Handle error
    } else {
        // Maybe pause ongoing processes like video or gameplay when a banner ad is clicked.
    }
 }
 ```
*/
- (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error;

/*!
Called after an ad has recorded an impression.
# Discussion #
-  Implement to be notified of when an ad has recorded an impression.
- This method will be called once a valid impression is recorded after showing the ad.
- parameter event: An impression event with info related to the visible ad.
*/
- (void)didRecordImpression:(CHBImpressionEvent *)event;

@end

/*!
Delegate protocol for ads that can be dismissed.
# Discussion #
Provides methods to receive notifications related to an ad's actions and to control its behavior.
*/
@protocol CHBDismissableAdDelegate <CHBAdDelegate>

@optional

/*!
Called after an ad is dismissed.
# Discussion #
- Implement to be notified of when an ad is no longer displayed.
- Note that this method won't get called for ads that failed to be shown. To handle that case implement didShowAd:error:
- You may use the error property inside the event to know if the dismissal was expected or caused by an error.
 
- parameter event: A dismiss event with info related to the dismissed ad.

 A typical implementation would look like this:
 ```objc
 - (void)didDismissAd:(CHBDismissEvent *)event {
    // Resume processes paused in willShowAd:
 }
 ```
*/
- (void)didDismissAd:(CHBDismissEvent *)event;

@end

/*!
Interstitial delegate protocol.
# Discussion #
- Provides methods to receive notifications related to an interstitial ad behavior.
- In a typical integration you would implement willShowAd:, didShowAd: and didDismissAd:, pausing and resuming ongoing processes (e.g: gameplay, video) there.
*/
@protocol CHBInterstitialDelegate <CHBDismissableAdDelegate>
@end

/*!
Rewarded delegate protocol.
# Discussion #
- Provides methods to receive notifications related to a rewarded ad behavior.
- In a typical integration you would implement willShowAd:, didShowAd: and didDismissAd:, pausing and resuming ongoing processes (e.g: gameplay, video) there.
- The method didEarnReward: needs to be implemented in order to be notified when the user earns a reward.
*/
@protocol CHBRewardedDelegate <CHBDismissableAdDelegate>

@optional

/*!
Called when a rewarded ad has completed playing.
# Discussion #
Implement to be notified when a reward is earned.

- parameter event: A reward event with info related to the ad and the reward.
*/
- (void)didEarnReward:(CHBRewardEvent *)event;

@end

/*!
Banner delegate protocol.
# Discussion #
Provides methods to receive notifications related to a banner ad behavior.
*/
@protocol CHBBannerDelegate <CHBAdDelegate>

@optional

/*!
Called when the link viewer presented as result of an ad click has been dismissed.
# Discussion #
- Implement to be notified of when an ad click has been handled.
- This can mean an in-app web browser or App Store app sheet has been dismissed, or that the user came back to the app after the link was opened on an external application.

- parameter event: A click event with info related to the ad clicked.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.
 
 A typical implementation would look like this:
 ```objc
 - (void)didFinishHandlingClick:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    // Resume processes previously paused on didClickAd:error: implementation.
 }
 ```
*/

- (void)didFinishHandlingClick:(CHBClickEvent *)event error:(nullable CHBClickError *)error __attribute__((deprecated("Will be removed with the next major update")));

@end

NS_ASSUME_NONNULL_END

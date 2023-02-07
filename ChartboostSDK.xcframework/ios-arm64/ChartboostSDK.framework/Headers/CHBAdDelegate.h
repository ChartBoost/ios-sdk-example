/*
 * CHBAdDelegate.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <ChartboostSDK/CHBAdEvent.h>
#import <ChartboostSDK/CHBError.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @protocol CHBAdDelegate
 @brief The protocol which all Chartboost ad delegates inherit from.
 @discussion Provides methods to receive notifications related to an ad's actions and to control its behavior.
 */
@protocol CHBAdDelegate <NSObject>

@optional

/*!
 @brief Called after a cache call, either if an ad has been loaded from the Chartboost servers and cached, or tried to but failed.
 @param event A cache event with info related to the cached ad.
 @param error An error specifying the failure reason, or nil if the operation was successful.
 @discussion Implement to be notified of when an ad is ready to be shown after the cache method has been called.
 
 A typical implementation would look like this:
 @code
 - (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    if (error) {
        // Handle error
    } else {
        // At this point event.ad.isCached will be true, and the ad is ready to be shown.
    }
 }
 @endcode
 */
- (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error;

/*!
 @brief Called after a showFromViewController: call, right before an ad is presented.
 @param event A show event with info related to the ad to be shown.
 @discussion Implement to be notified of when an ad is about to be presented.
 
 A typical implementation would look like this:
 @code
 - (void)willShowAd:(CHBShowEvent *)event {
    // Pause ongoing processes like video or gameplay.
 }
 @endcode
 */
- (void)willShowAd:(CHBShowEvent *)event;

/*!
 @brief Called after a showFromViewController: call, either if the ad has been presented and an ad impression logged, or if the operation failed.
 @param event A show event with info related to the ad shown.
 @param error An error specifying the failure reason, or nil if the operation was successful.
 @discussion Implement to be notified of when the ad presentation process has finished.
 This method will be called once for each call to showFromViewController: on an interstitial or rewarded ad.
 In contrast, this may be called up to two times after showing a banner, if some error occurs after the ad has been successfully shown.
 
 A common practice consists of caching an ad here so there's an ad ready for the next time you need to show it.
 @code
 - (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error {
    if (error) {
        // Handle error, possibly resuming processes paused in willShowAd:
    } else {
        [event.ad cache];
    }
 }
 @endcode
 */
- (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error;

/*!
 @brief Called after an ad has been clicked.
 @param event A click event with info related to the ad clicked.
 @param error An error specifying the failure reason, or nil if the operation was successful.
 @discussion Implement to be notified of when an ad has been clicked.
 If the click does not result into the opening of a link an error will be provided explaning why.
 
 A typical implementation would look like this:
 @code
 - (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    if (error) {
        // Handle error
    } else {
        // Maybe pause ongoing processes like video or gameplay when a banner ad is clicked.
    }
 }
 @endcode
 */
- (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error;

/*!
 @brief Called after an ad has recorded an impression.
 @param event An impression event with info related to the visible ad.
 @discussion Implement to be notified of when an ad has recorded an impression.
 This method will be called once a valid impression is recorded after showing the ad.
 */
- (void)didRecordImpression:(CHBImpressionEvent *)event;

@end

/*!
 @protocol CHBDismissableAdDelegate
 @brief Delegate protocol for ads that can be dismissed.
 @discussion Provides methods to receive notifications related to an ad's actions and to control its behavior.
 */
@protocol CHBDismissableAdDelegate <CHBAdDelegate>

@optional

/*!
 @brief Called after an ad is dismissed.
 @param event A dismiss event with info related to the dismissed ad.
 @discussion Implement to be notified of when an ad is no longer displayed.
 Note that this method won't get called for ads that failed to be shown. To handle that case implement didShowAd:error:
 You may use the error property inside the event to know if the dismissal was expected or caused by an error.
 
 A typical implementation would look like this:
 @code
 - (void)didDismissAd:(CHBDismissEvent *)event {
    // Resume processes paused in willShowAd:
 }
 @endcode
 */
- (void)didDismissAd:(CHBDismissEvent *)event;

@end

/*!
 @protocol CHBInterstitialDelegate
 @brief Interstitial delegate protocol.
 @discussion Provides methods to receive notifications related to an interstitial ad behavior.
 In a typical integration you would implement willShowAd:, didShowAd: and didDismissAd:, pausing and resuming ongoing processes (e.g: gameplay, video) there.
 */
@protocol CHBInterstitialDelegate <CHBDismissableAdDelegate>
@end

/*!
 @protocol CHBRewardedDelegate
 @brief Rewarded delegate protocol.
 @discussion Provides methods to receive notifications related to a rewarded ad behavior.
 In a typical integration you would implement willShowAd:, didShowAd: and didDismissAd:, pausing and resuming ongoing processes (e.g: gameplay, video) there.
 The method didEarnReward: needs to be implemented in order to be notified when the user earns a reward.
 */
@protocol CHBRewardedDelegate <CHBDismissableAdDelegate>

@optional

/*!
 @brief Called when a rewarded ad has completed playing.
 @param event A reward event with info related to the ad and the reward.
 @discussion Implement to be notified when a reward is earned.
 */
- (void)didEarnReward:(CHBRewardEvent *)event;

@end

/*!
 @protocol CHBBannerDelegate
 @brief Banner delegate protocol.
 @discussion Provides methods to receive notifications related to a banner ad behavior.
 */
@protocol CHBBannerDelegate <CHBAdDelegate>

@optional

/*!
 @brief Called when the link viewer presented as result of an ad click has been dismissed.
 @param event A click event with info related to the ad clicked.
 @param error An error specifying the failure reason, or nil if the operation was successful.
 @discussion Implement to be notified of when an ad click has been handled.
 This can mean an in-app web browser or App Store app sheet has been dismissed, or that the user came back to the app after the link was opened on an external application.
 
 A typical implementation would look like this:
 @code
 - (void)didFinishHandlingClick:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    // Resume processes previously paused on didClickAd:error: implementation.
 }
 @endcode
 */
- (void)didFinishHandlingClick:(CHBClickEvent *)event error:(nullable CHBClickError *)error;

@end

NS_ASSUME_NONNULL_END

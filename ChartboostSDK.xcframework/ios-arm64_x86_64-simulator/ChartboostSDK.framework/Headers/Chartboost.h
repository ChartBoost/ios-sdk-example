//
//  Chartboost.h
//  Chartboost
//
//  Copyright 2018 Chartboost. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ChartboostSDK/CHBInterstitial.h>
#import <ChartboostSDK/CHBRewarded.h>
#import <ChartboostSDK/CHBBanner.h>
#import <ChartboostSDK/CHBDataUseConsent.h>

@class CHBStartError;

NS_ASSUME_NONNULL_BEGIN

/*!
Chartboost SDK logging level options
*/
typedef NS_ENUM(NSUInteger, CBLoggingLevel) {
    CBLoggingLevelOff,
    CBLoggingLevelError,
    CBLoggingLevelWarning,
    CBLoggingLevelInfo,
    CBLoggingLevelVerbose
};

/*!
Provides global settings and shared functionality for the Chartboost SDK.
# Discussion #
- Make sure to start Chartboost before requesting any ad.
- Setting data use consent information beforehand is also highly recommended, otherwise Chartboost's ability to provide ads might be hindered.
*/
@interface Chartboost : NSObject

/*!
Starts the SDK with the publisher app credentials.
# Discussion #
It takes an error parameter which indicates if the initialization succeeded or not.
This method must be called before creating an ad. Other methods, like data use consent or logging level methods, are fine to call before start.
- parameter appID: The Chartboost application ID for this app.
- parameter appSignature: The Chartboost application signature for this app.
- parameter completion:  A completion block to be executed when the SDK finishes initializing.
*/
+ (void)startWithAppID:(NSString *)appID appSignature:(NSString *)appSignature completion:(void (^)(CHBStartError * _Nullable error))completion;

/*!
Use to restrict Chartboost's ability to collect personal data from the user.
# Discussion #
- This method can be called multiple times to set the consent for different privacy standards.
- If a consent has already been set for a privacy standard, adding a consent object for that standard will overwrite the previous value.
- This method should be called before starting the Chartboost SDK with startWithAppID:appSignature:completion: if possible.
- The added consents are persisted, so you may just call this when the consent status needs to be updated.
*/
+ (void)addDataUseConsent:(CHBDataUseConsent *)consent NS_SWIFT_NAME(addDataUseConsent(_:));

/*!
Clears the previously added consent for the desired privacy standard.
# Discussion #
- Chartboost persists the added consents, so you'll need to call this method if you want to withdraw a previously added consent.
- If no consent was available for the indicated standard nothing will happen.
- parameter privacyStandard: The privacy standard for which you want to clear the consent.
*/
+ (void)clearDataUseConsentForPrivacyStandard:(CHBPrivacyStandard)privacyStandard NS_SWIFT_NAME(clearDataUseConsent(for:));

/*!
Returns the current consent status for the desired privacy standard.
# Discussion #
Use this to check the current consent status, either set by a call to addDataUseConsent: or persisted from a call to the same method on a previous app run. You may need to cast the returned object to the proper CHBDataUseConsent subclass in order to read its consent value.
- parameter privacyStandard: The privacy standard for which you want to obtain the consent status.
- returns: A CHBDataUseConsent subclass (the same one used to set the consent in addDataUseConsent:) or nil if no consent status is currently available.
 
For example, to check if a consent is not set for GDPR:
 ```objc
 // Obj-C
 if (![Chartboost dataUseConsentForPrivacyStandard:CHBPrivacyStandardGDPR]) { ... }
 // Swift
 if Chartboost.dataUseConsent(for: .GDPR) == nil { ... }
```
To check the specific consent status for GDPR:
 ```objc
 // Obj-C
 CHBGDPRDataUseConsent *gdpr = [Chartboost dataUseConsentForPrivacyStandard:CHBPrivacyStandardGDPR];
 if (gdpr && gdpr.consent == CHBGDPRConsentNonBehavioral) { ... }
 // Swift
 let gdpr = Chartboost.dataUseConsent(for: .GDPR) as? CHBDataUseConsent.GDPR
 if gdpr?.consent == .nonBehavioral { ... }
 ```
*/
+ (nullable __kindof CHBDataUseConsent *)dataUseConsentForPrivacyStandard:(CHBPrivacyStandard)privacyStandard NS_SWIFT_NAME(dataUseConsent(for:));

/*!
The version of the Chartboost SDK.
 */
+ (NSString *)getSDKVersion;

/*!
Sets a logging level.
 - parameter loggingLevel: The minimum level that's going to be logged
# Discussion #
Logging by default is off.
 */
+ (void)setLoggingLevel:(CBLoggingLevel)loggingLevel;

/*!
Returns the token used to authenticate with the Chartboost servers.
 */
+ (nullable NSString *)bidderToken;

@end

NS_ASSUME_NONNULL_END

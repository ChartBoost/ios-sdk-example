//
//  CHBDataUseConsent.h
//  Chartboost
//
//  Copyright 2020 Chartboost. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
Constant that identifies a privacy standard to comply to.
*/
typedef NSString * CHBPrivacyStandard NS_TYPED_EXTENSIBLE_ENUM;
/*! @brief GDPR privacy standard identifier */
FOUNDATION_EXPORT CHBPrivacyStandard const CHBPrivacyStandardGDPR;
/*! @brief CCPA privacy standard identifier */
FOUNDATION_EXPORT CHBPrivacyStandard const CHBPrivacyStandardCCPA;
/*! @brief COPPA privacy standard identifier */
FOUNDATION_EXPORT CHBPrivacyStandard const CHBPrivacyStandardCOPPA;
/*! @brief LGPD privacy standard identifier */
FOUNDATION_EXPORT CHBPrivacyStandard const CHBPrivacyStandardLGPD;

/*!
Abstract class. Subclasses define a data use consent option for a privacy standard.
# Discussion #
Not intended to be used directly, always use a subclass to pass to +[Chartboost addDataUseConsent:] or to cast the result of +[Chartboost dataUseConsentForPrivacyStandard:]
*/
@interface CHBDataUseConsent: NSObject
/*! The identifier for the privacy standard this consent applies to. */
@property (nonatomic, readonly) CHBPrivacyStandard privacyStandard;
/*! Use the subclasses initializers to obtain a valid consent instance. */
- (instancetype)init NS_UNAVAILABLE;

@end

// MARK: - GDPR

/*!
Consent options for GDPR compliance.
*/
typedef NS_ENUM(NSUInteger, CHBGDPRConsent) {
    /*! User does not consent to behavioral targeting in compliance with GDPR. */
    CHBGDPRConsentNonBehavioral,
    /*! User consents to behavioral targeting in compliance with GDPR. */
    CHBGDPRConsentBehavioral
} NS_SWIFT_NAME(CHBGDPRDataUseConsent.Consent);

/*!
CHBDataUseConsent subclass for compliance with GDPR.
*/
NS_SWIFT_NAME(CHBDataUseConsent.GDPR)
@interface CHBGDPRDataUseConsent: CHBDataUseConsent
/*! The GDPR consent option. */
@property (nonatomic, readonly) CHBGDPRConsent consent;
/*!
Returns a GDPR consent object.
- parameter consent: The desired GDPR consent option.
*/
+ (CHBGDPRDataUseConsent *)gdprConsent:(CHBGDPRConsent)consent NS_SWIFT_NAME(init(_:));

@end

// MARK: - CCPA

/*!
Consent options for CCPA compliance.
*/
typedef NS_ENUM(NSUInteger, CHBCCPAConsent) {
    /*! User does not consent to the sale of his or her personal information in compliance with CCPA. */
    CHBCCPAConsentOptOutSale,
    /*! User consents to the sale of his or her personal information in compliance with CCPA. */
    CHBCCPAConsentOptInSale
} NS_SWIFT_NAME(CHBCCPADataUseConsent.Consent);

/*!
CHBDataUseConsent subclass for compliance with CCPA.
*/
NS_SWIFT_NAME(CHBDataUseConsent.CCPA)
@interface CHBCCPADataUseConsent: CHBDataUseConsent
/*!The CCPA consent option. */
@property (nonatomic, readonly) CHBCCPAConsent consent;
/*!
Returns a CCPA consent object.
- parameter consent: The desired CCPA consent option.
*/
+ (CHBCCPADataUseConsent *)ccpaConsent:(CHBCCPAConsent)consent NS_SWIFT_NAME(init(_:));
@end

// MARK: - COPPA

/*!
CHBDataUseConsent subclass for compliance with COPPA.
*/
NS_SWIFT_NAME(CHBDataUseConsent.COPPA)
@interface CHBCOPPADataUseConsent: CHBDataUseConsent
/*!Indicates if the app is directed to children. */
@property (nonatomic, readonly) BOOL isChildDirected;
/*!
Returns a COPPA consent object.
- parameter isChildDirected: Pass `true` if your app is directed to children.
 */
+ (CHBCOPPADataUseConsent *)isChildDirected:(BOOL)isChildDirected NS_SWIFT_NAME(init(isChildDirected:));
@end

// MARK: - LGPD

/*!
CHBDataUseConsent subclass for compliance with LGPD.
*/
NS_SWIFT_NAME(CHBDataUseConsent.LGPD)
@interface CHBLGPDDataUseConsent: CHBDataUseConsent
/*!Indicates if the user consents to behavioral targeting in compliance with LGPD. */
@property (nonatomic, readonly) BOOL allowBehavioralTargeting;
/*!
Returns a LGPD consent object.
- parameter allowBehavioralTargeting: Pass `true` if the user consents to behavioral targeting, `false` otherwise.
*/
+ (CHBLGPDDataUseConsent *)allowBehavioralTargeting:(BOOL)allowBehavioralTargeting NS_SWIFT_NAME(init(allowBehavioralTargeting:));
@end

// MARK: - Custom

/*!
CHBDataUseConsent subclass for compliance with a custom privacy standard.
*/
NS_SWIFT_NAME(CHBDataUseConsent.Custom)
@interface CHBCustomDataUseConsent: CHBDataUseConsent
/*!The custom consent value. */
@property (nonatomic, readonly) NSString *consent;
/*!
Returns a custom consent object.
# Discussion #
- Normally you would use other CHBDataUseConsent subclasses instead, which provide predefined options for current privacy standards.
- If you decide to use this make sure you pass valid values, as defined in [Chartboost Helpsite - Privacy Methods](https://answers.chartboost.com/en-us/child_article/ios-privacy-methods)
- parameter privacyStandard: The desired privacy standard identifier.
- parameter consent: The desired consent value.
*/
+ (CHBCustomDataUseConsent *)customConsentWithPrivacyStandard:(CHBPrivacyStandard)privacyStandard consent:(NSString *)consent NS_SWIFT_NAME(init(privacyStandard:consent:));

@end

NS_ASSUME_NONNULL_END

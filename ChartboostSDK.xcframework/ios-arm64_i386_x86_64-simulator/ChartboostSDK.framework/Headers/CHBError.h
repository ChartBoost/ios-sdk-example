//
//  Chartboost.h
//  Chartboost
//
//  Copyright 2021 Chartboost. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef NS_ENUM (NSUInteger, CHBCacheErrorCode)
 @brief Error codes for failed cache operations.
 */
typedef NS_ENUM(NSInteger, CHBCacheErrorCode) {
    CHBCacheErrorCodeInternal,
    CHBCacheErrorCodeInternetUnavailable,
    CHBCacheErrorCodeNetworkFailure,
    CHBCacheErrorCodeNoAdFound,
    CHBCacheErrorCodeSessionNotStarted,
    CHBCacheErrorCodeAssetDownloadFailure,
    CHBCacheErrorCodePublisherDisabled,
    CHBCacheErrorCodeServerError
};

/*!
 @class CHBCacheError
 @brief An error object passed on cache-related delegate methods.
 */
@interface CHBCacheError : NSError
/*! @brief Error code that indicates the failure reason. */
@property (nonatomic, readonly) CHBCacheErrorCode code;
@end


/*!
 @typedef NS_ENUM (NSUInteger, CHBShowErrorCode)
 @brief Error codes for failed show operations.
 */
typedef NS_ENUM(NSInteger, CHBShowErrorCode) {
    CHBShowErrorCodeInternal,
    CHBShowErrorCodeSessionNotStarted,
    CHBShowErrorCodeInternetUnavailable,
    CHBShowErrorCodePresentationFailure,
    CHBShowErrorCodeNoCachedAd,
    CHBShowErrorCodeNoViewController
};

/*!
 @class CHBShowError
 @brief An error object passed on show-related delegate methods.
 */
@interface CHBShowError : NSError
/*! @brief Error code that indicates the failure reason. */
@property (nonatomic, readonly) CHBShowErrorCode code;
@end

/*!
 @typedef NS_ENUM (NSUInteger, CHBClickErrorCode)
 @brief Error codes for failed click operations.
 */
typedef NS_ENUM(NSInteger, CHBClickErrorCode) {
    CHBClickErrorCodeUriInvalid,
    CHBClickErrorCodeUriUnrecognized,
    CHBClickErrorCodeInternal
};

/*!
 @class CHBClickError
 @brief An error object passed on click-related delegate methods.
 */
@interface CHBClickError : NSError
/*! @brief Error code that indicates the failure reason. */
@property (nonatomic, readonly) CHBClickErrorCode code;
@end

/*!
 @typedef NS_ENUM (NSUInteger, CHBStartErrorCode)
 @brief Error codes for failed start operations.
 */
typedef NS_ENUM(NSInteger, CHBStartErrorCode) {
    CHBStartErrorCodeInvalidCredentials,
    CHBStartErrorCodeNetworkFailure,
    CHBStartErrorCodeServerError
};

/*!
 @class CHBStartError
 @brief An error object passed on SDK start completion callbacks.
 */
@interface CHBStartError : NSError
/*! @brief Error code that indicates the failure reason. */
@property (readonly) CHBStartErrorCode code;
@end

NS_ASSUME_NONNULL_END

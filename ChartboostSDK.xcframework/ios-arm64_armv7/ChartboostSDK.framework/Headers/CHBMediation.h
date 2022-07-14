/*
 * CHBMediation.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class CHBMediation
@brief A class that holds information about the mediation library used to create an ad.
*/
@interface CHBMediation : NSObject
/*! @brief The mediation library name. */
@property (nonatomic, readonly) NSString *name;
/*! @brief The mediation library version. */
@property (nonatomic, readonly) NSString *libraryVersion;
/*! @brief The mediation library adapter version. */
@property (nonatomic, readonly) NSString *adapterVersion;

/*!
@brief The initializer for the mediation object.
@param name The name of the mediation library used. E.g. "Helium"
@param libraryVersion A string representing the library version. E.g. "5.1.0"
@param adapterVersion A string representing the Chartbooost adapter version for this library. E.g. "5.1.0.1"
*/
- (instancetype)initWithName:(NSString *)name libraryVersion:(NSString*)libraryVersion adapterVersion:(NSString*)adapterVersion;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

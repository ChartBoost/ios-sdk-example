/*
 * CHBMediation.h
 * Chartboost
 *
 * Copyright 2019 Chartboost. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
A class that holds information about the mediation library used to create an ad.
*/
@interface CHBMediation : NSObject
/*! The mediation library name. */
@property (nonatomic, readonly) NSString *name;
/*! The mediation library version. */
@property (nonatomic, readonly) NSString *libraryVersion;
/*! The mediation library adapter version. */
@property (nonatomic, readonly) NSString *adapterVersion;

/*!
The initializer for the mediation object.
- parameter name: The name of the mediation library used. E.g. "Helium"
- parameter libraryVersion: A string representing the library version. E.g. "5.1.0"
- parameter adapterVersion: A string representing the Chartbooost adapter version for this library. E.g. "5.1.0.1"
*/
- (instancetype)initWithName:(NSString *)name libraryVersion:(NSString*)libraryVersion adapterVersion:(NSString*)adapterVersion;

/*
# Discussion #
Please use -[CHBMediation initWithName:libraryVersion:adapterVersion:] instead.
*/
- (instancetype)CHBMediation NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

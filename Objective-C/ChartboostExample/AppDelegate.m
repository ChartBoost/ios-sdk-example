/*
 * AppDelegate.m
 * ChartboostExample
 *
 * Copyright (c) 2013 Chartboost. All rights reserved.
 */

#import <ChartboostSDK/Chartboost.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import "AppDelegate.h"
#import "ViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSLog(@"Chartboost SDK Version %@", [Chartboost getSDKVersion]);
    
    [Chartboost addDataUseConsent:[CHBGDPRDataUseConsent gdprConsent:CHBGDPRConsentBehavioral]];
    [Chartboost addDataUseConsent:[CHBCCPADataUseConsent ccpaConsent:CHBCCPAConsentOptInSale]];
    
    [Chartboost setLoggingLevel:CBLoggingLevelInfo];
    
    [Chartboost startWithAppID:@"4f21c409cd1cb2fb7000001b"
                  appSignature:@"92e2de2fd7070327bdeb54c15a5295309c6fcd2d"
                    completion:^(CHBStartError * error) {
        ViewController *vc = (ViewController *)self.window.rootViewController;
        [vc log:error == nil ? @"Chartboost initialized successfully!" : @"Chartboost failed to initialize."];
    }];

    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    if (@available(iOS 14, *)) {
        if ([ATTrackingManager trackingAuthorizationStatus] == ATTrackingManagerAuthorizationStatusNotDetermined) {
            [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
                NSLog(@"Tracking authorization status changed: %lu", (unsigned long)status);
            }];
        } else {
            NSLog(@"Tracking authorization status: %lu", (unsigned long)[ATTrackingManager trackingAuthorizationStatus]);
        }
    }
}

@end

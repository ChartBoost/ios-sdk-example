/*
 * AppDelegate.m
 * ChartboostExample
 *
 * Copyright (c) 2013 Chartboost. All rights reserved.
 */

#import <Chartboost/Chartboost.h>
#import "AppDelegate.h"
#import "ViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSLog(@"Chartboost SDK Version %@", [Chartboost getSDKVersion]);
  
    [Chartboost addDataUseConsent:[CHBGDPRDataUseConsent gdprConsent:CHBGDPRConsentBehavioral]];
    [Chartboost addDataUseConsent:[CHBCCPADataUseConsent ccpaConsent:CHBCCPAConsentOptInSale]];
    
    [Chartboost setLoggingLevel:CBLoggingLevelInfo];
    
    [Chartboost startWithAppId:@"4f21c409cd1cb2fb7000001b"
                  appSignature:@"92e2de2fd7070327bdeb54c15a5295309c6fcd2d"
                    completion:^(BOOL success) {
        ViewController *vc = (ViewController *)self.window.rootViewController;
        [vc log:success ? @"Chartboost initialized successfully!" : @"Chartboost failed to initialize."];
    }];

    return YES;
}

@end

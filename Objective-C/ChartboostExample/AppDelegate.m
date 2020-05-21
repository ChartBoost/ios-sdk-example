/*
 * AppDelegate.m
 * ChartboostExampleApp
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
  
    [Chartboost setPIDataUseConsent:YesBehavioral];
    [Chartboost setLoggingLevel:CBLoggingLevelInfo];
    // Begin a user session. Must not be dependent on user actions or any prior network requests.
    [Chartboost startWithAppId:@"4f21c409cd1cb2fb7000001b" appSignature:@"92e2de2fd7070327bdeb54c15a5295309c6fcd2d" completion:^(BOOL success) {
        [((ViewController *)self.window.rootViewController) log:success ? @"Chartboost initialized successfully!" : @"Chartboost failed to initialize."];
    }];

    return YES;
}

@end

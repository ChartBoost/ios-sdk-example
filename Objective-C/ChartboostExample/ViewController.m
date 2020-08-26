/*
 * ViewController.m
 * ChartboostExample
 *
 * Copyright (c) 2013 Chartboost. All rights reserved.
 */

#import "ViewController.h"
#import <Chartboost/Chartboost.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>

@interface ViewController () <CHBInterstitialDelegate, CHBRewardedDelegate, CHBBannerDelegate>
@property (weak, nonatomic) IBOutlet UITextView *textView;
@property (nonatomic) NSString *logBeforeViewDidLoad;
@property (nonatomic, strong) CHBInterstitial *interstitial;
@property (nonatomic, strong) CHBRewarded *rewarded;
@property (nonatomic, strong) CHBBanner *banner;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.interstitial = [[CHBInterstitial alloc] initWithLocation:CBLocationDefault delegate:self];
    self.rewarded = [[CHBRewarded alloc] initWithLocation:CBLocationDefault delegate:self];
    self.banner = [[CHBBanner alloc] initWithSize:CHBBannerSizeStandard location:CBLocationDefault delegate:self];
    [self log:self.logBeforeViewDidLoad];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self requestPermission];
}

- (IBAction)cacheInterstitial:(id)sender {
    [self.interstitial cache];
}

- (IBAction)showInterstitial:(id)sender {
    // If the interstitial is not cached didShowAd:error: will be called with an error.
    [self.interstitial showFromViewController:self];
}

- (IBAction)cacheRewarded:(id)sender {
    [self.rewarded cache];
}

- (IBAction)showRewarded:(id)sender {
    // We can let showFromViewController: fail for not-cached ads as we do in showInterstitial:, or preemtively check against the isCached property before calling it:
    if (self.rewarded.isCached) {
        [self.rewarded showFromViewController:self];
    } else {
        [self log:@"Tried to show a rewarded ad before it is cached"];
    }
}

- (IBAction)showSupport:(id)sender {
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://answers.chartboost.com"]];
}

- (IBAction)showBanner:(id)sender {
    if (!self.banner.superview) {
        [self layoutBanner];
    }
    [self.banner showFromViewController:self];
}

- (void)layoutBanner {
    [self.view addSubview:self.banner];
    self.banner.translatesAutoresizingMaskIntoConstraints = NO;
    
    NSLayoutAnchor *bottomContainerAnchor = self.view.bottomAnchor;
    if (@available(iOS 11.0, *)) {
        bottomContainerAnchor = self.view.safeAreaLayoutGuide.bottomAnchor;
    }
    [NSLayoutConstraint activateConstraints:@[[self.banner.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
                                              [self.banner.bottomAnchor constraintEqualToAnchor:bottomContainerAnchor]]];
}

- (void)requestPermission {
    if (@available(iOS 14, *)) {
        [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
            dispatch_async(dispatch_get_main_queue(), ^{
                switch (status) {
                    case ATTrackingManagerAuthorizationStatusAuthorized:
                        [self log:@"Authorized"];
                        break;
                    case ATTrackingManagerAuthorizationStatusNotDetermined:
                        [self log:@"Not Determined"];
                        break;
                    case ATTrackingManagerAuthorizationStatusDenied:
                        [self log:@"Denied"];
                        break;
                    case ATTrackingManagerAuthorizationStatusRestricted:
                        [self log:@"Restricted"];
                        break;
                    default:
                        break;
                }
            });
        }];
    }
}


- (void)log:(NSString *)message
{
    NSLog(@"%@", message);
    if (self.textView) {
        self.textView.text = [NSString stringWithFormat:@"%@\n%@", self.textView.text, message];
    } else {
        self.logBeforeViewDidLoad = message;
    }
}

// MARK: - Ad Delegate (Interstitial, Rewarded & Banner)

- (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    [self log:[NSString stringWithFormat:@"didCacheAd: %@ %@", [event.ad class], [self statusWithError:error]]];
}

- (void)willShowAd:(CHBShowEvent *)event {
    [self log:[NSString stringWithFormat:@"willShowAd: %@", [event.ad class]]];
}

- (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error {
    [self log:[NSString stringWithFormat:@"didShowAd: %@ %@", [event.ad class], [self statusWithError:error]]];
}

- (BOOL)shouldConfirmClick:(CHBClickEvent *)event confirmationHandler:(void(^)(BOOL))confirmationHandler {
    [self log:[NSString stringWithFormat:@"shouldConfirmClick: %@", [event.ad class]]];
    return NO;
}

- (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    [self log:[NSString stringWithFormat:@"didClickAd: %@ %@", [event.ad class], [self statusWithError:error]]];
}

- (void)didFinishHandlingClick:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    [self log:[NSString stringWithFormat:@"didFinishHandlingClick: %@ %@", [event.ad class], [self statusWithError:error]]];
}

- (NSString *)statusWithError:(id)error
{
    return error ? [NSString stringWithFormat:@"FAILED (%@)", error] : @"SUCCESS";
}

// MARK: - Ad Delegate (Interstitial & Rewarded)

- (void)didDismissAd:(CHBDismissEvent *)event {
    [self log:[NSString stringWithFormat:@"didDismissAd: %@", [event.ad class]]];
}

// MARK: - Ad Delegate (Rewarded)

- (void)didEarnReward:(CHBRewardEvent *)event {
    [self log:[NSString stringWithFormat:@"didEarnReward: %ld", (long)event.reward]];
}

@end

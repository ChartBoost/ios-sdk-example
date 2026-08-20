# Chartboost SDK iOS Demo App

*Version 9.13.0*

Our demo app showcases how to integrate the [Chartboost SDK](https://developers.chartboost.com/docs/monetization-ios-get-started).

## Versions

The `master` branch includes the example app supporting the latest version of the Chartboost SDK.

For previous SDK versions check out the other branches.

## Integration options

The demo can be built with either dependency manager — the app is identical, only the SDK integration differs:

- **CocoaPods**: run `pod install`, then open `ChartboostSDKDemo.xcworkspace`.
- **Swift Package Manager**: open `ChartboostSDKDemo-SPM.xcodeproj` directly — Xcode resolves the `ChartboostSDK` package on open.

> **Note (SPM):** the Chartboost SDK ships as a static framework containing Objective-C categories, so apps integrating it via SPM must add `-ObjC` to `OTHER_LDFLAGS` (already configured in the demo project). CocoaPods adds this flag automatically.

## Targets

Both projects include the same two targets (and schemes): 

- `ChartboostSDKDemo-Swift`: The Chartboost SDK is integrated in Swift files. 

- `ChartboostSDKDemo-ObjC`: The Chartboost SDK is integrated in Objective-C files.

# Chartboost SDK Example App

Example app to showcase how to integrate the [Chartboost SDK](https://answers.chartboost.com/en-us/child_article/ios). 

## Versions

The `master` branch includes the example app supporting the latest version of the Chartboost SDK.

For previous SDK versions check out the other branches.

## Targets

The ChartboostExample project includes two targets: 

- `ChartboostExample`: Manual dependency management. 

 It requires the `Chartboost.framework` to be dropped into the root directory (where this readme is).
You can download the latest version of the Chartboost SDK [here](http://www.chartboo.st/sdk/ios).

- `ChartboostExample-Pods`: CocoaPods dependency management. 

 Just go into the project directory and run `pod install`.

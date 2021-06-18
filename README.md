# Chartboost SDK iOS Example App

*Version 8.4.2*

Our example app showcases how to integrate the [Chartboost SDK](https://answers.chartboost.com/en-us/child_article/ios).

## Versions

The `master` branch includes the example app supporting the latest version of the Chartboost SDK.

For previous SDK versions check out the other branches.

## Targets

The ChartboostExample project includes two targets: 

- `ChartboostExample`: Manual dependency management. 

It requires the `Chartboost.framework`, which is already in the root directory (where this readme is) and linked to the Xcode project.
You can download the latest version of the Chartboost SDK [here](http://www.chartboo.st/sdk/ios).

- `ChartboostExample-Pods`: CocoaPods dependency management. 

 Just go into the project directory and run `pod install`.

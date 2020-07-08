//
//  AppDelegate.swift
//  ChartboostExample
//
//  Created by Arnau Marti on 08/07/2020.
//  Copyright © 2020 Chartboost. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        print("Chartboost SDK Version ", Chartboost.getSDKVersion() ?? "Error")

        Chartboost.addDataUseConsent(.CCPA(.optInSale))
        Chartboost.addDataUseConsent(.GDPR(.behavioral))

        Chartboost.setLoggingLevel(.info)

        Chartboost.start(withAppId: "4f21c409cd1cb2fb7000001b",
                         appSignature: "92e2de2fd7070327bdeb54c15a5295309c6fcd2d") { (success) in

                        self.window = UIWindow(frame: UIScreen.main.bounds)
                        let storyboard = UIStoryboard(name: "Main", bundle: nil)
                        let vc = storyboard.instantiateViewController(withIdentifier: "viewController")
                        self.window?.rootViewController = vc
                        self.window?.makeKeyAndVisible()
        }
        return true
    }

}


//
//  ViewController.swift
//  ChartboostExample
//
//  Created by Arnau Marti on 08/07/2020.
//  Copyright © 2020 Chartboost. All rights reserved.
//

import UIKit

class ViewController: UIViewController, CHBInterstitialDelegate, CHBRewardedDelegate, CHBBannerDelegate {

    private var interstitial: CHBInterstitial?
    private var rewarded: CHBRewarded?
    private var banner: CHBBanner?

    @IBOutlet weak var textView: UITextView!

    override func viewDidLoad() {
        super.viewDidLoad()
        interstitial = CHBInterstitial(location: CBLocationDefault, delegate: self)
        rewarded = CHBRewarded(location: CBLocationDefault, delegate: self)
        banner = CHBBanner(size: CHBBannerSizeStandard, location: CBLocationDefault, delegate: self)
    }

    private func log(message: String) {
        self.textView.text = self.textView.text + "\n" + message
    }


    @IBAction func cacheInterstitial(_ sender: Any) {
    }

    @IBAction func showInterstitial(_ sender: Any) {
    }

    @IBAction func cacheRewarded(_ sender: Any) {
    }

    @IBAction func showRewarded(_ sender: Any) {
    }

    @IBAction func showBanner(_ sender: Any) {
    }

    @IBAction func showSupport(_ sender: Any) {
        guard let url = URL(string: "http://answers.chartboost.com") else { return }
        if #available(iOS 10.0, *) {
            UIApplication.shared.open(url, options: [:], completionHandler: nil)
        } else {
            UIApplication.shared.openURL(url)
        }
    }
}


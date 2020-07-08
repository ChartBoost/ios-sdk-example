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
        interstitial?.cache()
    }

    @IBAction func showInterstitial(_ sender: Any) {
        interstitial?.show(from: self)
    }

    @IBAction func cacheRewarded(_ sender: Any) {
        rewarded?.cache()
    }

    @IBAction func showRewarded(_ sender: Any) {
        if rewarded?.isCached == true {
            rewarded?.show(from: self)
        } else {
            self.log(message: "Tried to show rewarded ad before it is cached")
        }
    }

    @IBAction func showBanner(_ sender: Any) {
        if banner?.superview == nil {
            layoutBanner()
        }
        banner?.show(from: self)
    }

    private func layoutBanner() {
        guard let banner = banner else { return }
        self.view.addSubview(banner)

        banner.translatesAutoresizingMaskIntoConstraints = false

        if #available(iOS 11.0, *) {
            NSLayoutConstraint.activate([
                banner.bottomAnchor.constraint(equalTo: self.view.safeAreaLayoutGuide.bottomAnchor)
            ])
        } else {
            NSLayoutConstraint.activate([
                banner.bottomAnchor.constraint(equalTo: self.view.bottomAnchor)
            ])
        }
        NSLayoutConstraint.activate([
            banner.centerXAnchor.constraint(equalTo: self.view.centerXAnchor),
        ])
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


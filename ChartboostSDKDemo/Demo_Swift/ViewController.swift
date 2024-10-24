// Copyright 2020-2024 Chartboost, Inc.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

import ChartboostSDK
import UIKit

class ViewController: UIViewController, CHBInterstitialDelegate, CHBRewardedDelegate, CHBBannerDelegate {
    private lazy var interstitial = CHBInterstitial(location: "default", delegate: self)
    private lazy var rewarded = CHBRewarded(location: "default", delegate: self)
    private lazy var banner = CHBBanner(size: CHBBannerSizeStandard, location: "default", delegate: self)
    private var logBeforeViewDidLoad = String()

    @IBOutlet weak var textView: UITextView!

    override func viewDidLoad() {
        super.viewDidLoad()
        log(message: logBeforeViewDidLoad)
    }

    // MARK: - IBActions

    @IBAction func cacheInterstitial(_ sender: Any) {
        interstitial.cache()
    }

    @IBAction func showInterstitial(_ sender: Any) {
        // If the interstitial is not cached didShowAd:error: will be called with an error.
        interstitial.show(from: self)
    }

    @IBAction func cacheRewarded(_ sender: Any) {
        rewarded.cache()
    }

    @IBAction func showRewarded(_ sender: Any) {
        // We can let showFromViewController: fail for not-cached ads as we do in showInterstitial:
        // or preemtively check against the isCached property before calling it:
        if rewarded.isCached {
            rewarded.show(from: self)
        } else {
            self.log(message: "Tried to show rewarded ad before it is cached")
        }
    }

    @IBAction func cacheBanner(_ sender: Any) {
        banner.cache()
    }

    @IBAction func showBanner(_ sender: Any) {
        if banner.superview == nil {
            layoutBanner()
        }
        banner.show(from: self)
    }

    @IBAction func showSupport(_ sender: Any) {
        UIApplication.shared.open(URL(string: "http://answers.chartboost.com")!, options: [:], completionHandler: nil)
    }

    // MARK: - Other

    func log(message: String) {
        print(message)
        if self.textView != nil {
            self.textView.text = self.textView.text + "\n" + message
        } else {
            self.logBeforeViewDidLoad = message
        }
    }

    private func layoutBanner() {
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
            banner.centerXAnchor.constraint(equalTo: self.view.centerXAnchor)
        ])
    }

    private func statusWithError(_ error: Any?) -> String {
        if let error {
            return "FAILED (\(error))"
        }
        return "SUCCESS"
    }

    // MARK: - Ad Delegate (Interstitial, Rewarded & Banner)

    func didCacheAd(_ event: CHBCacheEvent, error: CacheError?) {
        log(message: "didCacheAd: \(type(of: event.ad)) \(statusWithError(error))")
    }

    func willShowAd(_ event: CHBShowEvent) {
        log(message: "willShowAd: \(type(of: event.ad))")
    }

    func didShowAd(_ event: CHBShowEvent, error: ShowError?) {
        log(message: "didShowAd: \(type(of: event.ad)) \(statusWithError(error))")
    }

    func didClickAd(_ event: CHBClickEvent, error: ClickError?) {
        log(message: "didClickAd: \(type(of: event.ad)) \(statusWithError(error))")
    }

    func didFinishHandlingClick(_ event: CHBClickEvent, error: ClickError?) {
        log(message: "didFinishHandlingClick: \(type(of: event.ad)) \(statusWithError(error))")
    }

    // MARK: - Ad Delegate (Interstitial & Rewarded)

    func didDismissAd(_ event: CHBDismissEvent) {
        log(message: "didDismissAd: \(type(of: event.ad))")
    }

    // MARK: - Ad Delegate (Rewarded)

    func didEarnReward(_ event: CHBRewardEvent) {
        log(message: "didEarnReward: " + String(event.reward))
    }
}

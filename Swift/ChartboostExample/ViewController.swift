//
//  ViewController.swift
//  ChartboostExample
//
//  Created by Arnau Marti on 08/07/2020.
//  Copyright © 2020 Chartboost. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
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


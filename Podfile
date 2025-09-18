platform :ios, '12.0'

abstract_target 'Demo' do
  use_frameworks!

  if ENV['MONETIZATION_DEMO_BUILD_TYPE'] == "DEVELOPMENT"
    # Local pod dependencies for internal use
    pod 'ChartboostSDK', :path => '../'
  else
    # Production pod dependencies for general use
    pod 'ChartboostSDK', '~> 9.10.0'
  end

  target 'ChartboostSDKDemo-ObjC'
  target 'ChartboostSDKDemo-Swift'
end

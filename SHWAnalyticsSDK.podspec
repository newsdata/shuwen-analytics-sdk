Pod::Spec.new do |s|
  s.name         = "SHWAnalyticsSDK"
  s.version      = "1.1.3"
  s.summary      = "Analytics framework."
  s.homepage     = "https://github.com/newsdata/shuwen-analytics-sdk"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "yangyang" => "yangyang@shuwen.com" }
  s.platform     = :ios, "8.0"
  s.source       = { :git => "https://github.com/newsdata/shuwen-analytics-sdk.git", :tag => "#{s.version}" }

  s.vendored_framework = "SHWAnalyticsSDK.framework"
  s.dependency 'UTDID', '1.0.0'
  s.dependency 'SAMKeychain', '1.5.2'

  s.requires_arc = true
  s.frameworks = 'CoreLocation','CoreTelephony','Foundation','JavaScriptCore','UIKit','WebKit', 'SystemConfiguration','CoreFoundation','Security'
  s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
end

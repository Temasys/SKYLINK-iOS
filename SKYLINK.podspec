#
# Be sure to run `pod lib lint SKYLINK.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# Any lines starting with a # are optional, but encouraged
#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "SKYLINK"
  s.version          = "2.2.2"
  s.summary          = "SKYLINK.framework distribution"
  s.description      = "SKYLINK.framework distribution for iOS"
  s.homepage         = "https://github.com/Temasys/SKYLINK-iOS"
  s.license          = 'MIT'
  s.author           = { "Temasys Communications" => "xiangrong@temasys.io", "Temasys Communications" => "yuxi.liu@temasys.io", "Temasys Communications" => "hungcuong.hoang@temasys.io", "Temasys Communications" => "chickchick.ce@gmail.com"}
  s.source           = { :git => "https://github.com/Temasys/SKYLINK-iOS.git", :tag => s.version.to_s }

  s.platform     = :ios, '9.0'
  s.requires_arc = true

  s.frameworks = 'AudioToolbox', 'AVFoundation', 'CFNetwork', 'CoreAudio', 'CoreGraphics', 'CoreMedia', 'Foundation', 'GLKit', 'UIKit', 'VideoToolbox'
  s.libraries = 'c', 'icucore', 'sqlite3', 'stdc++'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  s.vendored_frameworks = 'SKYLINK.framework', 'frameworks/WebRTC.framework', 'frameworks/SKYLINK_MESSAGE_CACHE.framework'
  s.preserve_paths = 'frameworks/*'
  s.dependency "Socket.IO-Client-Swift", "~> 15.2.0"

  # I think this is needed because on the new arm Macs. Now you can have arm64 simulators, which we don't support today
  # Additional note: this is not how I would like things to be...
  # https://stackoverflow.com/questions/63607158/xcode-12-building-for-ios-simulator-but-linking-in-object-file-built-for-ios
  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
end

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
  s.version          = "1.1.1"
  s.summary          = "SKYLINK.framework distribution"
  s.description      = "SKYLINK.framework distribution for iOS"
  s.homepage         = "https://github.com/Temasys/SKYLINK-iOS"
  s.license          = 'MIT'
  s.author           = { "Temasys Communications XR" => "xiangrong@temasys.io", "Temasys Communications RP" => "romain.pellen@temasys.io"}
  s.source           = { :git => "https://github.com/Temasys/SKYLINK-iOS.git", :branch => "master" }

  s.platform     = :ios, '8.0'
  s.requires_arc = true

  s.frameworks = 'AudioToolbox', 'AVFoundation', 'CFNetwork', 'CoreAudio', 'CoreGraphics', 'CoreMedia', 'Foundation', 'GLKit', 'UIKit', 'VideoToolbox'
  s.dependency 'SocketRocket', '~> 0.5.1'
  s.dependency 'tema-ios-ntp', '~> 1.0.0'
  s.dependency 'Socket.IO-Client-Swift', '~> 12.1.2'
  s.libraries = 'c', 'icucore', 'sqlite3', 'stdc++'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  s.vendored_frameworks = 'SKYLINK.framework'
  s.preserve_paths = 'SKYLINK.framework'
end

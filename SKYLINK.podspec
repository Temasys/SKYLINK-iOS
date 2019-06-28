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
  s.version          = "1.2.3"
  s.summary          = "SKYLINK.framework distribution"
  s.description      = "SKYLINK.framework distribution for iOS"
  s.homepage         = "https://github.com/Temasys/SKYLINK-iOS"
  s.license          = 'MIT'
  s.author           = { "Temasys Communications" => "xiangrong@temasys.io", "Temasys Communications" => "yuxi.liu@temasys.io"}
  s.source           = { :git => "https://github.com/Temasys/SKYLINK-iOS.git", :tag => s.version.to_s }

  s.platform     = :ios, '9.0'
  s.requires_arc = true

  s.frameworks = 'AudioToolbox', 'AVFoundation', 'CFNetwork', 'CoreAudio', 'CoreGraphics', 'CoreMedia', 'Foundation', 'GLKit', 'UIKit', 'VideoToolbox'
  s.dependency 'Socket.IO-Client-Swift', '~> 12.1.3'
  s.libraries = 'c', 'icucore', 'sqlite3', 'stdc++'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  s.vendored_frameworks = 'SKYLINK.framework'
  s.preserve_paths = 'SKYLINK.framework'
end

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
  s.version          = "0.9.0"
  s.summary          = "SKYLINK.framework distribution"
  s.description      = "SKYLINK.framework distribution"
  s.homepage         = "https://github.com/temahussain/SKYLINK-iOS"
  s.license          = 'MIT'
  s.author           = { "Temasys Communications" => "shussain@temasys.com" }
  s.source           = { :git => "https://github.com/temahussain/SKYLINK-iOS.git", :tag => s.version.to_s }

  s.platform     = :ios, '7.0'
  s.requires_arc = true

  s.frameworks = 'UIKit', 'MapKit', 'AudioToolbox', 'AVFoundation', 'CFNetwork', 'CoreGraphics', 'CoreMedia', 'CoreVideo', 'Foundation', 'GLKit', 'OpenGLES', 'QuartzCore', 'Security', 'SystemConfiguration'
  s.dependency 'SocketRocket', '~> 0.3.1-beta2'
  s.libraries = 'icucore', 'm', 'sqlite3', 'stdc++'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
  s.vendored_frameworks = 'SKYLINK.framework'
  s.vendored_libraries = 'libtemasys.a'
  s.preserve_paths = 'SKYLINK.framework'
end

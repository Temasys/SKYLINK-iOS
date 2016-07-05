# SKYLINK
[![Version](https://img.shields.io/cocoapods/v/MyLibrary.svg?style=flat)](http://cocoadocs.org/docsets/SKYLINK)  [![License](https://img.shields.io/cocoapods/l/MyLibrary.svg?style=flat)](http://cocoadocs.org/docsets/SKYLINK) [![Platform](https://img.shields.io/cocoapods/p/MyLibrary.svg?style=flat)](http://cocoadocs.org/docsets/SKYLINK)

**SkylinkSDK for iOS** lets you build real time webRTC applications with voice calling, video chat, P2P file sharing or data and messages exchange. Go multi-platform with our [Web](http://skylink.io/web/) and [Android](http://skylink.io/android) SDKs.

## Documentation

SkylinkSDK for iOS 1.0.9 documentation is available here: https://cdn.temasys.com.sg/skylink/skylinksdk/ios/1.0.9/docs/index.html

## Requirements
Your project should use ARC and target iOS 7 or higher.

## Installation

SKYLINK is available through [CocoaPods](http://cocoapods.org). 
To install it, simply add the following line to your Podfile:

    pod "SKYLINK"

> To use this SDK, you need to **get you API key** at http://developer.temasys.com.sg/register


### Use SkylinkSDK for iOS in a Swift project

To create a Swift project using SkylinkSDK for iOS, follow these steps:

- Create new Xcode project
- Run  `pod init`
- Your Podfile should look like that: 
```
    use_frameworks!
    target 'MyTarget' do
    pod "SKYLINK"
    end
```
- Run `pod install`
- Create the `Project-Bridging-Header.h` and refer to it in build settings (swift compiler section)
- Add `#import <SKYLINK/SKYLINK.h>` to the newlly created file
You should be able to run your project after this, and use SkylinkSDK for iOS in swift.

### Configuring Settings

- After running 'pod install', use the .xcworkspace file and always work with this from now on (instead of the .xcodeproj file).
- For each target planned to use SkylinkSDK, go to Build settings  (make sure “all” is selected) > Build Options > Enable bit code and set it to NO. This will avoid the “…does not contain bitcode” message
- If you get the error “The resource could not be loaded because the App Transport Security policy requires the use of a secure connection”, edit your info.plist by adding a NSAppTransportSecurity key as Dictionary, and add a sub-key named NSAllowsArbitraryLoads as boolean set to YES.
- Optionally, if you want your app to be able to process audio even when the users leaves the app or locks the device, just enable the VoIP background capability or the audio background capability in the target’s “capabilities” tab.

## Start coding !

SkylinkSDK for iOS is designed to be simple to use. The main idea when using it is to prepare and create a connection to a "room" via the Skylink platform. After that, you will be able to send messages to the connection and implement the desired protocols to control what happens between the local device and the peers connected to the same "room".

To learn more, please consult the follwing ressources:

### Sample App
Be sure to check out our sample app to get usage instructions and examples: http://github.com/Temasys/SkylinkSDK-iOS-Sample

### Tutorials
- Getting started with SkylinkSDK for iOS http://temasys.com.sg/getting-started-skylinksdk-ios/
- Handle the video view stretching: http://temasys.com.sg/a-simple-solution-for-video-stretching/


----------

**Other Resources**
==========================

Support portal
-------
If you encounter any issues or have any enquiries regarding Skylink, drop us a note on our [support portal](http://support.temasys.com.sg/support/login) and we would be happy to help! 

Skylink, by **Temasys**
-------

Check our company websites:
- **Skylink**: http://skylink.io
- By **Temasys**: http://temasys.com.sg
Also checkout our Skylink SDKs for [Web](http://skylink.io/web/) and [Android](http://skylink.io/android)


**License**
==========================

SKYLINK is available under the MIT license. See the LICENSE file for more info.




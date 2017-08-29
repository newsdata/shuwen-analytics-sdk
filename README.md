# 巴吉度 iOS SDK 接入指南(v1.0.16)

This project is a public SDK for who want analyse user behaviors.
Deploy target : iOS 8.0.

## 1 如何接入

### 1.1 在机器上添加Pod仓库
在命令行输入并执行：
```bash
pod repo add frameworkplatform https://code.aliyun.com/xhzy-ios/frameworkplatform.git
```

### 1.2 在项目的 Podfile 中，添加如下依赖：

```ruby
source 'https://github.com/CocoaPods/Specs.git'
source 'https://code.aliyun.com/xhzy-ios/frameworkplatform.git'

target 'YourProject' do
  pod 'SHWAnalytics', '~> 1.0.16'
end
```

> 注: 以上 pod 版本号，请自行更新到最新版本

### 1.3 执行 `pod install`

## 2 Regist your app.
Get your AppKey in our web site.
appKey值可从新华智云接口人获取（网站建设中，目前请联系接口人）

## 3 Config
"Build Settings" -> "Other Linker Flags", add "-Objc".

## 4 How to use

### 4.1 init
**需要在 `main.m` 中进行 SDK 初始化相关配置**

```objective-c
#import "SHWAnalyticsSDK.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {

        SHWAnalyticsPublicConfig *config = [SHWAnalyticsPublicConfig instanceWithAppKey:@"your AppKey"];
        [SHWAnalyticsSDKInterface startWithConfig:config];

        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
```

### 4.2 record
```objective-c
[SHWAnalyticsSDKInterface controllerIn:@"your controller name"];
[SHWAnalyticsSDKInterface controllerOut:@"your controller name"];

//Other interfaces
+ (void)appLaunch;
+ (void)appTerminate;

+ (void)appBecomeActive;
+ (void)appResignActive;

+ (void)controllerIn:(NSString *_Nonnull)pageName;
+ (void)controllerOut:(NSString *_Nonnull)pageName;

+ (void)signIn:(NSString *_Nonnull)signId;
+ (void)signOff:(NSString *_Nonnull)signId;

/**
 * 自定义点击事件埋点

 * @param pageName 点击的所在页面名
 * @param itemClassName 点击的 item 的 ClassName, eg: UIButton, UIView
 * @param itemTagName 点击的 item 名，eg: loginButton
 */
+ (void)clickPageName:(NSString *_Nonnull)pageName
            itemClass:(NSString *_Nonnull)itemClassName
             itemName:(NSString *_Nullable)itemTagName;

/**
 * 自定义事件埋点
 */
+ (void)customEvent:(NSString *_Nonnull)eventID;

+ (void)customEvent:(NSString *_Nonnull)eventID
               args:(NSDictionary *_Nullable)args;

+ (void)customEvent:(NSString *_Nonnull)eventID
              value:(NSInteger)value
               args:(NSDictionary *_Nullable)args;

+ (void)customEvent:(NSString *_Nonnull)eventName
              value:(NSInteger)value
           duration:(long)duration
               args:(NSDictionary *_Nullable)args;

/**
 * @brief                       获取SDK生成的设备唯一标识.
 *
 * @warning                     调用说明:这个设备唯一标识是持久的,并且格式安全,iOS6以及以下,多应用互通.
 *                              调用顺序:utdid任意时刻都可以调用.
 *
 * @return                      24字节的设备唯一标识.
 */
+ (NSString *_Nullable)queryUTDID;
```

### 4.3 JSBridge.(support UIWebView, not support WKWebView yet)
In your UIWebviewController
```objective-c
[SHWUIWebViewJSBridge registWebView:yourWebView withId:@"webViewID"];
[SHWUIWebViewJSBridge deRegistWebViewWithId:@"webViewID"];
```

In your js
```javascript
shw_analytics.record("your message in string format")
```

## 5 Other config
custom your report config.
```objective-c
/**
* 设置是否开启自动统计功能 (默认开启)，包括 app启动、app进入前台、退出前台、controllerIn、controllerOut、以及所有点击事件
* @warning 若关闭此功能，需手动插入埋点代码
*
* @param needAutoTrace 是否开启自动统计功能
*/
- (void)setAutoTraceEnable:(BOOL)needAutoTrace;


```objective-c
/**
*  upload events in disk to server every uploadInterval seconds, default is 30s.
*/
- (void)setUploadInterval:(NSUInteger)uploadInterval;
/**
*  When events' memory reaches this threshold, it will trigger memory queue store to disk.
*/
- (void)setMemoryEventNumberThreshold:(NSUInteger)memoryEventNumberThreshold;
/**
*  When single file size reaches storageSizeThreshold, this file will be frozen. 单位：KB
*/
- (void)setStorageSizeThreshold:(long long)storageSizeThreshold;
```

## 6 其它

- 由于 UTDID.framework 不支持 bitcode ，需要将 Build setting 下 Build Options 中的Enable Bitcode 至为 NO
- 测试发现友盟的 SDK 中 crash 上报功能会覆盖其它 SDK 中的 crash 上报，请在接入巴吉度时，关闭友盟的 crash 上报功能； 或者保证在调用友盟的 config 配置后，再调用巴吉度 `startWithConfig：` 方法；


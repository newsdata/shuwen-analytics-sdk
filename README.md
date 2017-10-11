# 巴吉度 iOS SDK 接入指南(v1.1.3)

Deploy target : iOS 8.0.

## 1 如何接入

### 1.1 在项目的 Podfile 中，添加如下依赖：

```ruby
target 'YourProject' do
  pod 'SHWAnalyticsSDK', '~> 1.1.3'
end
```

### 1.2 执行 `pod install`

### 1.3 Config

"Build Settings" -> "Other Linker Flags", add "-Objc".

## 2 Regist your app.

Get your AppKey in our web site.
appKey值可从新华智云接口人获取（网站建设中，目前请联系接口人）

## 3 How to use

### 3.1 init

**需要在 `main.m` 中进行 SDK 初始化相关配置**

```objective-c
#import "SHWAnalyticsSDK.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {

        SHWAnalyticsPublicConfig *config = [SHWAnalyticsPublicConfig instanceWithAppKey:@"your AppKey"];
//        [config setUploadInterval:15];
//        [config setStorageSizeThreshold:5];
//        [config setMemoryEventNumberThreshold:10];
        [SHWAnalyticsSDKInterface startWithConfig:config];

        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
```

### 3.2 record

```objective-c
#pragma mark - auto track event

// ******************** 以下为自动埋点，可不必手动添加  ************************
+ (void)appLaunch;
+ (void)appTerminate;
+ (void)appBecomeActive;
+ (void)appResignActive;

+ (void)controllerIn:(NSString *_Nonnull)pageName;
+ (void)controllerOut:(NSString *_Nonnull)pageName;
// ******************** 自动埋点，可不必手动添加 ↑ ************************

#pragma mark - custom event

/**
 *  登入、登出 event 埋点
 */
+ (void)signIn:(NSString *_Nonnull)signId;
+ (void)signOff:(NSString *_Nonnull)signId;

/**
 *  click 事件埋点
 *
 *  @param pageName          点击所在页面名
 *  @param itemClassName     点击的 item 的 Class Name
 *  @param itemTagName       点击的 item name
 */
+ (void)clickPageName:(NSString *_Nonnull)pageName
            itemClass:(NSString *_Nonnull)itemClassName
             itemName:(NSString *_Nullable)itemTagName;

/**
 *  自定义事件埋点
 */
+ (void)customEvent:(NSString *_Nonnull)eventName;

+ (void)customEvent:(NSString *_Nonnull)eventName
               args:(NSDictionary *_Nullable)args;

+ (void)customEvent:(NSString *_Nonnull)eventName
              value:(NSInteger)value
               args:(NSDictionary *_Nullable)args;

+ (void)customEvent:(NSString *_Nonnull)eventName
              value:(NSInteger)value
           duration:(long)duration
               args:(NSDictionary *_Nullable)args;

#pragma mark - white list event

// ******************** 添加白名单事件 ↓  ************************
//  NOTE: 白名单事件会立即上传（不区分网络状态)，勿随意设置

+ (void)recordImmediatelyUploadEvent:(NSString *_Nonnull)eventName;

+ (void)recordImmediatelyUploadEvent:(NSString *_Nonnull)eventName
                                args:(NSDictionary *_Nullable)args;

+ (void)recordImmediatelyUploadEvent:(NSString *_Nonnull)eventName
                               value:(NSInteger)value
                                args:(NSDictionary *_Nullable)args;

+ (void)recordImmediatelyUploadEvent:(NSString *_Nonnull)eventName
                               value:(NSInteger)value
                            duration:(long)duration
                                args:(NSDictionary *_Nullable)args;

// ******************** 白名单事件 ↑  ************************

#pragma mark - utils

/**
 *  获取SDK生成的设备唯一标识.
 *
 *  @warning    调用说明:这个设备唯一标识是持久的,并且格式安全,iOS6以及以下,多应用互通.
 *              调用顺序:utdid任意时刻都可以调用.
 *
 *  @return     24字节的设备唯一标识.
 */
+ (NSString *_Nullable)queryUTDID;
```

### 3.3 JSBridge.(support UIWebView, not support WKWebView yet)

In your UIWebviewController

```objective-c
[SHWUIWebViewJSBridge registWebView:yourWebView withId:@"webViewID"];
[SHWUIWebViewJSBridge deRegistWebViewWithId:@"webViewID"];
```

In your js

```javascript
shw_analytics.record("your message in string format")
```

## 4 Other config

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
 *  设置是否开启自动统计功能 (默认开启)
 *
 *  @warning 若关闭此功能，需手动插入埋点代码
 *
 *  @param needAutoTrace 是否开启自动统计
 */
- (void)setAutoTraceEnable:(BOOL)needAutoTrace;

/**
 *  设置日志上报周期 （default：15s）
 *  upload event in disk to server, every uploadInterval
 *
 *  @param uploadInterval 单位为秒,最小 3 秒,最大 86400 秒(24hour).
 */
- (void)setUploadInterval:(NSUInteger)uploadInterval;

/**
 *  设置内存日志写入文件的触发条数 limit （default：每满 15 条写入一次）
 *  When events' memory reaches this threshold, it will trigger memory queue store to disk
 *
 *  @param memoryEventNumberThreshold 单位为条
 */
- (void)setMemoryEventNumberThreshold:(NSUInteger)memoryEventNumberThreshold;

/**
 *  设置单个日志文件的 size limit （default： 3KB）
 *  When single file size reaches storageSizeThreshold, this file will not be frozen
 *
 *  @param storageSizeThreshold 单位为 KB
 */
- (void)setStorageSizeThreshold:(long long)storageSizeThreshold;
```

## 5 其它

- 由于 UTDID.framework 不支持 bitcode ，需要将 Build setting 下 Build Options 中的Enable Bitcode 至为 NO
- 测试发现友盟的 SDK 中 crash 上报功能会覆盖其它 SDK 中的 crash 上报，请在接入巴吉度时，关闭友盟的 crash 上报功能； 或者保证在调用友盟的 config 配置后，再调用巴吉度 `startWithConfig：` 方法；


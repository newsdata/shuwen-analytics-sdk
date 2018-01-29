# 巴吉度 iOS SDK 接入指南(v1.1.4)

Deploy target : iOS 8.0.

## 1 如何接入

### 1.1 在项目的 Podfile 中，添加如下依赖：

```ruby
target 'YourProject' do
  pod 'SHWAnalyticsSDK', '~> 1.1.4'
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
 *  第一个接口：只有参数 事件名。
 *  第二个接口：参数：事件名 + 自定义参数kv对。
 *  第三个接口：用于客户端合并批量事件时，value指事件数量。
 *  第四个接口：duration参数，对于耗时事件（比如登录花了多久）用于计时。
 *  后两个接口如果服务端没有特殊要求，可以通过第二个接口实现。
 *  白名单接口参数含义，参照本接口的设计。
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

### 3.3 UIWebView JSBridge

In your UIWebview's controller

```objective-c
/**
* @brief 注册webView，主线程调用。
* @param webView                   webView，不能为空
*/
+ (void)registWebView:(UIWebView *_Nonnull)webView;

/**
* @brief 注销webView，dealloc 中调用。
* @param webView           webView，不能为空
*/
+ (void)deRegistWebView:(UIWebView *_Nonnull)webView;
```

In your js

```javascript

```

### 3.4 WKWebView JSBridge

In your WKWebview's controller

```objective-c
//- (void)viewDidLoad。必须初始化userContentController。
WKWebViewConfiguration *config = [WKWebViewConfiguration new];
config.preferences = [WKPreferences new];
config.preferences.javaScriptEnabled = YES;
config.userContentController = [WKUserContentController new];   //注意，在调用registWKWebView:userContentController:后，不能再重新new了然后替换config的userContentController。
self.wkWebView = [[WKWebView alloc] initWithFrame:CGRectZero configuration:config];

/**
 * @brief 注册webView。
          注意：必须在viewWillAppear: 中调用。
 * @param webView                   webView，不能为空
 * @param userContentController     userContentController(WKWebViewConfiguration的属性)。
*/
+ (void)registWKWebView:(WKWebView *)webView userContentController:(WKUserContentController *)userContentController;
/**
  * @brief 注销webView。
           注意：必须在viewWillDisappear: 中调用。
 * @param webView           webView，不能为空
*/
+ (void)deRegistWKWebView:(WKWebView *)webView;
```

In your js

```javascript

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

### 5 JS 统计 SDK

在 Web 中，为了能统计数据，需要在页面中嵌入 js 版本的无痕统计 SDK

```html
// ID 目前需要线下申请
<script src="https://p.xinwen.cn/dot/tracing.js" data-id="your-id"></script>
```

如果在特定的地方需要手动触发统计，需要手动调用 `$t(category, action, data)` 全局函数

```
<script>
$t(category, action, data)
</script>
```
| 参数        | 类型    |  是否必填  |    描述     |
| --------   | :-----   | :------- | :---------- |
| category   | String   |   必填    | 代表统计的分类 |
| action     | String   |   必填    | 代表统计的标识 |
| data       | String   |   选填    | 代表统计的额外参数 |


## 6 其它

- 由于 UTDID.framework 不支持 bitcode ，需要将 Build setting 下 Build Options 中的Enable Bitcode 至为 NO
- 测试发现友盟的 SDK 中 crash 上报功能会覆盖其它 SDK 中的 crash 上报，请在接入巴吉度时，关闭友盟的 crash 上报功能； 或者保证在调用友盟的 config 配置后，再调用巴吉度 `startWithConfig：` 方法；


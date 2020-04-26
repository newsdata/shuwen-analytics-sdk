### 巴吉度 Android SDK 接入指南(v1.2.2)

#### 1. 集成方法
##### 1.1 配置Maven仓库
在项目根build.gradle中配置新华智云的Maven仓库：

```
allprojects {
    repositories {
        maven {
            url 'http://maven.wts.xinwen.cn/repository/maven-public/'
            credentials {
                username '*****'
                password '*****'
            }
        }
    }
}
```
##### 1.2 增加依赖
在app模块的build.gradle中添加依赖：

```
compile 'com.shuwen.analytics:analytics-sdk:1.2.2'
```

#### 2. SDK初始化
##### 2.1 配置appkey和channel
在Android manifest里面配置SHWANALYTICS_APPKEY和SHWANALYTICS_CHANNEL，这两个参数目前由服务端提供

```
<meta-data
    android:name="SHWANALYTICS_APPKEY"
    android:value="xxxxx" />
<meta-data
    android:name="SHWANALYTICS_CHANNEL"
    android:value="xxxxxx" />
```

##### 2.2 初始化SDK
在Application.onCreate()中，须尽早执行初始化：

```
// 使用默认配置
SHWAnalytics.init(application);
```

或者，如果要使用自定义配置：

```
SHWAnalyticsConfig config = new SHWAnalyticsConfig.Builder()
    .bufferNumEventsLimit(100)
    .captureCrash(true)
    .detectSessionEvents(true)
    .detectPageEvents(true)
    // 注意logServer如果对外提供，需要配置为如下地址，否则这一项不需要设置，使用默认内容即可
    .logServer("dot.wts.xinwen.cn")
    // more configs ....
    .build();
SHWAnalytics.init(application, config);
```

##### 2.3 添加动态权限
在6.0及以上的Android系统中，由于系统API的限制，需要由App来代理申请如下动态权限：
• android.permission.ACCESS_FINE_LOCATION
• android.permission.READ_PHONE_STATE

#### 3. 使用指南
##### 3.1 记录事件
###### 3.1.1 页面启动退出事件
默认配置下，SDK会自动统计每个页面的启动和退出。但如果在SHWAnalyticsConfig中关闭了session和page事件的自动侦测，则需要自行调用：

```
SHWAnalytics.recordSessionStart(); // App从后台切前台，(该接口立即上传日志信息到服务器)
SHWAnalytics.recordSessionStop(); // App从前台切后台，(该接口立即上传日志信息到服务器)
SHWAnalytics.recordPageStart(name); // App的一个页面开始展现
SHWAnalytics.recordPageStop(name); // App的一个页面退出
```

###### 3.1.2 登录事件
如果App有用户登陆体系，则可以借助巴吉度的分析能力对用户行为进行追踪(该接口立即上传日志信息到服务器)：

```
recordProfileSignedIn(provider, uid); // 用户登陆后调用，provider为登陆服务提供商名称，可为null
recordProfileSignedOff(provider, uid); // 用户登出后调用
```

###### 3.1.3 自定义事件
可自定义事件一：（不会立即上传到服务器，会优先缓存到本地文件中）

```
recordEvent(key);
recordEvent(key, properties);
recordEvent(key, properties, value);
recordEvent(key, properties, value, duration);
```

可自定义事件二：（白名单事件接口，根据参数（isImmediateReport）控制是否要立即上传到服务器）

```
recordEvent(key，isImmediateReport);
recordEvent(key, properties，isImmediateReport);
recordEvent(key, properties, value，isImmediateReport);
recordEvent(key, properties, value, duration，isImmediateReport);
```

##### 3.2 SHWAnalyticsConfig配置

```
SHWAnalyticsConfig config = new SHWAnalyticsConfig.Builder()
    /* App在前台时上报的频率（毫秒）*/
    .uploadIntervalForeground(15_000L)
    /* App在后台时上报的频率（毫秒）*/
    .uploadIntervalBackground(60_000L * 15)
    /* 内存缓存事件的条数，若超过则存入本地存储 */    
    .memoryEventNumThreshold(15)
    /* 内存缓存的容量（bytes），若超过则存入本地存储 */
    .memorySizeThreshold(3_000L)
    /* 单个本地存储的上限（bytes），超过上限则进入上报队列 */
    .storageSizeThreshold(100_000L)
    /* 是否打印log，默认false */
    .printLog(false)
    /* 是否自动侦测会话启动和停止，默认true */
    .detectSessionEvents(true)
    /* 是否自动侦测页面启动和停止，默认true */
    .detectPageEvents(true)
    .build();
SHWAnalytics.init(application, config);
```

##### 3.3 JS 统计 SDK
在 Web 中，为了能统计数据，需要在页面中嵌入 js 版本的无痕统计 SDK

```
// ID 目前需要线下申请
<script src="https://p.xinwen.cn/dot/tracing.js" data-id="your-id"></script>
```

如果在特定的地方需要手动触发统计，需要手动调用 $t(category, action, data) 全局函数

```
<script>
$t(category, action, data)
</script>
```


| 参数 | 类型 | 是否必填 |描述  |
| --- | --- | --- | --- |
| category |String  |必填  |代表统计分类  |
| action |String  |必填  |代表统计标识  |
|data  |String  | 选填 |代表统计额外参数  |


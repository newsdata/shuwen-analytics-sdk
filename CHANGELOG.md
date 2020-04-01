# Change Log

## iOS Changes

### 1.4.0

- 移除 `SHWUIWebViewJSBridge`
- 接入方如有使用 H5 埋点，请替换为 `SHWWKWebViewJSBridge`


### 1.3.0

- 移除/替换 SDK 内部使用 UIWebView 的地方
- `SHWUIWebViewJSBridge` 标记为废弃 （苹果的最新政策，已经不支持使用 UIWebView 的新 App 上架）
- 对外提供的 `SHWUIWebViewJSBridge` 类暂时保留，接入方如有使用 H5 埋点，请尽快替换为 `SHWWKWebViewJSBridge`，下个版本将会移除 `SHWUIWebViewJSBridge`!

### 1.2.3

- Bug fix，SDK 稳定性优化


## Android Changes


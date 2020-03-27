//
//  SHWJSBridgeContainer.h
//  TestJSBridge
//
//  Created by Yang Yang on 2017/5/31.
//  Copyright © 2017年 Yang Yang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface SHWUIWebViewJSBridge : NSObject

/**
 * @brief 注册webView，主线程调用。
 * @param webView                   webView，不能为空
 */
+ (void)registWebView:(UIWebView *_Nonnull)webView NS_DEPRECATED(2_0, 2_0, 2_0, 2_0, "请替换为SHWWKWebViewJSBridge");

/**
 * @brief 注销webView，dealloc 中调用。
 * @param webView           webView，不能为空
 */
+ (void)deRegistWebView:(UIWebView *_Nonnull)webView NS_DEPRECATED(2_0, 2_0, 2_0, 2_0, "请替换为SHWWKWebViewJSBridge");
@end

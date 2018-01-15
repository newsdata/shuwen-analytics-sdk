//
//  SHWWKWebViewJSBridge.h
//  TestJSBridge
//
//  Created by Yang Yang on 2018/1/15.
//  Copyright © 2018年 Yang Yang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

@interface SHWWKWebViewJSBridge : NSObject
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
@end

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
 *  invoke this method in main thread.
 */
+ (void)registWebView:(UIWebView *_Nonnull)webView withId:(NSString *_Nonnull)webViewId;

/**
 *  remember invoke this method in dealloc
 */
+ (void)deRegistWebViewWithId:(NSString *_Nonnull)webViewId;

@end

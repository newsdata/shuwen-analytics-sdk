//
//  SHWAnalyticsSDKLauncher.h
//  SHWAnalyticsSDK
//
//  Created by Yang Yang on 2017/5/23.
//  Copyright © 2017年 Xin Hua Zhi Yun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHWAnalyticsPublicConfig.h"

@interface SHWAnalyticsSDKInterface : NSObject
+ (void)startWithConfig:(SHWAnalyticsPublicConfig *_Nonnull)config;

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

/**
 * @brief                       获取SDK生成的设备唯一标识.
 *
 * @warning                     调用说明:这个设备唯一标识是持久的,并且格式安全,iOS6以及以下,多应用互通.
 *                              调用顺序:utdid任意时刻都可以调用.
 *
 * @return                      24字节的设备唯一标识.
 */
+ (NSString *_Nullable)queryUTDID;

@end

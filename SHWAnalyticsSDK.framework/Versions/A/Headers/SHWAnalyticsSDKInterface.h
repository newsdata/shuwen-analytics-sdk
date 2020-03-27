//
//  SHWAnalyticsSDKLauncher.h
//  SHWAnalyticsSDK
//
//  Created by Yang Yang on 2017/5/23.
//  Copyright © 2017年 Xin Hua Zhi Yun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHWAnalyticsPublicConfig.h"

#define SHW_ANALYTICES_SESSION_CREATED_NOTIFICATION @"AnalyticsSessionCreatedNotification"

@interface SHWAnalyticsSDKInterface : NSObject

/** 
 *  初始化埋点统计 SDK
 */
+ (void)startWithConfig:(SHWAnalyticsPublicConfig *_Nonnull)config;

#pragma mark - auto track event

// ******************** 以下为自动埋点，可不必手动添加  ************************
+ (void)appLaunch;
+ (void)appTerminate;
+ (void)appBecomeActive;
+ (void)appResignActive;

+ (void)controllerIn:(NSString *_Nonnull)pageName;
+ (void)controllerIn:(NSString *_Nonnull)pageName prePage:(NSString *)referer;

+ (void)controllerOut:(NSString *_Nonnull)pageName;
+ (void)controllerOut:(NSString *_Nonnull)pageName duration:(int)duration;
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

// ******************** 白名单事件埋点 ↓  ************************

/** 
 *  上报白名单事件
 *
 *  @warning  白名单 event 会立即上传（不区分网络状态)
 */
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

/**
 *  打印 SDK 内部日志，仅用于排查接入错误（默认关闭）
 */
+ (void)setLogEnable:(BOOL)enable;

@end

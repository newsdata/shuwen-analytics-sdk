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

+ (void)clickPageName:(NSString *_Nonnull)pageName itemClass:(NSString *_Nonnull)itemClassName itemName:(NSString *_Nullable)itemTagName;

+ (void)customEvent:(NSString *_Nonnull)eventName value:(NSInteger)value duration:(long)duration args:(NSDictionary *_Nullable)args;

+ (NSString *_Nullable)utdid;

@end

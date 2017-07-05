//
//  SHWAnalyticsPublicConfig.h
//  SHWAnalyticsSDK
//
//  Created by Yang Yang on 2017/6/6.
//  Copyright © 2017年 Xin Hua Zhi Yun. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SHWAnalyticsPublicConfig : NSObject

/**
 convenience init method

 @param appKey 新华智云平台注册的统一 appkey
 @param utdid  设备 UDID
 */
+ (SHWAnalyticsPublicConfig *_Nonnull)instanceWithAppKey:(NSString *_Nonnull)appKey
                                              deviceUDID:(NSString *_Nonnull)utdid;

/**
 设置是否开启自动统计功能 (默认开启)
 @warning 若关闭此功能，需手动插入埋点代码
 
 @param needAutoTrace 是否开启自动统计功能
 */
- (void)setAutoTraceEnable:(BOOL)needAutoTrace;

/**
 *  upload event in disk to server, every uploadInterval, default is 300s.
 */
- (void)setUploadInterval:(NSUInteger)uploadInterval;
/**
 *  When events' memory reaches this threshold, it will trigger memory queue store to disk.
 */
- (void)setMemoryEventNumberThreshold:(NSUInteger)memoryEventNumberThreshold;
/**
 *  When single file size reaches storageSizeThreshold, this file will not be frozen. 单位：KB
 */
- (void)setStorageSizeThreshold:(long long)storageSizeThreshold;

@end

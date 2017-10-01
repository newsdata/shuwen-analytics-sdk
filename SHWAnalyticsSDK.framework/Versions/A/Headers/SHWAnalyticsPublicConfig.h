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
 *  convenience init method
 *
 *  @param appKey 新华智云平台注册的统一 appkey
 */
+ (SHWAnalyticsPublicConfig *_Nonnull)instanceWithAppKey:(NSString *_Nonnull)appKey;

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

@end

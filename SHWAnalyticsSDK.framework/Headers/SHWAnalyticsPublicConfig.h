//
//  SHWAnalyticsPublicConfig.h
//  SHWAnalyticsSDK
//
//  Created by Yang Yang on 2017/6/6.
//  Copyright © 2017年 Xin Hua Zhi Yun. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SHWAnalyticsPublicConfig : NSObject

+ (SHWAnalyticsPublicConfig *_Nonnull)instanceWithAppKey:(NSString *_Nonnull)appKey;

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

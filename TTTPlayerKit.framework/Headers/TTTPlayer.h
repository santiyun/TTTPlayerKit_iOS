#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TTTPlayerOptions.h"



/**
 TTTPlayer 的播放状态
 */
typedef NS_ENUM(NSInteger, TTTPlayerStatus) {
    /**
     未知状态，只会作为 init 后的初始状态，开始播放之后任何情况下都不会再回到此状态。
     */
    TTTPlayerStatusUnknow = 0,
    
    /**
     正在准备播放所需组件，在调用 play 方法时出现。
     */
    TTTPlayerStatusPreparing,
    
    /**
     播放组件准备完成，准备开始播放，在调用 play 方法时出现。
     */
    TTTPlayerStatusReady,
    
    /**
     TTTPlayer 缓存数据为空状态
     */
    TTTPlayerStatusCaching,
    
    /**
     正在播放状态
     */
    TTTPlayerStatusPlaying,
    
    /**
     暂停状态
     */
    TTTPlayerStatusPaused,
    
    /**
     停止状态
     该状态仅会在回放时播放结束出现，RTMP 直播结束并不会出现此状态
     */
    TTTPlayerStatusStopped,
    
    /**
     错误状态，播放出现错误时会出现此状态。
     */
    TTTPlayerStatusError
};


/**
 TTTPlayer 的统计信息类
 */
@interface TTTPlayerStatsInfo : NSObject
@property (nonatomic, assign) int frameRate;  // 帧率(fps)
@property (nonatomic, assign) int videoBitrate; // 视频的码率(kbps)
@property (nonatomic, assign) int audioBitrate; // 音频的码率(kbps)
@property (nonatomic, assign) int width;        // 视频宽
@property (nonatomic, assign) int height;       // 视频高
@property (nonatomic, assign) int audioDelay;   // 音频延迟(ms)
@property (nonatomic, assign) int videoDelay;   // 视频延迟(ms)
@end

@protocol TTTPlayerDelegate;

/**
 TTTPlayer 是 TTTPlayerKit 中负责播放控制的核心类
 */
@interface TTTPlayer : NSObject

/**
 代理对象，用于告知播放器状态改变或其他行为，对象需实现 TTTPlayerDelegate 协议
 */
@property (nonatomic, weak) id<TTTPlayerDelegate> delegate;

/**
 TTTPlayer 的 options 对象
 */
@property (nonatomic, strong, readonly) TTTPlayerOptions *options;

/**
 TTTPlayer 的画面输出到该 UIView 对象
 */
@property (nonatomic, strong, readonly) UIView *playerView;

/**
 TTTPlayer 的播放状态
 */
@property (nonatomic, assign, readonly) TTTPlayerStatus status;

/**
 指示当前 TTTPlayer 是否处于正在播放状态
 */
@property (nonatomic, assign, readonly, getter=isPlaying) BOOL playing;

/**
 TTTPlayer 的当前播放时间
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/**
 TTTPlayer 的总播放时间
 */
@property (nonatomic, assign, readonly) NSTimeInterval totalDuration;

/** 旋转视频只支持0、90、180、270*/
@property (nonatomic) int rotateDegress;


/**
 使用 URL 和 options 生成一个 TTTPlayer 对象
 
 @param URL     需要播放的 URL
 @param options 播放器初始化选项，传入 nil 值将按照默认选项进行初始化
 
 @return 生成的 TTTPlayer 对象
 */
+ (instancetype)playerWithURL:(NSURL *)URL options:(TTTPlayerOptions *)options;

/**
 使用 url 和 option 初始化一个 TTTPlayer 对象
 
 @param URL     需要播放的 URL
 @param options 播放器初始化选项，传入 nil 值将按照默认选项进行初始化
 
 @return 初始化后的 TTTPlayer 对象
 */
- (instancetype)initWithURL:(NSURL *)URL options:(TTTPlayerOptions *)options;

/**
 开始播放
 */
- (void)play;

/**
 当播放器处于暂停状态时调用该方法可以使播放器继续播放
 */
- (void)resume;

/**
 当播放器处于 playing 或 caching 状态时调用该方法可以暂停播放器
 */
- (void)pause;

/**
 停止播放
 */
- (void)stop;

/**
 快速定位到指定播放时间点，该方法仅在回放时起作用，直播场景下该方法直接返回
 */
- (void)seekTo:(NSTimeInterval)time;

/**
 调节播放音量
 @param volume  0-100
 */
- (void)setPlaybackVolume:(int)volume;


- (UIImage *)thumbnailImageAtCurrentTime;

#pragma mark - KTV
/**
 KTV场景再play之前调用该接口
 */
- (void)prepareForKTV;

/**
 调节KTV播放音量
 @param volume  0-100
 */
-  (void)adjustKTVVolume:(int)volume;

/**
 * 拉取KTV音频数据
 *
 * @param data        数据地址
 * @param size        数据长度
 * @param sampleRate  采样率
 * @param channels    声道数
 */
- (void)pullKTVAudioData:(char *)data size:(int)size sampleRate:(int)sampleRate channels:(int)channels;

+ (NSString *)getVersion;
@end


/**
 TTTPlayer 的代理协议
 */
@protocol TTTPlayerDelegate <NSObject>
@optional;

/**
 告知代理对象播放器状态变更
 
 @param player       调用该方法的 TTTPlayer 对象
 @param playerStatus 变更之后的 TTTPlayer 状态
 */
- (void)player:(TTTPlayer *)player statusDidChange:(TTTPlayerStatus)playerStatus;

/**
 告知代理对象播放器因错误停止播放
 
 @param player 调用该方法的 TTTPlayer 对象
 @param error  携带播放器停止播放错误信息的 NSError 对象
 */
- (void)player:(TTTPlayer *)player stoppedWithError:(NSError *)error;

/**
 告知代理对象播放器统计信息（每2秒触发一次）
 
 @param player    调用该方法的 TTTPlayer 对象
 @param statsInfo 统计信息
 */
- (void)player:(TTTPlayer *)player statsInfo:(TTTPlayerStatsInfo *)statsInfo;

/**
 告知代理对象播放器H264SEI
 
 @param player  调用该方法的 TTTPlayer 对象
 @param sei     H264SEI
 */
- (void)player:(TTTPlayer *)player playbackH264SEI:(NSString *)sei;

/**
 告知代理对象播放器H264SEI中的音量信息
 
 @param player  调用该方法的 TTTPlayer 对象
 @param volInfo 音量信息
 */
- (void)player:(TTTPlayer *)player playbackVolInfo:(NSArray<NSDictionary *> *)volInfo;

/**
 * 视频第一帧解码成功
 */
- (void)playerVideoDecoderOpen:(TTTPlayer *)player;

- (void)playerVideoFrameRenderedStart:(TTTPlayer *)player;

- (void)playerRenderOverlay:(TTTPlayer *)player;

#pragma mark - KTV
/**
 回调KTV视频数据信息
 
 @param player  调用该方法的 TTTPlayer 对象
 @param data   420P数据
 @param width  视频宽
 @param height 视频高
 */
- (void)player:(TTTPlayer *)player videoData:(NSData *)data width:(int)width height:(int)height;

/**
 回调KTV音频数据信息
 
 @param player  调用该方法的 TTTPlayer 对象
 @param data    音频数据
 */
- (void)player:(TTTPlayer *)player audioData:(NSData *)data;

@end

#include "Animation.h"

void Animation::bindFrames(Texture tFrames[], int length) {		//传入纹理数组，数组长度
	frames = new Texture[length];								//让内置的纹理数组等于
	for (int i = 0; i < length; i++) {							//给动态定义长度
		frames[i] = tFrames[i];
	}
	frameLength = length;
}
void Animation::play() {
	setTexture(frames[frameNo]);			//设定当前帧的纹理
	frameNo += 1;							//下一帧
	if (frameNo == frameLength) {			//重新开始播放
		frameNo = 0;
	}
}
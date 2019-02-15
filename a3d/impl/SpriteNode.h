//  Created by ideawu on 08/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimationNode_hpp
#define AnimationNode_hpp

#include "Node.h"
#include "Clock.h"
#include "Sprite.h"

namespace a3d{
	class SpriteNode : public Node
	{
	public:
		SpriteNode();
		virtual ~SpriteNode();
		
		virtual void draw();
		virtual void updateAtTime(double time);

		void play();
		void pause();
		void stop();

		Sprite* sprite() const;
		// 内存由 SpriteNode 管理
		void sprite(Sprite *sprite);

		bool isPlaying() const;
		bool isPaused() const;
		bool isStopped() const;
		
		// 是否不可丢帧
		void isFrameLossless(bool isLossless);
		// 是否循环播放
		void isLooping(bool looping);
		
	private:
		SpriteNode(const SpriteNode &d);
		SpriteNode& operator =(const SpriteNode &d);
		
		bool _isFrameLossless;
		bool _isLooping;
		Clock _clock;
		Sprite *_sprite;
		
		double spriteTime() const;
	};
}; // end namespace

#endif /* AnimationNode_hpp */

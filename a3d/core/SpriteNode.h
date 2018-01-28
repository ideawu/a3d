//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef __a3d__SpriteNode__
#define __a3d__SpriteNode__

#include "Node.h"
#include "Sprite.h"
#include "Clock.h"

namespace a3d{
	class SpriteNode : public Node
	{
	public:
		SpriteNode();
		virtual ~SpriteNode();

		virtual void drawAtTime(float time);

		Node* contentNode() const;
		Sprite* sprite() const;
		void sprite(Sprite *sprite);

		// 是否是不可丢帧的
		void isFrameLossless(bool isLossless);
		// 是否循环播放
		void isLooping(bool looping);

		bool isPlaying() const;
		bool isPaused() const;
		bool isStopped() const;

		void play();
		void pause();
		void stop();

	private:
		SpriteNode(const SpriteNode &d);
		SpriteNode& operator =(const SpriteNode &d);

		Node *_contentNode;
		Sprite *_sprite;

		int _state;
		Clock _clock;
		bool _isFrameLossless;
		bool _isLooping;
	};
}; // end namespace

#endif /* defined(__a3d__SpriteNode__) */

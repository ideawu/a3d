//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef __a3d__SpriteNode__
#define __a3d__SpriteNode__

#include "Node.h"
#include "Clock.h"

namespace a3d{
	class Sprite;

	class SpriteNode : public Node
	{
	public:
		SpriteNode();

		virtual void drawAtTime(float time);

		Node* contentNode() const;
		Sprite* sprite() const;
		void sprite(Sprite *sprite);

		void play();
		void pause();
		void stop();

		// 是否是不可丢帧的
		void isFrameLossless(bool isLossless);
		// 是否循环播放
		void isLooping(bool looping);;

	private:
		SpriteNode(const SpriteNode &d);
		SpriteNode& operator =(const SpriteNode& d);

		Node *_contentNode;
		Sprite *_sprite;

		Clock _clock;
		bool _isFrameLossless;
		bool _isLooping;
	};
}; // end namespace

#endif /* defined(__a3d__SpriteNode__) */

//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef a3d_SpriteNode_h
#define a3d_SpriteNode_h

#include "Node.h"
#include "Sprite.h"
#include "Clock.h"

namespace a3d{
	class TextureNode;
	
	class SpriteNode : public Node
	{
	public:
		SpriteNode();
		virtual ~SpriteNode();
		virtual void drawAtTime(double time);

		Node* contentNode() const;
		Sprite* sprite() const;
		// 内存由 SpriteNode 管理
		void sprite(Sprite *sprite);

		Vector3 originSize() const;
		float originWidth() const;
		float originHeight() const;

		bool isPlaying() const;
		bool isPaused() const;
		bool isStopped() const;

		void play();
		void pause();
		void stop();

		// 是否是不可丢帧的
		void isFrameLossless(bool isLossless);
		// 是否循环播放
		void isLooping(bool looping);

	private:
		SpriteNode(const SpriteNode &d);
		SpriteNode& operator =(const SpriteNode &d);

		Vector3 _originSize;
		TextureNode *_contentNode;
		Sprite *_sprite;

		int _state;
		Clock _clock;
		bool _isFrameLossless;
		bool _isLooping;
		
		void updateClock(double time);
	};
}; // end namespace

#endif /* defined(__a3d__SpriteNode__) */

//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <vector>
#include "Color.h"

namespace a3d{
	class Renderer
	{
	public:
		// 当前 Context 上的 render
		static Renderer* current();
		
		Renderer();

		float opacity() const;
		// 基于当前的透明度叠加新的透明度
		void pushOpacity(float opacity);
		void popOpacity();

	private:
		Renderer(const Renderer &d);
		Renderer& operator =(const Renderer& d);

		Color _color;
		std::vector<float> _q_opacity;
	};
}; // end namespace

#endif /* Renderer_hpp */

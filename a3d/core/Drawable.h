//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include "Object.h"
#include <OpenGL/gl.h>

namespace a3d{
	class Drawable : public Object
	{
	public:
		// 子类实现此方法，但子类的使用者不直接调用此方法，而是调用 render()。
		virtual void draw() = 0;
		// 依次调用: pushMatrix(), draw(), popMatrix()
		void render();
		
	protected:
		Drawable(){}
		
		void pushMatrix();
		void popMatrix();
		
	private:
		Drawable(const Drawable &d){}
	};
	
}; // end namespace

#endif /* Drawable_hpp */

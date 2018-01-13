//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Matrix4.h"

namespace a3d{
	class Object : Matrix4
	{
	private:
		float _width, _height, _depth;
		
	public:
		Object();

	public:
		float width() const;
		float height() const;
		float depth() const;
		void width(float w);
		void height(float h);
		void depth(float d);

	public:
		void move(float x, float y, float z);
		void move(Vector3 offset);
		
		
		// 将力施加与坐标系的某一位置，当作用于标准球表面时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
		void force(Vector3 force, Vector3 atPoint);
		void force(Vector3 force, Vector3 atPoint, float rotationScalar);
};
	
}; // end namespace

#endif /* Object_hpp */

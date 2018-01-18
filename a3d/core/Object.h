//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Matrix4.h"
#include "Transform.h"

namespace a3d{
	// 不继承，而是使用 Matrix？
	class Object : public Matrix4
	{
	public:
		Object();
		Object(float w, float h, float d);

	public:
		Vector3 size() const;
		void size(Vector3 size);
		
		float width() const;
		void width(float w);
		float height() const;
		void height(float h);
		float depth() const;
		void depth(float d);

	public:
		void move(float x, float y, float z);
		void move(Vector3 offset);
		
		void transform(Vector3 size);
		void transform(Matrix4 mat);
		void transform(Transform trans);

		// 将力施加与坐标系的某一位置，当作用于标准球表面时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
		void force(Vector3 force, Vector3 atPoint);
		void force(Vector3 force, Vector3 atPoint, float rotationScalar);

	private:
		Vector3 _size;

		Object(const Object &obj);
	};
	
}; // end namespace

#endif /* Object_hpp */

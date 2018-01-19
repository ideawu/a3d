//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Matrix4.h"
#include "Transform.h"

namespace a3d{
	class Object
	{
	public:
		Object();
		Object(float w, float h, float d);

	public:
		Matrix4 matrix() const;
		
		Vector3 pos() const;
		void pos(const Vector3 &pos);
		void pos(float x, float y, float z);
		float x() const;
		void x(float x);
		float y() const;
		void y(float y);
		float z() const;
		void z(float z);

		Vector3 size() const;
		void size(const Vector3 &size);
		
		float width() const;
		void width(float w);
		float height() const;
		void height(float h);
		float depth() const;
		void depth(float d);

	public:
		void move(float x, float y, float z);
		void move(const Vector3 &offset);
		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);
		void rotate(float degree, const Vector3 &vec);
		// 绕自身坐标系内的任意轴旋转
		void rotate(float degree, const Axis &axis);
		// 同时缩放自身体积和坐标系
		void scale(float xyz);
		void scale(float x, float y, float z);
		
		void transform(const Vector3 &size);
		void transform(const Matrix4 &mat);
		void transform(const Transform &trans);

		// 将力施加与坐标系的某一位置，当作用于标准球表面时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
//		void force(const Vector3 &force, const Vector3 &atPoint);
//		void force(const Vector3 &force, const Vector3 &atPoint, float rotationScalar);

	private:
		Vector3 _size;
		Matrix4 _matrix;
	};
	
}; // end namespace

#endif /* Object_hpp */

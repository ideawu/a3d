//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Object_hpp
#define a3d_Object_hpp

#include "Matrix4.h"
#include "Transform.h"
#include "Vector3.h"
#include "Point3.h"
#include "Axis.h"

namespace a3d{
	class Object
	{
	public:
		Object();
		Object(float w, float h, float d);
		virtual ~Object(){}

	public:
		Matrix4 matrix() const;
		void matrix(const Matrix4 &mat);
		
		Vector3 position() const;
		void position(const Vector3 &pos);
		void position(float x, float y, float z);
		float x() const;
		void x(float x);
		float y() const;
		void y(float y);
		float z() const;
		void z(float z);

		Vector3 scale() const;
		void scaleTo(const Vector3 &scale);

		Quaternion quaternion() const;
		void quaternion(const Quaternion &quat);

		Vector3 size() const;
		void size(const Vector3 &size);
		void size(float w, float h, float d);

		float width() const;
		void width(float w);
		float height() const;
		void height(float h);
		float depth() const;
		void depth(float d);

		float opacity() const;
		void opacity(float opacity);
		void show();
		void hide();
		bool hidden() const;

	public:
		void moveX(float dx);
		void moveY(float dy);
		void moveZ(float dz);
		void move(float dx, float dy, float dz);
		void move(const Vector3 &offset);
		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);
		void rotate(float degree, const Vector3 &vec);
		// 绕自身坐标系内的任意轴旋转
		void rotate(float degree, const Axis &axis);
		// 仅缩放坐标系，不缩放自身体积
		void scale(float xyz);
		void scale(const Vector3 &scale);
		void scale(float x, float y, float z);

		void transform(float opacity);
		void transform(const Vector3 &size);
		// 在父坐标系内做mat变换，而不是在自己的坐标系内做mat变换
		void transform(const Matrix4 &mat);
		void transform(const Transform &trans);

		// ### 与父坐标系之间的坐标转换
		Vector3 convertVectorToParent(const Vector3 &vec) const;
		Vector3 convertVectorFromParent(const Vector3 &vec) const;
		Point3 convertPointToParent(const Point3 &pos) const;
		Point3 convertPointFromParent(const Point3 &pos) const;
		Axis convertAxisToParent(const Axis &axis) const;
		Axis convertAxisFromParent(const Axis &axis) const;
		Matrix4 convertMatrixToParent(const Matrix4 &mat) const;
		Matrix4 convertMatrixFromParent(const Matrix4 &mat) const;

		// 将力施加于坐标系的某一位置，当作用于标准球表面时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
//		void force(const Vector3 &force, const Vector3 &atPoint);
//		void force(const Vector3 &force, const Vector3 &atPoint, float rotationScalar);

	private:
		Matrix4 _matrix;
		Vector3 _size;
		float _opacity;
	};
	
}; // end namespace

#endif /* Object_hpp */

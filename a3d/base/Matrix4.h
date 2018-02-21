//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Matrix4_hpp
#define a3d_Matrix4_hpp

#include <GLKit/GLKMath.h>
#include <string>
#include "Vector3.h"
#include "Point3.h"
#include "Axis.h"
#include "Quaternion.h"

// 矩阵乘法的含义：
// mat1 * mat2: mat1 在自己的坐标系内做 mat2 变换，或者说 mat2 在父坐标系内做 mat1 变换
// 矩阵除法的含义：
// mat2 / mat1: mat1 为了与 mat2 重合，需要在父坐标系内做的变换(D=m2/m1, D*m1=m2)

namespace a3d{
	class Matrix4
	{
	public:
		/// 静态方法
		static Matrix4 identity();
		static Matrix4 frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
		static Matrix4 ortho(float left, float right, float bottom, float top, float nearZ, float farZ);

		// 创建一个单位向量
		Matrix4();
		Matrix4(const Quaternion &quat);
		std::string str() const;

	public:
		/// 属性
		const float* array() const;
		
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

	public:
		/// 方法
		void translate(float dx, float dy, float dz);
		void translate(const Vector3 &offset);
		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);
		void rotate(float degree, const Vector3 &vec);
		// 绕自身坐标系内的任意轴旋转
		void rotate(float degree, const Axis &axis);
		void scale(float xyz);
		void scale(const Vector3 &scale);
		void scale(float x, float y, float z);
		void resetScale();

		Matrix4 invert() const;
		Matrix4 mul(const Matrix4 &mat) const;
		Matrix4 div(const Matrix4 &mat) const;

		Vector3 mul(const Vector3 &vec) const;
		Point3 mul(const Point3 &pos) const;

	private:
		GLKMatrix4 _mat;
		Matrix4(const GLKMatrix4 &mat);
	};
	
}; // end namespace

#endif /* Matrix4_hpp */

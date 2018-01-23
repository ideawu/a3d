//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Matrix4_hpp
#define Matrix4_hpp

#include <GLKit/GLKMath.h>
#include "Vector3.h"
#include "Axis.h"

namespace a3d{
	class Matrix4
	{
	public:
		// 创建一个单位向量
		Matrix4();
		
		/// 静态方法
		static Matrix4 identity();
		static Matrix4 frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
		static Matrix4 ortho(float left, float right, float bottom, float top, float nearZ, float farZ);

	public:
		/// 属性
		const float* array() const;
		
		// decompose position
		Vector3 position() const;
		void position(const Vector3 &pos);
		void position(float x, float y, float z);
		float x() const;
		void x(float x);
		float y() const;
		void y(float y);
		float z() const;
		void z(float z);
		
		// decompose scale
		Vector3 scale() const;
		// TODO: decompose rotation, Quaternion?
//		Vector3 rotation() const;

	public:
		/// 方法
		void translate(float x, float y, float z);
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

		Matrix4 invert() const;
		Matrix4 mul(const Matrix4 &mat) const;
		// 返回目标矩阵距离当前矩阵需要做的变换
		Matrix4 div(const Matrix4 &mat) const;
		
		Vector3 mul(const Vector3 &vec, bool withTranslation) const;

	private:
		GLKMatrix4 _mat;
		Matrix4(const GLKMatrix4 &mat);
	};
	
}; // end namespace

#endif /* Matrix4_hpp */

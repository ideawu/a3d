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
		/// 静态方法
		// 创建一个单位向量
		Matrix4();
		Matrix4(GLKMatrix4 mat);
		
		static Matrix4 identity();

	public:
		/// 属性
		const float* matrix() const;
		
		Vector3 pos() const;
		void pos(Vector3 pos);
		float x() const;
		void x(float x);
		float y() const;
		void y(float y);
		float z() const;
		void z(float z);

	public:
		/// 方法
		void translate(float x, float y, float z);
		void translate(Vector3 offset);
		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);
		void rotate(float degree, Vector3 vec);
		// 绕自身坐标系内的任意轴旋转
		void rotate(float degree, const Axis &axis);
		void scale(float xyz);
		void scale(float x, float y, float z);

		Matrix4 invert() const;
		Matrix4 mul(Matrix4 mat) const;
		// 返回当前矩阵要达到目标矩阵需要做的变换
		Matrix4 diff(Matrix4 second) const;
		
		Vector3 mulVector3(Vector3 vec) const;

//	public:
	private:
		GLKMatrix4 _mat;
	};
	
}; // end namespace

#endif /* Matrix4_hpp */

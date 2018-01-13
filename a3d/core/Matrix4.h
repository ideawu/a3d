//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Matrix4_hpp
#define Matrix4_hpp

#include <GLKit/GLKMath.h>
#include "Vector3.h"

namespace a3d{
	class Matrix4
	{
	private:
		GLKMatrix4 _mat;
	public:
		/// 静态方法
		Matrix4(); // 创建一个单位向量
		Matrix4(GLKMatrix4 mat);
		
		static Matrix4 identity();
		
	public:
		/// 属性
		Vector3 pos() const;
		float x() const;
		float y() const;
		float z() const;
		
	public:
		/// 方法
		void translate(float x, float y, float z);
		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);
		void rotate(float degree, Vector3 axis);
		void scale(float x, float y, float z);

		Matrix4 invert(Matrix4 mat) const;

		Matrix4 add(Matrix4 mat) const;
		Matrix4 sub(Matrix4 mat) const;
		Matrix4 mul(Matrix4 mat) const;
		
		Vector3 mulVector3(Vector3 vec) const;
	};
	
}; // end namespace

#endif /* Matrix4_hpp */

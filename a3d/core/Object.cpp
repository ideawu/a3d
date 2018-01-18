//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Object.h"

namespace a3d{
	Object::Object(){
	}

	Object::Object(float w, float h, float d){
		_size = Vector3(w, h, d);
	}

	Vector3 Object::size() const{
		return _size;
	}
	
	void Object::size(Vector3 size){
		_size = size;
	}

	float Object::width() const{
		return _size.x();
	}
	
	void Object::width(float w){
		_size.x(w);
	}

	float Object::height() const{
		return _size.y();
	}
	
	void Object::height(float h){
		_size.y(h);
	}

	float Object::depth() const{
		return _size.z();
	}
	
	void Object::depth(float d){
		_size.z(d);
	}
	
	void Object::move(float x, float y, float z){
		this->translate(x, y, z);
	}
	
	void Object::move(Vector3 offset){
		this->translate(offset);
	}

	void Object::transform(Vector3 size){
		this->size(_size.add(size));
	}

	void Object::transform(Matrix4 mat){
		this->mul(mat);
	}

	void Object::transform(Transform trans){
		this->transform(trans.size);
		this->transform(trans.matrix);
	}

}; // end namespace

/*
 
 // 将力施加与坐标系的某一位置，当作用于标准球位置时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
 - (void)force:(GLKVector3)force atPoint:(GLKVector3)point{
 return [self force:force atPoint:point rotationScalar:1];
 }
 
 - (void)force:(GLKVector3)force atPoint:(GLKVector3)point rotationScalar:(float)scalar{
 GLKVector3 normal = GLKVector3Normalize(GLKVector3Make(point.x, point.y, point.z));
 // 将力分解为球表面法线方向(或反方向)和切线方向，法线方向即位移，切线方向即旋转方向
 GLKVector3 offset;
 GLKVector3 tangent;
 float len = trimf(GLKVector3DotProduct(force, normal));
 if(len == 0){ // 力与法线垂直
 offset = GLKVector3Make(0, 0, 0);
 tangent = force;
 }else if(trimf(fabs(len) - 1) == 0){ // 力与法线平行
 offset = force;
 tangent = GLKVector3Make(0, 0, 0);
 }else{
 offset = GLKVector3MultiplyScalar(normal, len); // 法线力
 tangent = GLKVector3Subtract(force, offset); // 切线力
 }
 GLKVector3 axis = GLKVector3CrossProduct(normal, tangent); // 旋转轴
 float degree = scalar * GLKVector3Length(tangent);
 
 log_debug(@"force: %@", NSStringFromGLKVector3(force));
 log_debug(@"point: %@", NSStringFromGLKVector3(point));
 log_debug(@"normal: %@", NSStringFromGLKVector3(normal));
 log_debug(@"offset: %@", NSStringFromGLKVector3(offset));
 log_debug(@"tangent: %@", NSStringFromGLKVector3(tangent));
 log_debug(@"degree: %f, axis: %.2f %.2f %.2f", degree, axis.x, axis.y, axis.z);
 
 [self moveX:offset.x y:offset.y z:offset.z];
 [self rotate:degree x:axis.x y:axis.y z:axis.z];
 }
 */

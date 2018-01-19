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

	Matrix4 Object::matrix() const{
		return _matrix;
	}

	Vector3 Object::pos() const{
		return Vector3(x(), y(), z());
	}
	
	void Object::pos(const Vector3 &pos){
		this->x(pos.x);
		this->y(pos.y);
		this->z(pos.z);
	}
	
	float Object::x() const{
		return _matrix.x();
	}
	
	void Object::x(float x){
		_matrix.x(x);
	}
	
	float Object::y() const{
		return _matrix.y();
	}
	
	void Object::y(float y){
		_matrix.y(y);
	}
	
	float Object::z() const{
		return _matrix.z();
	}
	
	void Object::z(float z){
		_matrix.z(z);
	}

	Vector3 Object::size() const{
		return _size;
	}
	
	void Object::size(const Vector3 &size){
		_size = size;
	}

	float Object::width() const{
		return _size.x;
	}
	
	void Object::width(float w){
		_size.x = w;
	}

	float Object::height() const{
		return _size.y;
	}
	
	void Object::height(float h){
		_size.y = h;
	}

	float Object::depth() const{
		return _size.z;
	}
	
	void Object::depth(float d){
		_size.z = d;
	}
	
	void Object::move(float x, float y, float z){
		_matrix.translate(x, y, z);
	}
	
	void Object::move(const Vector3 &offset){
		_matrix.translate(offset);
	}

	void Object::rotateX(float degree){
		_matrix.rotateX(degree);
	}
	
	void Object::rotateY(float degree){
		_matrix.rotateY(degree);
	}
	
	void Object::rotateZ(float degree){
		_matrix.rotateZ(degree);
	}
	
	void Object::rotate(float degree, const Vector3 &vec){
		_matrix.rotate(degree, vec);
	}
	
	// 绕自身坐标系内的任意轴旋转
	void Object::rotate(float degree, const Axis &axis){
		_matrix.rotate(degree, axis);
	}
	
	void Object::scale(float xyz){
		this->scale(xyz, xyz, xyz);
	}
	
	void Object::scale(float x, float y, float z){
		_matrix.scale(x, y, z);
		this->width(this->width() * x);
		this->height(this->height() * y);
		this->depth(this->depth() * z);
	}
	
	void Object::transform(const Vector3 &size){
		this->size(_size.add(size));
	}

	void Object::transform(const Matrix4 &mat){
		_matrix = _matrix.mul(mat);
	}

	void Object::transform(const Transform &trans){
		this->transform(trans.size);
		this->transform(trans.matrix);
	}

}; // end namespace


// // 将力施加与坐标系的某一位置，当作用于标准球位置时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
// - (void)force:(GLKVector3)force atPoint:(GLKVector3)point{
// return [self force:force atPoint:point rotationScalar:1];
// }
// 
// - (void)force:(GLKVector3)force atPoint:(GLKVector3)point rotationScalar:(float)scalar{
// GLKVector3 normal = GLKVector3Normalize(GLKVector3Make(point.x, point.y, point.z));
// // 将力分解为球表面法线方向(或反方向)和切线方向，法线方向即位移，切线方向即旋转方向
// GLKVector3 offset;
// GLKVector3 tangent;
// float len = trimf(GLKVector3DotProduct(force, normal));
// if(len == 0){ // 力与法线垂直
// offset = GLKVector3Make(0, 0, 0);
// tangent = force;
// }else if(trimf(fabs(len) - 1) == 0){ // 力与法线平行
// offset = force;
// tangent = GLKVector3Make(0, 0, 0);
// }else{
// offset = GLKVector3MultiplyScalar(normal, len); // 法线力
// tangent = GLKVector3Subtract(force, offset); // 切线力
// }
// GLKVector3 axis = GLKVector3CrossProduct(normal, tangent); // 旋转轴
// float degree = scalar * GLKVector3Length(tangent);
// 
// log_debug(@"force: %@", NSStringFromGLKVector3(force));
// log_debug(@"point: %@", NSStringFromGLKVector3(point));
// log_debug(@"normal: %@", NSStringFromGLKVector3(normal));
// log_debug(@"offset: %@", NSStringFromGLKVector3(offset));
// log_debug(@"tangent: %@", NSStringFromGLKVector3(tangent));
// log_debug(@"degree: %f, axis: %.2f %.2f %.2f", degree, axis.x, axis.y, axis.z);
// 
// [self moveX:offset.x y:offset.y z:offset.z];
// [self rotate:degree x:axis.x y:axis.y z:axis.z];
// }


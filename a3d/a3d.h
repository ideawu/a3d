//  Created by ideawu on 02/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef A3D_h
#define A3D_h

#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>

#ifdef __cplusplus
namespace a3d{
}; // end namespace
#endif

#include "Matrix4.h"
#include "Axis.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Point3.h"
#include "Color.h"
#include "Frame.h"
#include "Clock.h"

#include "Object.h"
#include "Transform.h"
#include "Node.h"
#include "SpriteNode.h"
#include "Sprite.h"
#include "ImageSprite.h"
#include "Camera.h"
#include "Scene.h"

#include "Animate.h"
#include "Animator.h"
#include "AnimationTypes.h"

#include "Texture.h"
#include "Renderer.h"

#include "Context.h"
#include "Drawable.h"

#ifdef __OBJC__
#	include "A3DView.h"
#endif // end __OBJC__

#endif

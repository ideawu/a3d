//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Drawable.h"

namespace a3d{
	void Drawable::render(){
		pushMatrix();
		draw();
		popMatrix();
	}

	void Drawable::pushMatrix(){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)this->matrix());
	}
	
	void Drawable::popMatrix(){
		glPopMatrix();
	}
	
}; // end namespace

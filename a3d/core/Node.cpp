//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"

namespace a3d{
	void Node::render(){
		pushMatrix();
		draw();
		popMatrix();
	}

	void Node::pushMatrix(){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)this->matrix());
	}
	
	void Node::popMatrix(){
		glPopMatrix();
	}
	
}; // end namespace

//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef DraftImage_hpp
#define DraftImage_hpp

class DraftImage : public a3d::Drawable
{
public:
	DraftImage(const char *filename);
	virtual void draw();
private:
	DraftImage(){};
};

#endif /* DraftImage_hpp */

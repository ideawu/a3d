//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

namespace a3d{
	class Color
	{
	public:
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a=1);
		
		static Color black(){return Color(0,0,0);}
		static Color white(){return Color(1,1,1);}
		static Color red(){return Color(1,0,0);}
		static Color green(){return Color(0,1,0);}
		static Color blue(){return Color(0,0,1);}
		static Color gray(){return Color(0.5,0.5,0.5);}
		static Color yellow(){return Color(1,1,0);}
	};
}; // end namespace

#endif /* Color_hpp */

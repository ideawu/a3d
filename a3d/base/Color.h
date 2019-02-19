//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Color_hpp
#define a3d_Color_hpp

namespace a3d{
	class Color
	{
	public:
		union{
			struct{float r, g, b, a;};
			float m[4];
		};

		Color();
		Color(float r, float g, float b, float a=1);
		
		static Color clear(){ return Color(0,0,0, 0);} // 透明
		static Color black(){ return Color(0,0,0);}
		static Color white(){ return Color(1,1,1);}
		static Color red(){   return Color(1,0,0);}
		static Color green(){ return Color(0,1,0);}
		static Color blue(){  return Color(0,0,1);}
		static Color gray(){  return Color(0.5,0.5,0.5);}
		static Color yellow(){return Color(1,1,0);}
	};
}; // end namespace

#endif /* Color_hpp */

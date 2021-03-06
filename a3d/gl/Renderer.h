//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Renderer_hpp
#define a3d_Renderer_hpp

#include <vector>
#include "Color.h"
#include "Matrix4.h"

namespace a3d{
	class Renderer
	{
	public:
		Renderer();

		float opacity() const;
		// 基于当前的透明度叠加新的透明度
		void pushOpacity(float opacity);
		void popOpacity();
		
		// 基于当前的矩阵叠加新矩阵
		void pushMatrix(const Matrix4 &mat);
		void popMatrix();

		void clearStencil();
		void pushStencil();
		void bindStencil();
		void popStencil();

	private:
		Renderer(const Renderer &d);
		Renderer& operator =(const Renderer &d);

		float _opacity;
		std::vector<float> _opacity_list;
		
		int _stencilRef;
		// 只在 stencil buffer 上作画，忽略 color 和 depth
		void beginStencil();
		// 结束只在 stencil buffer 上作画
		void endStencil();
	};
}; // end namespace

#endif /* Renderer_hpp */

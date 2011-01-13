#ifndef OSS_CLASSIC_UI_TOOLS_TOOL_H
#define OSS_CLASSIC_UI_TOOLS_TOOL_H

#include "tools.h"


namespace OSS {
	namespace Classic {
		class Tool : public SceneObject, public Responder {
			
			/**
			 * Construction
			 */
		public:
			const Pointer<ToolsUI> ui;
			Tool(ToolsUI * ui) : ui(ui) {}
			
			
			/**
			 * State
			 */
		public:
			virtual void update() {}
			
			
			/**
			 * Drawing
			 */
		public:
			virtual void draw(rectd dirtyRect) {}
			
			
			/**
			 * Event
			 */
		public:
			virtual bool eventMouseDown(MouseButtonEvent * event) { return false; }
			virtual bool eventMouseUp(MouseButtonEvent * event) { return false; }
			virtual bool eventMouseMove(MouseMoveEvent * event) { return false;}
		};
	}
}


#endif

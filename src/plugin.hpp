#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
// extern Model *modelMyModule;
extern Model *modelAuto_8vert;
extern Model *modelEurogen;
extern Model *CVMap;

struct LilKnob : RoundBlackKnob {
	LilKnob() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Little_Knob.svg")));
	}
};

struct Little_In : PJ301MPort {
	Little_In() {
		box.size = Vec(20, 20);
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Little_In.svg")));
	}
};
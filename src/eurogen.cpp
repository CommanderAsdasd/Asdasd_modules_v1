#include "plugin.hpp"

struct Eurogen : Module {
    enum ParamIds {
    };
    enum OutputIds {
    };

    Eurogen() {
        // config()
    }

    void process(const ProcessArgs &args) override {

    }
};

struct EurogenWidget : ModuleWidget {
    EurogenWidget(Eurogen * module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/asdasd_notes.svg")));
    }

};

Model* modelEurogen = createModel<Eurogen, EurogenWidget>("eurogen");
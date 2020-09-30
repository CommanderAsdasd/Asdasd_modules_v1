#include "plugin.hpp"


struct Auto_8vert : Module {
	enum ParamIds {
		ENUMS(PARAMS_GAIN, 8),
		ENUMS(PARAMS_OFFSET, 8),
		NUM_PARAMS
	};

	enum InputIds {
		ENUMS(IN_INPUTS, 8),
		ENUMS(CV_GAIN, 8),
		ENUMS(CV_OFFSET, 8),
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUT_OUTPUTS, 8),
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Auto_8vert() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		for (int i = 0; i < 8; i++) {
			configParam(PARAMS_GAIN + i, -1.f, 1.f, 0.f, string::f("Ch %d gain", i + 1), "%", 0, 100);
			configParam(PARAMS_OFFSET + i, -4.f, 4.f, 0.0f, string::f("Ch %d offset", i + 1), " v");
		}
	}

	void process(const ProcessArgs &args) override {
		float in[16] = {10.f};
		int channels = 1;

		for (int i = 0; i < 8; i++) {
			// Get input
			if (inputs[IN_INPUTS + i].isConnected()) {
				channels = inputs[IN_INPUTS + i].getChannels();
				inputs[IN_INPUTS + i].readVoltages(in);
			}

			if (outputs[OUT_OUTPUTS + i].isConnected()) {
				
				float out[16];
				float gain[16];
				float offset[16];
				
				// collect gains from knobs and CV

				if (inputs[CV_GAIN + i].isConnected()){
					inputs[CV_GAIN + i].readVoltages(gain);
					for (int c = 0; c < channels; c++) {
						gain[c] = gain[c] + params[PARAMS_GAIN + i].getValue();
					}
				} else {
					for (int c = 0; c < channels; c++) {
						gain[c] = params[PARAMS_GAIN + i].getValue();
					}
				}

				// collect offsets from knobs and CV

				if (inputs[CV_OFFSET + i].isConnected()){
					for (int c = 0; c < channels; c++) {
						offset[c] = inputs[CV_OFFSET + i].getPolyVoltage(c);
						offset[c] = clamp(offset[c] + params[PARAMS_OFFSET + i].getValue(),-4.f, 4.f);
					}
				} else {
					for (int c = 0; c < channels; c++) {
						offset[c] = params[PARAMS_OFFSET + i].getValue();
					}
				}

				for (int c = 0; c < channels; c++) {
					for (int gc = 0; gc < channels; gc++) {
						out[c] = gain[c] * in[c] + offset[c];
					}
				}

				// Set output
				outputs[OUT_OUTPUTS + i].setChannels(channels);
				outputs[OUT_OUTPUTS + i].writeVoltages(out);
			}
		}
	}
};


struct Auto_8vertWidget : ModuleWidget {
	Auto_8vertWidget(Auto_8vert *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/auto_8vert.svg")));

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 30, 365)));

		addParam(createParam<LilKnob>(Vec(41.308, 47.753), module, Auto_8vert::PARAMS_GAIN + 0));
		addParam(createParam<LilKnob>(Vec(41.308, 86.198), module, Auto_8vert::PARAMS_GAIN + 1));
		addParam(createParam<LilKnob>(Vec(41.308, 124.639), module, Auto_8vert::PARAMS_GAIN + 2));
		addParam(createParam<LilKnob>(Vec(41.308, 163.084), module, Auto_8vert::PARAMS_GAIN + 3));
		addParam(createParam<LilKnob>(Vec(41.308, 201.529), module, Auto_8vert::PARAMS_GAIN + 4));
		addParam(createParam<LilKnob>(Vec(41.308, 239.974), module, Auto_8vert::PARAMS_GAIN + 5));
		addParam(createParam<LilKnob>(Vec(41.308, 278.415), module, Auto_8vert::PARAMS_GAIN + 6));
		addParam(createParam<LilKnob>(Vec(41.308, 316.86), module, Auto_8vert::PARAMS_GAIN + 7));

		addInput(createInput<Little_In>(Vec(41.308, 50.397+15), module, Auto_8vert::CV_GAIN + 0));
		addInput(createInput<Little_In>(Vec(41.308, 88.842+15), module, Auto_8vert::CV_GAIN + 1));
		addInput(createInput<Little_In>(Vec(41.308, 127.283+15), module, Auto_8vert::CV_GAIN + 2));
		addInput(createInput<Little_In>(Vec(41.308, 165.728+15), module, Auto_8vert::CV_GAIN + 3));
		addInput(createInput<Little_In>(Vec(41.308, 204.173+15), module, Auto_8vert::CV_GAIN + 4));
		addInput(createInput<Little_In>(Vec(41.308, 242.614+15), module, Auto_8vert::CV_GAIN + 5));
		addInput(createInput<Little_In>(Vec(41.308, 281.059+15), module, Auto_8vert::CV_GAIN + 6));
		addInput(createInput<Little_In>(Vec(41.308, 319.504+15), module, Auto_8vert::CV_GAIN + 7));

		addParam(createParam<LilKnob>(Vec(41.308+20.0, 47.753), module, Auto_8vert::PARAMS_OFFSET + 0));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 86.198), module, Auto_8vert::PARAMS_OFFSET + 1));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 124.639), module, Auto_8vert::PARAMS_OFFSET + 2));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 163.084), module, Auto_8vert::PARAMS_OFFSET + 3));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 201.529), module, Auto_8vert::PARAMS_OFFSET + 4));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 239.974), module, Auto_8vert::PARAMS_OFFSET + 5));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 278.415), module, Auto_8vert::PARAMS_OFFSET + 6));
		addParam(createParam<LilKnob>(Vec(41.308+20.0, 316.86), module, Auto_8vert::PARAMS_OFFSET + 7));

		addInput(createInput<Little_In>(Vec(41.308+20.0, 50.397+15), module, Auto_8vert::CV_OFFSET + 0));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 88.842+15), module, Auto_8vert::CV_OFFSET + 1));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 127.283+15), module, Auto_8vert::CV_OFFSET + 2));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 165.728+15), module, Auto_8vert::CV_OFFSET + 3));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 204.173+15), module, Auto_8vert::CV_OFFSET + 4));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 242.614+15), module, Auto_8vert::CV_OFFSET + 5));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 281.059+15), module, Auto_8vert::CV_OFFSET + 6));
		addInput(createInput<Little_In>(Vec(41.308+20.0, 319.504+15), module, Auto_8vert::CV_OFFSET + 7));

		addInput(createInput<PJ301MPort>(Vec(9.507, 50.397), module, Auto_8vert::IN_INPUTS + 0));
		addInput(createInput<PJ301MPort>(Vec(9.507, 88.842), module, Auto_8vert::IN_INPUTS + 1));
		addInput(createInput<PJ301MPort>(Vec(9.507, 127.283), module, Auto_8vert::IN_INPUTS + 2));
		addInput(createInput<PJ301MPort>(Vec(9.507, 165.728), module, Auto_8vert::IN_INPUTS + 3));
		addInput(createInput<PJ301MPort>(Vec(9.507, 204.173), module, Auto_8vert::IN_INPUTS + 4));
		addInput(createInput<PJ301MPort>(Vec(9.507, 242.614), module, Auto_8vert::IN_INPUTS + 5));
		addInput(createInput<PJ301MPort>(Vec(9.507, 281.059), module, Auto_8vert::IN_INPUTS + 6));
		addInput(createInput<PJ301MPort>(Vec(9.507, 319.504), module, Auto_8vert::IN_INPUTS + 7));

		addOutput(createOutput<PJ301MPort>(Vec(86.393, 50.397), module, Auto_8vert::OUT_OUTPUTS + 0));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 88.842), module, Auto_8vert::OUT_OUTPUTS + 1));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 127.283), module, Auto_8vert::OUT_OUTPUTS + 2));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 165.728), module, Auto_8vert::OUT_OUTPUTS + 3));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 204.173), module, Auto_8vert::OUT_OUTPUTS + 4));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 242.614), module, Auto_8vert::OUT_OUTPUTS + 5));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 281.059), module, Auto_8vert::OUT_OUTPUTS + 6));
		addOutput(createOutput<PJ301MPort>(Vec(86.393, 319.504), module, Auto_8vert::OUT_OUTPUTS + 7));
	}
};


Model* modelAuto_8vert = createModel<Auto_8vert, Auto_8vertWidget>("auto_8vert");
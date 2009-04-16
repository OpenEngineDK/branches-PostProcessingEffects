#include "GaussianBlur.h"

GaussianBlur::GaussianBlur(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,false) {
}

void GaussianBlur::Setup() {

    // calc gaussian values (with variance=1) in the interval [-4;4];
    calcBlurWeightArray();

    vector<vector<float> > weights;
    for (int i=0; i<NUM_SAMPLES; i++) {
	vector<float> weight;
	weight.push_back(blurweights[i]);
	weights.push_back(weight);
    }

    // init passes
    pass1 = AddPass("Effects/GaussianBlur_Pass1.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->BindFloat("weights", weights);
    pass1->AttachUserBuffer(0);
    //pass1->enableOutputToColorBuffer();

    pass2 = AddPass("Effects/GaussianBlur_Pass2.frag");
    pass2->BindUserBuffer("colorbuf", pass1, 0);
    pass2->BindFloat("weights", weights);
    pass2->EnableColorBufferOutput();
}

void GaussianBlur::PerFrame(const float deltaTime) {
}

// see wiki: http://en.wikipedia.org/wiki/Gaussian_blur
// calc 1D gaussian weights (with sigma = 1) => standard normal distribution function
float GaussianBlur::g(float x) {
    static const float PI = 3.14159265;
    float power       = - x*x / 2;
    float denominator = (float)sqrt(2*PI);

    return 1.0f / denominator * (float)exp(power);
}

// calc gaussian values (with variance=1) in the interval [-4;4];
void GaussianBlur::calcBlurWeightArray() {

     float xmin = -4;
     float xmax = 4;
     float xstep = (xmax-xmin)/NUM_SAMPLES;

     float sum = 0;

     float x = xmin;
     for (int i=0; i<NUM_SAMPLES; i++) {

	blurweights[i] = g(x);

	//printf("i=%d, G(%f) = %f\n", i, x, g(x));
	sum += g(x);

	x += xstep;
     }

     //printf("sum=%f\n", sum);

     // normalize, so that the sum of weights are 1
     for (int i=0; i<NUM_SAMPLES; i++) {
	 blurweights[i] /= sum;
     }

}

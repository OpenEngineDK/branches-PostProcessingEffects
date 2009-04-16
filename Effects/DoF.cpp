#include "DoF.h"

DoF::DoF(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,true) {
    znear .push_back(10);
    zfar  .push_back(33000);
    zsharp.push_back(500);
}

void DoF::Setup() {

    // calc gaussian values (with variance=1) in the interval [-4;4];
    calcBlurWeightArray();

    vector<vector<float> > weights;
    for (int i=0; i<NUM_SAMPLES; i++) {
	vector<float> weight;
	weight.push_back(blurweights[i]);
	weights.push_back(weight);
    }

    // blur
    pass1 = AddPass("Effects/GaussianBlur_Pass1.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->BindFloat("weights", weights);
    pass1->AttachUserBuffer(0);

    pass2 = AddPass("Effects/GaussianBlur_Pass2.frag");
    pass2->BindUserBuffer("colorbuf", pass1, 0);
    pass2->BindFloat("weights", weights);
    pass2->AttachUserBuffer(0);

/*
    pass1 = AddPass("TwoPassBlur_Pass1.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->AttachUserBuffer(0);

    pass2 = AddPass("TwoPassBlur_Pass2.frag");
    pass2->BindUserBuffer("colorbuf", pass1, 0);
    pass2->AttachUserBuffer(0);
*/
    // dof
    IPostProcessingPass* pass3 = AddPass("Effects/DoF.frag");
    pass3->BindFloat("znear", znear);
    pass3->BindFloat("zfar", zfar);
    pass3->BindFloat("zsharp", zsharp);
    pass3->BindUserBuffer ("blurred", pass2, 0);
    pass3->BindColorBuffer("unblurred");
    pass3->BindDepthBuffer("depthbuf");
    pass3->EnableColorBufferOutput();
}

void DoF::PerFrame(const float deltaTime) {

    ITexture2DPtr tex = GetFinalColorBufferRef();

    // display data
    /*
    float* data = (float*)tex->GetData();
    //for (int i=0; i<tex->GetWidth()*tex->GetHeight()*4; i+=4) {
    for (int i=0; i<4*1; i+=4) {
	printf("(%f, %f, %f ,%f)\n", data[i], data[i+1], data[i+2], data[i+3]);
    }
    delete data;
    */


}

// see wiki: http://en.wikipedia.org/wiki/Gaussian_blur
// calc 1D gaussian weights (with sigma = 1) => standard normal distribution function
float DoF::g(float x) {
    static const float PI = 3.14159265;
    float power       = - x*x / 2;
    float denominator = (float)sqrt(2*PI);

    return 1.0f / denominator * (float)exp(power);
}

// calc gaussian values (with variance=1) in the interval [-4;4];
void DoF::calcBlurWeightArray() {

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


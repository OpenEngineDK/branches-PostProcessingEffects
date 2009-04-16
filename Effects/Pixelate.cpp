#include "Pixelate.h"

// clean up, plz

Pixelate::Pixelate(Viewport* viewport, IEngine& engine) : PostProcessingEffect(viewport,engine,false) {
    this->viewport = viewport;
    this->xcnt = 0;
    this->ycnt = 0;
}

void Pixelate::Setup() {

    pass1 = AddPass("Effects/pixelate.frag");
    pass1->BindColorBuffer("colorbuf");
    pass1->EnableColorBufferOutput();

    xsize.push_back(1);
    ysize.push_back(1);

    pass1->BindFloat("xsize", xsize);
    pass1->BindFloat("ysize", ysize);

    vector<int> screenxsize;
    vector<int> screenysize;
    screenxsize.push_back(viewport->GetDimension()[2]);
    screenysize.push_back(viewport->GetDimension()[3]);

    pass1->BindInt("scrxsize", screenxsize);
    pass1->BindInt("scrysize", screenysize);
}


void Pixelate::PerFrame(const float deltaTime) {

    // set new zoom size
    xsize[0] = (sin(xcnt)+1.1)/20.0 * viewport->GetDimension()[2];
    ysize[0] = (sin(ycnt)+1.1)/20.0 * viewport->GetDimension()[3];

    pass1->BindFloat("xsize", xsize);
    pass1->BindFloat("ysize", ysize);

    xcnt += 0.001 * deltaTime;
    ycnt += 0.001 * deltaTime;

    // set screen size again (if it was changed since last time)
    vector<int> screenxsize;
    vector<int> screenysize;
    screenxsize.push_back(viewport->GetDimension()[2]);
    screenysize.push_back(viewport->GetDimension()[3]);

    pass1->BindInt("scrxsize", screenxsize);
    pass1->BindInt("scrysize", screenysize);

}

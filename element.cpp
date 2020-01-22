#include "element.h"

Element::Element(int _x, int _y, std::string img_path){
    x = _x;
    y = _y;
    img = load_bitmap(img_path, NULL);
}

Element::render(Bitmap *buffer){

}

Element::update(){
}

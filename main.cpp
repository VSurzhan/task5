#include "head.hpp"

int main() {
    Parametrs param;
    std::vector<Figure*> objects;

    std::string file;

    std::cout << "Enter file with parametrs: ";
    std::cin >> file;
    
    bool res1 = GetParametrs(file, param);
    if(!res1) {
        return -1;
    }

    std::cout << "Enter file with objects: ";
    std::cin >> file;
    
    bool res2 = GetFigures(file, objects);
    if(!res2) {
        return -1;
    }

    
    std::map<double, size_t> cntDistantFig;

    for(size_t i = 0; i < objects.size(); ++i) {
        double v = (objects[i]->center()-param.cam).norm();
        ++cntDistantFig[v];
    }
    
    Vec3d colour_min(255, 0, 0);
    Vec3d colour_max(0, 0, 255);

    double b = 255/(cntDistantFig.size()-1);
    for(size_t i = 0; i < objects.size(); ++i) {
        double q = 0; // порядковый номер
        for(auto it : cntDistantFig) {
            if(it.first == (objects[i]->center()-param.cam).norm()) break;
            ++q;
        }
        if(q == 0) objects[i]->UpdateColour(colour_min);
        else if(q == cntDistantFig.size()-1) objects[i]->UpdateColour(colour_max);
        else objects[i]->UpdateColour(Vec3d(255.0-b*q, 0, 255.0-b*q));
    }

    create_image(objects, param);

    return 0;
}


#include "head.hpp"
#include "Figure_Factory.hpp"

bool GetParametrs(const std::string& FileName, Parametrs& param) {
    std::ifstream inp(FileName);
    
    if(!inp){
        std::cout << "Error! Cannot open file: " << FileName << "\n";
        return 0;
    }
    
    while(!inp.eof()){
        std::string I; inp >> I;

        if(I == "cam") {
            double x, y, z;
            inp >> x >> y >> z;
            param.cam = Vec3d(x, y, z);
        }
        else if(I == "width") {
            inp >> param.width;
        }
        else if(I == "height") {
            inp >> param.height;
        }
        else if(I == "light") {
            double x, y, z;
            inp >> x >> y >> z;
            param.light = Vec3d(x, y ,z);
        }
        else if(I == "normal") {
            double x, y, z;
            inp >> x >> y >> z;
            param.normal = Vec3d(x, y ,z);
        }
        else if(I == "up") {
            double x, y, z;
            inp >> x >> y >> z;
            param.up = Vec3d(x, y ,z);
        }
        else if(I == "screen") {
            inp >> param.screen;
        }
        else if(I == "limit") {
            inp >> param.limit;
        }
        else if(I == "alpha") {
            inp >> param.alpha;
        }
        else{
            std::cout << "Error! Unknown parametr: " << I << "\n";
            inp.close();
            return 0;
        }
    }

    inp.close();

    return 1;
}

bool GetFigures(const std::string& FileName, std::vector<Figure*>& objects) {
    std::ifstream inp(FileName);
    if(!inp){
        std::cout << "Error! Cannot open file: " << FileName << "\n";
        return 0;
    }

    
    std::map<std::string, Creator*> Factory;
    Factory["sphere"] = new CreateSphere;
    Factory["tetra"]  = new CreateTetrahedron;
    

    while(!inp.eof()) {
        std::string I; inp >> I;

        
        auto ConcreteCreator = Factory.find(I);
        if(ConcreteCreator == Factory.end()){
            std::cout << "Error! Wrong number type: " << I << "\n";
            return 0;
        }
        

        if(I == "sphere") {
            double x, y, z, r;
            inp >> x >> y >> z >> r;
            //objects.push_back(new Sphere(Vec3d(x, y, z), r));
            objects.push_back(ConcreteCreator->second->factoryMethod(Vec3d(x, y, z), r));
        } else if(I == "tetra") {
            Vec3d points[4];
            for(int i = 0; i < 4; ++i) {
                inp >> points[i][0] >> points[i][1] >> points[i][2];
            }
            //objects.push_back(new Tetrahedron(points[0], points[1], points[2], points[3]));
            objects.push_back(ConcreteCreator->second->factoryMethod(points[0], points[1], points[2], points[3]));
        }
    }
    inp.close();

    for(auto& fb : Factory) {
        delete fb.second;
    }

    return 1;
}
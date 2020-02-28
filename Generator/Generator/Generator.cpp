// Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<tuple>
#include<stdio.h>
#include<vector>
#include <iostream>
#include <fstream>
using namespace std;

errno_t err;

class Point{       
public:             
    double x = 0;        
    double y = 0;
    double z = 0;
    Point() {

    }
    Point(double x1, double y1, double z1) {
        x = x1;
        y = y1;
        z = z1;
    }

    string pointToString() {
        char* buff = (char *)malloc(sizeof(char) * 100);
        snprintf(buff,200,"%.4f %.4f %.4f",x,y,z);
        return buff;
    }
};

class Triangle{
public:
    tuple <Point, Point, Point> coord;

    Triangle() {
        Point p(0,0,0); 
        coord = make_tuple(p, p, p);
    }

    Triangle(Point a, Point b, Point c) {
        coord = make_tuple(a, b, c);
    }
};
void trianglesToFile(vector<Triangle> t, string f) {
    ofstream file(f);
    int i = 0;
    while (i < t.size()) {
        file << get<0>(t[i].coord).pointToString()<< "," << get<1>(t[i].coord).pointToString() << "," << get<2>(t[i].coord).pointToString() << endl;
        i++;
    }
}

void generatePlaneFile(float x1,float z1, string f) {
    float auxX = x1 / 2, auxZ = x1 / 2;

    //Pontos para Triangulo 1
    Point p1(-auxX, 0, auxZ);
    Point p2(-auxX, 0, -auxZ);
    Point p3(auxX, 0, auxZ);

    //Pontos para Trinagulo 2
    Point p4(-auxX, 0, auxZ);
    Point p5(auxX, 0, -auxZ);
    Point p6(auxX, 0, auxZ);

    //Triangulo 1 e 2
    Triangle t1(p1, p2, p3);
    Triangle t2(p4, p5, p6);

    vector <Triangle> v = { t1,t2 };

    trianglesToFile(v, f);

}
//plane file.3d
//box x y z (n) file.3d
//sphere 1 10 10 sphere.3d
//cone r h sl st file.3d
int main(int argc, char* argv[]){
    if (strcmp(argv[1], "plane") == 0 && argc==5){
        generatePlaneFile(atof(argv[2]),atof(argv[3]),argv[4]);
    }
    else if (strcmp(argv[1], "box") == 0) {
        ;
    }
    else if (strcmp(argv[1], "sphere") == 0) {
        ;
    }
    else if (strcmp(argv[1], "cone") == 0) {
        ;
    }

}

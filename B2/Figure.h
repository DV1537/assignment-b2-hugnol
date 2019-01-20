//
// Created by hugon on 16/01/2019.
//

#ifndef A2FINAL_FIGURE_H
#define A2FINAL_FIGURE_H

#include "FileFunctions.h"
#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include "Triangle.h"
#include "Polygon.h"

class Figure {
private:
    Shape **groupedShapes;
    Shape **transfer;
    int currentShapeAmount;
    int maxShapeAmount;
public:
    Figure();
    ~Figure();

    void addShape(Shape *s);
    Line getBoundingBox(); //Returns top left and bottom right corners of the box.
    void getClosest(Shape *location, int n);
};


#endif //A2FINAL_FIGURE_H

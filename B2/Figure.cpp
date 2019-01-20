//
// Created by hugon on 16/01/2019.
//

#include "Figure.h"

Figure::Figure() : currentShapeAmount(0), maxShapeAmount(5) {
    groupedShapes = new Shape *[maxShapeAmount];
}

Figure::~Figure() {
    if (groupedShapes) {
        delete[] groupedShapes;
        groupedShapes = nullptr;
    }
}

void Figure::addShape(Shape *s) {  //Shape adder
    if (currentShapeAmount == maxShapeAmount) {
        transfer = new Shape *[maxShapeAmount];
        for (int i = 0; i < maxShapeAmount; i++) {
            transfer[i] = groupedShapes[i];
        }
        delete[] groupedShapes;
        maxShapeAmount = maxShapeAmount * 2;
        groupedShapes = new Shape *[maxShapeAmount];
        for (int i = 0; i < currentShapeAmount; i++) {
            groupedShapes[i] = transfer[i];
        }
        delete[] transfer;
        transfer = nullptr;
        groupedShapes[currentShapeAmount] = s;
        currentShapeAmount++;
    } else {
        groupedShapes[currentShapeAmount] = s;
        currentShapeAmount++;
    }
}

Line Figure::getBoundingBox() {
    Point topLeft(0, 0), bottomRight(0, 0);

    for (int i = 0; i < currentShapeAmount; i++) {
        if (groupedShapes[i]->getType() == sPolygon) {
            auto *currentShape = dynamic_cast<Polygon *>(groupedShapes[i]);
            if (i == 0) {
                bottomRight.X = currentShape->points[i].X;
                bottomRight.Y = currentShape->points[i].Y;
                topLeft.X = bottomRight.X;
                topLeft.Y = bottomRight.Y;
            }
            for (int j = 0; j < currentShape->getPointsAmount(); j++) {
                if (currentShape->points[j].X < topLeft.X) {
                    topLeft.X = currentShape->points[j].X;
                }
                if (currentShape->points[j].Y > topLeft.Y) {
                    topLeft.Y = currentShape->points[j].Y;
                }
                if (currentShape->points[j].X > bottomRight.X) {
                    bottomRight.X = currentShape->points[j].X;
                }
                if (currentShape->points[j].Y < bottomRight.Y) {
                    bottomRight.Y = currentShape->points[j].Y;
                }
                delete currentShape;
            }
        } else if (groupedShapes[i]->getType() == sTriangle) {
            auto *currentShape = dynamic_cast<Triangle *>(groupedShapes[i]);
            if (i == 0) {
                bottomRight.X = currentShape->a.X;
                bottomRight.Y = currentShape->a.Y;
                topLeft.X = bottomRight.X;
                topLeft.Y = bottomRight.Y;
            }
            if (currentShape->a.X < topLeft.X) {
                topLeft.X = currentShape->a.X;
            }
            if (currentShape->a.Y > topLeft.Y) {
                topLeft.Y = currentShape->a.Y;
            }
            if (currentShape->b.X < topLeft.X) {
                topLeft.X = currentShape->b.X;
            }
            if (currentShape->b.Y > topLeft.Y) {
                topLeft.Y = currentShape->b.Y;
            }
            if (currentShape->c.X < topLeft.X) {
                topLeft.X = currentShape->c.X;
            }
            if (currentShape->c.Y > topLeft.Y) {
                topLeft.Y = currentShape->c.Y;
            }

            if (currentShape->a.X > bottomRight.X) {
                bottomRight.X = currentShape->a.X;
            }
            if (currentShape->a.Y < bottomRight.Y) {
                bottomRight.Y = currentShape->a.Y;
            }
            if (currentShape->b.X > bottomRight.X) {
                bottomRight.X = currentShape->b.X;
            }
            if (currentShape->b.Y < bottomRight.Y) {
                bottomRight.Y = currentShape->b.Y;
            }
            if (currentShape->c.X > bottomRight.X) {
                bottomRight.X = currentShape->c.X;
            }
            if (currentShape->c.Y < bottomRight.Y) {
                bottomRight.Y = currentShape->c.Y;
            }
            delete currentShape;
        } else if (groupedShapes[i]->getType() == sLine) {
            auto *currentShape = dynamic_cast<Line *>(groupedShapes[i]);
            if (i == 0) {
                bottomRight.X = currentShape->a.X;
                bottomRight.Y = currentShape->a.Y;
                topLeft.X = bottomRight.X;
                topLeft.Y = bottomRight.Y;
            }
            if (currentShape->a.X < topLeft.X) {
                topLeft.X = currentShape->a.X;
            }
            if (currentShape->a.Y > topLeft.Y) {
                topLeft.Y = currentShape->a.Y;
            }
            if (currentShape->b.X < topLeft.X) {
                topLeft.X = currentShape->b.X;
            }
            if (currentShape->b.Y > topLeft.Y) {
                topLeft.Y = currentShape->b.Y;
            }
            if (currentShape->a.X > bottomRight.X) {
                bottomRight.X = currentShape->a.X;
            }
            if (currentShape->a.Y < bottomRight.Y) {
                bottomRight.Y = currentShape->a.Y;
            }
            if (currentShape->b.X > bottomRight.X) {
                bottomRight.X = currentShape->b.X;
            }
            if (currentShape->b.Y < bottomRight.Y) {
                bottomRight.Y = currentShape->b.Y;
            }
            delete currentShape;

        } else if (groupedShapes[i]->getType() == sPoint) {
            auto *currentShape = dynamic_cast<Point *>(groupedShapes[i]);
            if (i == 0) {
                bottomRight.X = currentShape->X;
                bottomRight.Y = currentShape->Y;
                topLeft.X = bottomRight.X;
                topLeft.Y = bottomRight.Y;
            }
            if (currentShape->X < topLeft.X) {
                topLeft.X = currentShape->X;
            }
            if (currentShape->Y > topLeft.Y) {
                topLeft.Y = currentShape->Y;
            }
            if (currentShape->X > bottomRight.X) {
                bottomRight.X = currentShape->X;
            }
            if (currentShape->Y < bottomRight.Y) {
                bottomRight.Y = currentShape->Y;
            }
            delete currentShape;
        }
    }
    Line boundingLine(topLeft, bottomRight);
    return boundingLine;
}

void Figure::getClosest(Shape *location, int n) {
    double distances[currentShapeAmount];
    int order[currentShapeAmount];
    for (int i = 0; i < currentShapeAmount; i++) {
        distances[i] = groupedShapes[i]->distance(location);
        order[i] = i;
    }
    int index(0);
    recursiveSelectionSort(distances, order, currentShapeAmount, index);
    std::cout << "Shapes closest to choosen shape: " << std::endl;
    for (int i = 1; i < n+1; i++) {
        std::cout << "Shape #" << i << " ";
        if (groupedShapes[order[i]]->getType() == sPolygon) {
            auto *currentShape = dynamic_cast<Polygon *>(groupedShapes[order[i]]);
            std::cout << "Polygon: ";
            for (int j = 0; j < currentShape->getPointsAmount(); j++) {
                std::cout << " (" << currentShape->points[j].X << ", "
                          << currentShape->points[j].Y << ") ";
            }
            std::cout << "Distance: " << distances[i] << " length units.\n";
        } else if (groupedShapes[order[i]]->getType() == sTriangle) {
            auto *currentShape = dynamic_cast<Triangle *>(groupedShapes[order[i]]);
            std::cout << "Triangle: " << " (" << currentShape->a.X << ", " << currentShape->a.Y << ") " << " ("
                      << currentShape->b.X
                      << ", " << currentShape->b.Y << ") " << " (" << currentShape->c.X << ", " << currentShape->c.Y
                      << ") " << "Distance: " << distances[i] << " length units.\n";

        } else if (groupedShapes[order[i]]->getType() == sLine) {
            auto *currentShape = dynamic_cast<Line *>(groupedShapes[order[i]]);
            std::cout << "Line: " << " (" << currentShape->a.X << ", " << currentShape->a.Y << ") " << " ("
                      << currentShape->b.X
                      << ", " << currentShape->b.Y << ") " << "Distance: " << distances[i] << " length units.\n";

        } else if (groupedShapes[order[i]]->getType() == sPoint) {
            auto *currentShape = dynamic_cast<Point *>(groupedShapes[order[i]]);
            std::cout << "Point: " << " (" << currentShape->X << ", " << currentShape->Y << ") " << "Distance: "
                      << distances[i] << " length units.\n";
        }
    }
}

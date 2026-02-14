#include <GL/glut.h>
#include <map>
#include <string>

class point{ 
    public:
        GLfloat x, y;
        point(GLfloat x,GLfloat y){
            this->x= x;
            this->y= y;
        }
};
class color{ 
    public:
        GLfloat r,g,b;
        color(GLfloat r, GLfloat g, GLfloat b){
            this->r= r;
            this->g= g;
            this->b= b;
        }
};

std::map<std::string, point> pos= {
    {"bottomLeft"   , {  0,   0}},
    {"bottomMiddle" , { 50,   0}},
    {"bottomRight"  , {100,   0}},

    {"middleLeft"   , {  0,  50}},
    {"middleMost"   , { 50,  50}},
    {"middleRight"  , {100,  50}},

    {"topLeft"      , {  0, 100}},
    {"topMiddle"    , { 50, 100}},
    {"topRight"     , {100, 100}},
};
std::map<std::string, color> colorMap= {
    {"Grid", {0.0, 1.0, 0.0}},
    {"X", {1.0, 0.5, 0.0}},
    {"O", {0.0, 0.5, 1.0}},
};

void init(void){
    glClearColor(0.0, 0.2, 0.2, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}
void drawGrid(point origin, color c= colorMap.at("Grid")){
    glColor3f(c.r, c.g, c.b);
    // vertical lines
    glVertex2i(origin.x+  50, origin.y     );
    glVertex2i(origin.x+  50, origin.y+ 150);

    glVertex2i(origin.x+ 100, origin.y     );
    glVertex2i(origin.x+ 100, origin.y+ 150);

    // horizantal lines
    glVertex2i(origin.x     , origin.y+  50);
    glVertex2i(origin.x+ 150, origin.y+  50);

    glVertex2i(origin.x     , origin.y+ 100);
    glVertex2i(origin.x+ 150, origin.y+ 100);
}
void drawX(point origin, std::string cell, color c= colorMap.at("X")){
    glColor3f(c.r, c.g, c.b);
    point dynamicOrigin= {origin.x+ pos.at(cell).x, origin.y+ pos.at(cell).y};

    glVertex2f(dynamicOrigin.x+  5, dynamicOrigin.y+  5);
    glVertex2f(dynamicOrigin.x+ 45, dynamicOrigin.y+ 45);

    glVertex2f(dynamicOrigin.x+ 45, dynamicOrigin.y+  5);
    glVertex2f(dynamicOrigin.x+  5, dynamicOrigin.y+ 45);

}
void drawO(point origin, std::string cell, color c= colorMap.at("O")){
    glColor3f(c.r, c.g, c.b);
    point dOrg= {origin.x+ pos.at(cell).x, origin.y+ pos.at(cell).y};

    //bottom of circle
    glVertex2f(dOrg.x+ 20, dOrg.y+  5);
    glVertex2f(dOrg.x+ 30, dOrg.y+  5);

    //top of circle
    glVertex2f(dOrg.x+ 20, dOrg.y+ 45);
    glVertex2f(dOrg.x+ 30, dOrg.y+ 45);

    //left of circle
    glVertex2f(dOrg.x+  5, dOrg.y+ 20);
    glVertex2f(dOrg.x+  5, dOrg.y+ 30);

    //right of circle
    glVertex2f(dOrg.x+ 45, dOrg.y+ 20);
    glVertex2f(dOrg.x+ 45, dOrg.y+ 30);

    //top left connection
    glVertex2f(dOrg.x+  5, dOrg.y+ 30);
    glVertex2f(dOrg.x+  8, dOrg.y+ 36);

    glVertex2f(dOrg.x+  8, dOrg.y+ 36);
    glVertex2f(dOrg.x+ 14, dOrg.y+ 42);

    glVertex2f(dOrg.x+ 14, dOrg.y+ 42);
    glVertex2f(dOrg.x+ 20, dOrg.y+ 45);

    //top right connection
    glVertex2f(dOrg.x+ 45, dOrg.y+ 30);
    glVertex2f(dOrg.x+ 42, dOrg.y+ 36);

    glVertex2f(dOrg.x+ 42, dOrg.y+ 36);
    glVertex2f(dOrg.x+ 36, dOrg.y+ 42);

    glVertex2f(dOrg.x+ 36, dOrg.y+ 42);
    glVertex2f(dOrg.x+ 30, dOrg.y+ 45);

    //bottom left connection
    glVertex2f(dOrg.x+  5, dOrg.y+ 20);
    glVertex2f(dOrg.x+  8, dOrg.y+ 14);

    glVertex2f(dOrg.x+  8, dOrg.y+ 14);
    glVertex2f(dOrg.x+ 14, dOrg.y+  8);

    glVertex2f(dOrg.x+ 14, dOrg.y+  8);
    glVertex2f(dOrg.x+ 20, dOrg.y+  5);

    //bottom right connection
    glVertex2f(dOrg.x+ 45, dOrg.y+ 20);
    glVertex2f(dOrg.x+ 42, dOrg.y+ 14);

    glVertex2f(dOrg.x+ 42, dOrg.y+ 14);
    glVertex2f(dOrg.x+ 36, dOrg.y+  8);

    glVertex2f(dOrg.x+ 36, dOrg.y+  8);
    glVertex2f(dOrg.x+ 30, dOrg.y+  5);
}

void lineSegment(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    point origin= {10, 10};

    drawGrid(origin);

    // X in bottom left cell
    drawX(origin, "middleRight");
    drawX(origin, "bottomRight");

    // O in middle most cell
    drawO(origin, "middleMost");
    drawO(origin, "topLeft");

    glEnd();
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutInitWindowPosition(200, 50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("GL RGB Lines");

    init();

    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return 0;
}
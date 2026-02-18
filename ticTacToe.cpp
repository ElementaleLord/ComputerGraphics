#include <GL/glut.h>
#include <map>
#include <string>

struct point{
    GLfloat x, y;
    point(GLfloat x, GLfloat y){
        this->x= x; this-> y= y;
    }
};
struct color{
    GLfloat r, g, b;
    color(GLint r, GLint g, GLint b){
        this->r= r/255.0; this-> g= g/ 255.0; this->b= b/255.0;
    }
};

std::map<std::string, point> pos= {
    {"bottomLeft"   , point(  0,   0)},
    {"bottomMiddle" , point( 50,   0)},
    {"bottomRight"  , point(100,   0)},

    {"middleLeft"   , point( 50,  0)},
    {"middleMost"   , point( 50,  50)},
    {"middleRight"  , point(100,  50)},

    {"topLeft"      , point(  0, 100)},
    {"topMiddle"    , point( 50, 100)},
    {"topRight"     , point(100, 100)},
};
std::map<std::string, color> colorMap= {
    {"Grid", color(  0, 255, 0)},
    {"X", color(255, 128,   0)},
    {"O", color(  0, 128, 255)},
};

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
    
    // init();
    glClearColor(0.0, 0.2, 0.2, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);

    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return 0;
}
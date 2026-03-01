#include <GL/glut.h>
#include <map>
#include <string>
#include <math.h>
#include <cmath>

#define PI 3.14
#define circleRes 360 // resolution of leaf circle
#define iterationCount 6 // 

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
std::map<std::string, color> colorMap={
    {"Black",  color(  0,   0,   0)},
    {"White",  color(255, 255, 255)},
    {"Green",  color(  0, 255,   0)}, 
    {"Brown",  color(150, 140,  80)},
    {"Purple", color(128,   0, 128)},
};

void drawLeaf(point origin, color leafC= colorMap.at("Green")){
    glColor3f(leafC.r, leafC.g, leafC.b);

    glVertex2f(origin.x     , origin.y);
    glVertex2f(origin.x+   5, origin.y);
    
    glVertex2f(origin.x+   5, origin.y);
    glVertex2f(origin.x+  10, origin.y+  5);

    glVertex2f(origin.x+  10, origin.y+  5);
    glVertex2f(origin.x+   5, origin.y+  5);

    glVertex2f(origin.x+   5, origin.y+  5);
    glVertex2f(origin.x     , origin.y);
    
    glVertex2f(origin.x+   2, origin.y+  1);
    glVertex2f(origin.x+   8, origin.y+  4);

}

void drawLimit(point origin, GLfloat height, GLfloat width){
    color c= colorMap.at("Purple");
    glColor3f(c.r, c.g, c.b);

    glVertex2f(origin.x, origin.y);
    glVertex2f(origin.x, origin.y+ 10);
    glVertex2f(origin.x, origin.y);
    glVertex2f(origin.x+ 10, origin.y);

    
    glVertex2f(origin.x+ width, origin.y+ height);
    glVertex2f(origin.x+ width, origin.y+ height- 10);
    glVertex2f(origin.x+ width, origin.y+ height);
    glVertex2f(origin.x+ width- 10, origin.y+ height);

    
    glVertex2f(origin.x, origin.y+ height);
    glVertex2f(origin.x+ 10, origin.y+ height);
    glVertex2f(origin.x, origin.y+ height);
    glVertex2f(origin.x, origin.y+ height- 10);

    glVertex2f(origin.x+ width, origin.y);
    glVertex2f(origin.x+ width, origin.y+ 10);
    glVertex2f(origin.x+ width, origin.y);
    glVertex2f(origin.x+ width- 10, origin.y);
}

void drawTree(point origin, GLfloat height, GLfloat width, color leafC= colorMap.at("Green"), color trunkC= colorMap.at("Brown")){
    drawLimit(origin, height, width);
    //Trunk
    glColor3f(trunkC.r, trunkC.g, trunkC.b);

    glVertex2f(origin.x+ width* 0.345, origin.y);
    glVertex2f(origin.x+ width* 0.65, origin.y);

    glVertex2f(origin.x+ width* 0.345, origin.y);
    glVertex2f(origin.x+ width* 0.4, origin.y+ height* 0.1);

    glVertex2f(origin.x+ width* 0.4, origin.y+ height* 0.1);
    glVertex2f(origin.x+ width* 0.4, origin.y+ height* 0.8);

    glVertex2f(origin.x+ width* 0.65, origin.y);
    glVertex2f(origin.x+ width* 0.6, origin.y+ height* 0.1);

    glVertex2f(origin.x+ width* 0.6, origin.y+ height* 0.1);
    glVertex2f(origin.x+ width* 0.6, origin.y+ height* 0.8);

    //Leaves
    for (int i= 0; i< circleRes; i++){
        int angle= i* (iterationCount* PI/ circleRes);

        GLfloat orgX= origin.x+ width* 0.5;
        GLfloat orgY= origin.y+ height* 0.7;

        GLfloat x= orgX+ (width* 0.4)* std::cos(angle);
        GLfloat y= orgY+ (height* 0.25)* std::sin(angle);
        
        glVertex2f(orgX, orgY);
        glVertex2f(x, y);
        drawLeaf({x, y}, leafC);
    }
}

void drawForest(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    drawTree({ 10,  10}, 150, 100);
    
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
    glClearColor(0.2, 0.2, 0.2, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);

    glutDisplayFunc(drawForest);
    glutMainLoop();

    return 0;
}
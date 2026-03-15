#include <GL/glut.h>
#include <map>
#include <string>
#include <cmath>

#define EXP 2.18
#define PI 3.14
#define MAX_X 4
#define SCREEN_LENGTH 200

struct point{
    GLfloat x, y;
    point(GLfloat x, GLfloat y){
        this->x= x; this-> y= y;
    }
};
struct coord{
    GLfloat x, y, z;
    coord(GLfloat x, GLfloat y, GLfloat z){
        this->x= x; this-> y= y; this->z= z;
    }
};
struct color{
    GLfloat r, g, b;
    color(GLint r, GLint g, GLint b){
        this->r= r/255.0; this-> g= g/ 255.0; this->b= b/255.0;
    }
};
std::map<std::string, color> colorMap={
    {"Black",   color(  0,   0,   0)},
    {"White",   color(255, 255, 255)},
    {"Red",     color(255,   0,   0)}, 
    {"Green",   color(  0, 255,   0)}, 
    {"Blue",    color(  0,   0, 255)}, 
};

GLfloat plot(GLfloat x){
    return (std::pow(EXP, -x)* std::cos(2* PI* x));
}
point translateToScreen(GLfloat x){
    return {(GLfloat) x* (GLfloat) SCREEN_LENGTH/ 4.0, (GLfloat) ((GLfloat) plot(x)+ 1.0)* (GLfloat) SCREEN_LENGTH/ 2.0};
}

void drawPlot(GLfloat x, color c= colorMap.at("White")){
    glColor3f(c.r, c.g, c.b);

    point p= translateToScreen(x);

    glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
    glEnd();
}

void drawFigure(GLfloat x, color c= colorMap.at("White")){
    glColor3f(c.r, c.g, c.b);

    glBegin(GL_LINES);
        glVertex2f(x, SCREEN_LENGTH/ 2.0);
        glVertex2f(x+ SCREEN_LENGTH, SCREEN_LENGTH/ 2.0);

        glVertex2f(x+ 0.005, 0);
        glVertex2f(x+ 0.005, SCREEN_LENGTH);
    glEnd();
}

void drawCurve(){
    float i= 0.0;
    drawFigure(i);
    for (; i<= MAX_X; i+= 0.005){
        drawPlot(i);
    }
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutInitWindowPosition(200, 50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("GL Cube");

    // init();
    glClearColor(0.2, 0.2, 0.2, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, SCREEN_LENGTH, 0.0, SCREEN_LENGTH);

    
    
    glutDisplayFunc(drawCurve);
    glutMainLoop();

    return 0;
}
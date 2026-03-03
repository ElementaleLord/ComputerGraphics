#include <GL/glut.h>
#include <cmath>
#include <map>
#include <string>

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
#define PI 3.14159265

void savePolygon(GLuint regHex, point origin, GLfloat radius, GLint segments, color c= colorMap.at("White")){
    glColor3f(c.r, c.g, c.b);
    GLuint x, y, k; GLdouble theta;

    glNewList(regHex, GL_COMPILE);

    glBegin(GL_POLYGON);
    for (k= 0; k< segments; k++){
        theta= (PI* 2.0)* ((GLfloat)k/ (GLfloat)segments);
        x= origin.x+ (radius* std::cos(theta));
        y= origin.y+ (radius* std::sin(theta));
        glVertex2i (x, y);
    }
    glEnd();

    glEndList();
}
void drawShape(){
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint regHex= glGenLists(1),regTrig= glGenLists(1), regRec= glGenLists(1), regDec= glGenLists(1);
    savePolygon(regHex,{250, 250}, 150, 6);

    glCallList (regHex);

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
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(drawShape);
    glutMainLoop();

    return 0;
}
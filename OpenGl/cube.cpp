#include <GL/glut.h>
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
void drawCube(coord origin, color c= colorMap.at("White")){
    glColor3f(c.r, c.g, c.b);

    GLfloat pt[][3]= {
        {0, 0, 0}, // 0
        {1, 0, 0}, // 1
        {1, 0, 1}, // 2
        {0, 0, 1}, // 3
        {0, 1, 1}, // 4
        {0, 1, 0}, // 5
        {1, 1, 0}, // 6
        {1, 1, 1}, // 7
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pt);
    GLubyte vertIndex[]= {0, 1, 2, 3, //bottom
        3, 4, 5, 0, // z side back
        0, 5, 6, 1, // x side back
        1, 6, 7, 2, // z side front
        2, 1, 6, 7, // x side front
        7, 6, 5, 4, // top
    };
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);
}

void drawShape(){
    
    glBegin(GL_LINES);

    drawCube({10, 10, 10});

    glEnd();
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
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);

    glutDisplayFunc(drawShape);
    glutMainLoop();

    return 0;
}
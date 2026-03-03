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
void drawCube(coord origin, coord hwd, color c= colorMap.at("White")){
    glColor3f(c.r, c.g, c.b);
    GLfloat points [8][3] = { 
        {origin.x+ 0* hwd.x, origin.y+ 0* hwd.y, origin.z+ 0* hwd.z},
        {origin.x+ 0* hwd.x, origin.y+ 1* hwd.y, origin.z+ 0* hwd.z},
        {origin.x+ 1* hwd.x, origin.y+ 0* hwd.y, origin.z+ 0* hwd.z},
        {origin.x+ 1* hwd.x, origin.y+ 1* hwd.y, origin.z+ 0* hwd.z},
        {origin.x+ 0* hwd.x, origin.y+ 0* hwd.y, origin.z+ 1* hwd.z},
        {origin.x+ 0* hwd.x, origin.y+ 1* hwd.y, origin.z+ 1* hwd.z},
        {origin.x+ 1* hwd.x, origin.y+ 0* hwd.y, origin.z+ 1* hwd.z},
        {origin.x+ 1* hwd.x, origin.y+ 1* hwd.y, origin.z+ 1* hwd.z}
    };
    GLubyte vertIndex[]= {
        6, 2, 3, 7, 
        5, 1, 0, 4,
        7, 3, 1, 5,
        4, 0, 2, 6,
        2, 0, 1, 3,
        7, 5, 4, 6
    };
    // step 1
    glEnableClientState(GL_VERTEX_ARRAY);
    // step 2
    glVertexPointer(3, GL_FLOAT, 0, points);
    // step 3
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, vertIndex);
}

void drawShape(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    
    drawCube({0, 0, 0}, {5, 5, 5});
    
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutInitWindowPosition(200, 50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("GL Cube");

    // init();
    glClearColor(0.2, 0.2, 0.2, 0.5);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

    glutDisplayFunc(drawShape);
    glutMainLoop();

    return 0;
}
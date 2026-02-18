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
std::map<std::string, color> colorMap= {
    {"White"    , color(255, 255, 255)},
    {"Purple"   , color(255,   0, 255)},
    {"Red"      , color(255,   0,   0)},
    {"Yellow"   , color(255, 255,   0)},
    {"Green"    , color(  0, 255,   0)},
    {"Cyan"     , color(  0, 255, 255)},
    {"Blue"     , color(  0,  0, 255)},
};

void drawHouse(point peak, GLfloat width, GLfloat height, color c){
    // house color
    glColor3f(c.r, c.g, c.b);
    
    //~ house base
    // bottom line of house square
    glVertex2f(peak.x, peak.y);
    glVertex2f(peak.x+ width, peak.y);
    // right line of house square
    glVertex2f(peak.x+ width, peak.y);
    glVertex2f(peak.x+ width, peak.y+ height);
    // left line of house square
    glVertex2f(peak.x, peak.y+ height);
    glVertex2f(peak.x, peak.y);

    //~ roof
    // top line of house square / bottom line of roof triangle
    glVertex2f(peak.x+ width, peak.y+ height);
    glVertex2f(peak.x, peak.y+ height);
    // left side of roof triangle
    glVertex2f(peak.x, peak.y+ height);
    glVertex2d(peak.x+ width* 0.5, peak.y+ height* 1.7);
    // right side of roof triangle
    glVertex2f(peak.x+ width,   peak.y+ height);
    glVertex2d(peak.x+ width* 0.5, peak.y+ height* 1.7);

    //~door
    // left side of door
    glVertex2f(peak.x+ width*0.2, peak.y);
    glVertex2f(peak.x+ width*0.2, peak.y+ height* 0.5);
    // right side of door
    glVertex2f(peak.x+ width*0.4, peak.y);
    glVertex2f(peak.x+ width*0.4, peak.y+ height* 0.5);
    // top of door
    glVertex2f(peak.x+ width*0.2, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.4, peak.y+ height* 0.5);

    //~ window
    // bottom side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.25);
    // left side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.5);
    // right side of window
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.25);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.5);
    // top side of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.5);
    // horizontal bar of window
    glVertex2f(peak.x+ width*0.6, peak.y+ height* 0.375);
    glVertex2f(peak.x+ width*0.8, peak.y+ height* 0.375);
    // vertical bar of window
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 0.5);
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 0.25);

    //~ Chimney
    // left side  of chimney
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 1.42);
    glVertex2f(peak.x+ width*0.7, peak.y+ height* 1.6);
    // right side of chimney
    glVertex2f(peak.x+ width*0.9, peak.y+ height* 1.14);
    glVertex2f(peak.x+ width*0.9, peak.y+ height* 1.6);
    // top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.6);
    // left side of top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.65);
    // right side of top of chimney
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.6);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.65);
    // true top of chimney
    glVertex2f(peak.x+ width*0.65, peak.y+ height* 1.65);
    glVertex2f(peak.x+ width*0.95, peak.y+ height* 1.65);
}

void drawVillage(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    drawHouse({ 70, 210},    5,   5, colorMap.at("White"));    // very far white house
    drawHouse({170, 210},   10,  10, colorMap.at("Purple"));   // far-far purple house
    drawHouse({ 20, 170},   20,  20, colorMap.at("Red"));      // far red house
    drawHouse({110, 150},   40,  40, colorMap.at("Yellow"));   // far-middle yellow house
    drawHouse({230, 100},   60,  60, colorMap.at("Green"));    // middle green house
    drawHouse({140,  50},   80,  80, colorMap.at("Cyan"));     // close-middle cyan house
    drawHouse({ 10,  10},  100, 100, colorMap.at("Blue"));     // close blue house

    glEnd();
    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutInitWindowPosition(200, 50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("GL Village");

    // init();
    glClearColor(0.2, 0.2, 0.2, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);

    glutDisplayFunc(drawVillage);
    glutMainLoop();

    return 0;
}
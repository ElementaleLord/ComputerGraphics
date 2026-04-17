#include <GL/glut.h>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>

// ─── display ────────────────────────────────────────────────────────────────
#define SCREEN_WIDTH                800
#define SCREEN_HEIGHT               600
#define SCREEN_X_OFFSET             300
#define SCREEN_Y_OFFSET             100
#define VIEWPORT_X                  0
#define VIEWPORT_Y                  0
#define FOV                         60
#define Z_NEAR                      0.1f
#define Z_FAR                       5000.0f

// ─── camera ─────────────────────────────────────────────────────────────────
#define VERTICAL_ROTATION_POS_LIMIT  89.0f
#define VERTICAL_ROTATION_NEG_LIMIT -89.0f
#define MOVE_SPEED                   2.0f
#define ZOOM_SPEED                   2.0f
#define MOUSE_SENS                   0.15f
#define CAM_START_X                  0.0f
#define CAM_START_Y                  300.0f
#define CAM_START_Z                  500.0f
#define CAM_LOOK_START_X             0.0f
#define CAM_LOOK_START_Y            -0.5f
#define CAM_LOOK_START_Z            -1.0f
#define CAM_HORIZ_ROT_START         -90.0f
#define CAM_VERT_ROT_START          -20.0f

// ─── math ────────────────────────────────────────────────────────────────────
#define PI                          3.14159265358979323846f
#define DEG_TO_RAD                  (PI / 180.0f)

// ─── simulation ──────────────────────────────────────────────────────────────
// Earth completes one orbit in EARTH_ORBIT_PERIOD_SECS real seconds
#define EARTH_ORBIT_PERIOD_SECS     5.0f
// Earth completes EARTH_DAYS_PER_YEAR spins per orbit
#define EARTH_DAYS_PER_YEAR         365.0f
// derived: degrees/sec for Earth's orbit and spin
#define EARTH_ORBIT_DEG_PER_SEC     (360.0f / EARTH_ORBIT_PERIOD_SECS)
#define EARTH_SPIN_DEG_PER_SEC      (EARTH_DAYS_PER_YEAR * 360.0f / EARTH_ORBIT_PERIOD_SECS)

// ─── scene scale ─────────────────────────────────────────────────────────────
#define SUN_SCALE                   4.0f
#define PLANET_SCALE                8.0f
#define ORBIT_SCALE                 10.0f

// ─── stars ───────────────────────────────────────────────────────────────────
#define NUM_STARS                   2000
#define STAR_SPHERE_RADIUS_MIN      800.0f
#define STAR_SPHERE_RADIUS_RANGE    400.0f
#define STAR_POINT_SIZE             1.5f
#define STAR_BRIGHTNESS_BASE        0.6f
#define STAR_BRIGHTNESS_RANGE       0.4f
#define STAR_BRIGHTNESS_STEPS       7

// ─── orbit rings ─────────────────────────────────────────────────────────────
#define ORBIT_RING_SEGMENTS         128
#define ORBIT_RING_ALPHA            0.08f

// ─── sphere tessellation ─────────────────────────────────────────────────────
#define SPHERE_SLICES               32
#define SPHERE_STACKS               16

// ─────────────────────────────────────────────────────────────────────────────

struct coord
{
    GLfloat x, y, z;
    coord(GLfloat x, GLfloat y, GLfloat z){
        this->x= x; this->y= y; this->z= z;
    }
};

struct color
{
    GLfloat r, g, b;
    color(GLint r, GLint g, GLint b){
        this->r= r/255.0; this->g= g/255.0; this->b= b/255.0;
    }
};

// planet data: all fixed astronomical values in one place
struct Planet
{
    const char* colorKey;
    float       orbitRadiusAU;  // from the comment table, in our AU units
    float       bodyRadius;     // from the comment table, in our AU units
    float       orbitalPeriod;  // Earth years
    float       siderealDay;    // Earth days (negative = retrograde)
    // runtime state
    float       orbitAngle;
    float       spinAngle;
};

// ─── planet table ────────────────────────────────────────────────────────────
//     color        orbitAU   bodyRad     period     day   orbitAngle  spinAngle
Planet planets[] = {
    { "mercury",    2.572f,     0.02167f,  0.24f,    58.650f,  0.0f,    0.0f },
    { "venus",      4.806f,     0.05374f,  0.61f,  -243.020f,  0.0f,    0.0f },
    { "earth",      6.644f,     0.05658f,  1.00f,     1.000f,  0.0f,    0.0f },
    { "mars",      10.120f,     0.03011f,  1.87f,     1.025f,  0.0f,    0.0f },
    { "jupiter",   34.580f,     0.62090f, 11.86f,     0.413f,  0.0f,    0.0f },
    { "saturn",    63.650f,     0.51740f, 29.46f,     0.444f,  0.0f,    0.0f },
    { "uranus",   127.800f,     0.22530f, 84.13f,    -0.718f,  0.0f,    0.0f },
    { "neptune",  200.000f,     0.21870f,164.84f,     0.671f,  0.0f,    0.0f },
};
const int NUM_PLANETS = sizeof(planets) / sizeof(planets[0]);

// ─────────────────────────────────────────────────────────────────────────────

const std::map<int, std::string> mouseKeys= {
    {0, "leftClick"     },
    {1, "middleClick"   },
    {2, "rightClick"    },
    {3, "scrollUp"      },
    {4, "scrollDown"    },
};
const std::map<int, std::string> modKeys= {
    {0, "none"              },
    {1, "shift"             },
    {2, "ctrl"              },
    {3, "shift+ ctrl"       },
    {4, "alt"               },
    {5, "alt+ shift"        },
    {6, "alt+ ctrl"         },
    {7, "alt+ ctrl+ shift"  },
};

const std::map<std::string, color> colors= {
    {"black",   {  0,   0,   0}},
    {"white",   {255, 255, 255}},
    {"red",     {255,   0,   0}},
    {"green",   {  0, 255,   0}},
    {"blue",    {  0,   0, 255}},
    {"yellow",  {255, 255,   0}},
    {"cyan",    {  0, 255, 255}},
    {"magenta", {255,   0, 255}},
    {"orange",  {255, 128,   0}},
    {"lime",    {128, 255,   0}},
    {"purple",  {128,   0, 255}},

    {"sun",     {241,  93,  34}},
    {"mercury", {191, 189, 188}},
    {"venus",   {218, 178, 146}},
    {"earth",   { 31,  56, 111}},
    {"mars",    {242, 124,  95}},
    {"jupiter", {191, 176, 156}},
    {"saturn",  {218, 183, 120}},
    {"uranus",  {207, 236, 240}},
    {"neptune", {120, 158, 191}},
    {"star",    {200, 200, 210}},
};

// ─── globals ─────────────────────────────────────────────────────────────────
coord camPos    = { CAM_START_X,      CAM_START_Y,      CAM_START_Z      };
coord camLook   = { CAM_LOOK_START_X, CAM_LOOK_START_Y, CAM_LOOK_START_Z };
coord camUp     = { 0.0f, 1.0f, 0.0f };

float horizentalRotation    = CAM_HORIZ_ROT_START;
float verticalRotation      = CAM_VERT_ROT_START;
bool  firstMouse            = true;
bool  inMouseMode           = false;
int   lastMouseX            = SCREEN_WIDTH  / 2;
int   lastMouseY            = SCREEN_HEIGHT / 2;
int   windowCenterX         = SCREEN_WIDTH  / 2;
int   windowCenterY         = SCREEN_HEIGHT / 2;

struct Star { GLfloat x, y, z; };
Star stars[NUM_STARS];

// ─────────────────────────────────────────────────────────────────────────────

void generateStars()
{
    srand(42);
    for (int i = 0; i < NUM_STARS; i++){
        float theta     = ((float)rand() / RAND_MAX) * 2.0f * PI;
        float phi       = acosf(1.0f - 2.0f * ((float)rand() / RAND_MAX));
        float r         = STAR_SPHERE_RADIUS_MIN + ((float)rand() / RAND_MAX) * STAR_SPHERE_RADIUS_RANGE;
        stars[i].x      = r * sinf(phi) * cosf(theta);
        stars[i].y      = r * cosf(phi);
        stars[i].z      = r * sinf(phi) * sinf(theta);
    }
}

void drawStars()
{
    color sc = colors.at("star");
    glPointSize(STAR_POINT_SIZE);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_STARS; i++){
        float b = STAR_BRIGHTNESS_BASE + STAR_BRIGHTNESS_RANGE * ((float)(i % STAR_BRIGHTNESS_STEPS) / (STAR_BRIGHTNESS_STEPS - 1));
        glColor3f(sc.r * b, sc.g * b, sc.b * b);
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }
    glEnd();
}

void drawOrbitRing(GLfloat radius)
{
    glColor4f(1.0f, 1.0f, 1.0f, ORBIT_RING_ALPHA);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ORBIT_RING_SEGMENTS; i++){
        float angle = (float)i / ORBIT_RING_SEGMENTS * 2.0f * PI;
        glVertex3f(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
    }
    glEnd();
}

void init()
{
    glClearColor(0.01f, 0.01f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (GLdouble)SCREEN_WIDTH / (GLdouble)SCREEN_HEIGHT, Z_NEAR, Z_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    generateStars();
}

coord crossProduct(const coord &a, const coord &b)
{
    return coord(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

void wrap(float &a)
{ 
    if (a >  360.0f) a -= 360.0f; 
    if (a < -360.0f) a += 360.0f; 
};

void updateCamLook()
{
    float horizentalRotationRad = horizentalRotation * DEG_TO_RAD;
    float verticalRotationRad   = verticalRotation   * DEG_TO_RAD;
    camLook.x = std::cos(verticalRotationRad) * std::cos(horizentalRotationRad);
    camLook.y = std::sin(verticalRotationRad);
    camLook.z = std::cos(verticalRotationRad) * std::sin(horizentalRotationRad);
}

void handlePassiveMotion(int x, int y)
{
    if (inMouseMode){
        if (firstMouse) {
            lastMouseX  = windowCenterX;
            lastMouseY  = windowCenterY;
            firstMouse  = false;
            glutWarpPointer(windowCenterX, windowCenterY);
            return;
        }
        horizentalRotation += (x - lastMouseX) * MOUSE_SENS;
        verticalRotation   += (lastMouseY - y)  * MOUSE_SENS;
        if (verticalRotation >  VERTICAL_ROTATION_POS_LIMIT) verticalRotation =  VERTICAL_ROTATION_POS_LIMIT;
        if (verticalRotation <  VERTICAL_ROTATION_NEG_LIMIT) verticalRotation =  VERTICAL_ROTATION_NEG_LIMIT;
        updateCamLook();
        glutWarpPointer(windowCenterX, windowCenterY);
        lastMouseX = windowCenterX;
        lastMouseY = windowCenterY;
        glutPostRedisplay();
    }
}

void handleSpecialKeys(int key, int x, int y)
{
    coord vertMove = crossProduct(camLook, camUp);
    switch(key)
    {
        case GLUT_KEY_UP:
            if (inMouseMode)
            { 
                camPos.x += camLook.x * MOVE_SPEED; 
                camPos.y += camLook.y * MOVE_SPEED; 
                camPos.z += camLook.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.y += MOVE_SPEED; 
            }
            break;
        case GLUT_KEY_DOWN:
            if (inMouseMode)
            { 
                camPos.x -= camLook.x * MOVE_SPEED; 
                camPos.y -= camLook.y * MOVE_SPEED; 
                camPos.z -= camLook.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.y -= MOVE_SPEED; 
            }
            break;
        case GLUT_KEY_RIGHT:
            if (inMouseMode)
            { 
                camPos.x += vertMove.x * MOVE_SPEED; 
                camPos.y += vertMove.y * MOVE_SPEED; 
                camPos.z += vertMove.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.x += MOVE_SPEED; 
            }
            break;
        case GLUT_KEY_LEFT:
            if (inMouseMode)
            { 
                camPos.x -= vertMove.x * MOVE_SPEED; 
                camPos.y -= vertMove.y * MOVE_SPEED; 
                camPos.z -= vertMove.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.x -= MOVE_SPEED; 
            }
            break;
    }
    glutPostRedisplay();
}

void handleKeys(unsigned char key, int x, int y)
{
    coord vertMove = crossProduct(camLook, camUp);
    switch(key)
    {
        case 'r': case 'R':
            inMouseMode = !inMouseMode;
            if (inMouseMode)
            { 
                glutSetCursor(GLUT_CURSOR_NONE); 
                firstMouse = true; 
            }
            else 
            { 
                glutSetCursor(GLUT_CURSOR_LEFT_ARROW); 
            }
            break;
        case 'w': case 'W':
            if (inMouseMode)
            { 
                camPos.x += camLook.x * MOVE_SPEED; 
                camPos.y += camLook.y * MOVE_SPEED; 
                camPos.z += camLook.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.y += MOVE_SPEED; 
            }
            break;
        case 's': case 'S':
            if (inMouseMode)
            { 
                camPos.x -= camLook.x * MOVE_SPEED; 
                camPos.y -= camLook.y * MOVE_SPEED; 
                camPos.z -= camLook.z * MOVE_SPEED; 
            }
            else { camPos.y -= MOVE_SPEED; }
            break;
        case 'd': case 'D':
            if (inMouseMode)
            { 
                camPos.x += vertMove.x * MOVE_SPEED; 
                camPos.y += vertMove.y * MOVE_SPEED; 
                camPos.z += vertMove.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.x += MOVE_SPEED; 
            }
            break;
        case 'a': case 'A':
            if (inMouseMode)
            { 
                camPos.x -= vertMove.x * MOVE_SPEED; 
                camPos.y -= vertMove.y * MOVE_SPEED; 
                camPos.z -= vertMove.z * MOVE_SPEED; 
            }
            else 
            { 
                camPos.x -= MOVE_SPEED; 
            }
            break;
    }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y)
{
    if (button == 3)
    { 
        camPos.x += camLook.x * ZOOM_SPEED; 
        camPos.y += camLook.y * ZOOM_SPEED; 
        camPos.z += camLook.z * ZOOM_SPEED; 
    }
    else if (button == 4)
    { 
        camPos.x -= camLook.x * ZOOM_SPEED;
        camPos.y -= camLook.y * ZOOM_SPEED; 
        camPos.z -= camLook.z * ZOOM_SPEED; 
    }
    glutPostRedisplay();
}

void handleReshape(int width, int height)
{
    if (height == 0) height = 1;
    glViewport(VIEWPORT_X, VIEWPORT_Y, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (GLdouble)width / (GLdouble)height, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleIdle()
{
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    int   currentTime   = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime     = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        planets[i].orbitAngle += (EARTH_ORBIT_DEG_PER_SEC / planets[i].orbitalPeriod) * deltaTime;
        planets[i].spinAngle  += (EARTH_SPIN_DEG_PER_SEC  / planets[i].siderealDay)   * deltaTime;
        wrap(planets[i].orbitAngle);
        wrap(planets[i].spinAngle);
    }

    glutPostRedisplay();
}

void makeSphere(GLfloat orbitRadius, GLfloat orbitAngle, GLfloat spinAngle, GLfloat radius, color c)
{
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
        glRotatef(orbitAngle, 0, 1, 0);
        glTranslatef(orbitRadius, 0, 0);
        glRotatef(spinAngle, 0, 1, 0);
        glutWireSphere(radius, SPHERE_SLICES, SPHERE_STACKS);
    glPopMatrix();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camPos.x, camPos.y, camPos.z,
              camPos.x + camLook.x, camPos.y + camLook.y, camPos.z + camLook.z,
              camUp.x, camUp.y, camUp.z);

    drawStars();

    for (int i = 0; i < NUM_PLANETS; i++)
        drawOrbitRing(planets[i].orbitRadiusAU * ORBIT_SCALE);

    // sun has no orbit or spin state so it is drawn directly
    makeSphere(0, 0, 0, 6.183f * SUN_SCALE, colors.at("sun"));

    for (int i = 0; i < NUM_PLANETS; i++)
    {
        makeSphere(
            planets[i].orbitRadiusAU * ORBIT_SCALE,
            planets[i].orbitAngle,
            planets[i].spinAngle,
            planets[i].bodyRadius    * PLANET_SCALE,
            colors.at(planets[i].colorKey)
        );
    }

    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(SCREEN_X_OFFSET, SCREEN_Y_OFFSET);
    glutCreateWindow("Solar System");

    init();

    glutDisplayFunc(draw);
    glutKeyboardFunc(handleKeys);
    glutSpecialFunc(handleSpecialKeys);
    glutMouseFunc(handleMouse);
    glutReshapeFunc(handleReshape);
    glutPassiveMotionFunc(handlePassiveMotion);
    glutIdleFunc(handleIdle);

    glutMainLoop();
}
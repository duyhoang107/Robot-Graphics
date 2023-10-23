#include <GL/freeglut.h>
#include <math.h>

GLfloat camera_x = 10.0;
GLfloat camera_y = 5.0;
GLfloat camera_z = 15.0;

GLfloat light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
GLfloat light0_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

GLfloat mat_red_diffuse[] = { 0.7, 0.0, 0.0, 1.0 };
GLfloat mat_green_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat mat_blue_diffuse[] = { 0.2, 0.3, 1.0, 1.0 };
GLfloat mat_blue2_diffuse[] = { 0.0, 0.17, 0.5, 1.0 };
GLfloat mat_yellow_diffuse[] = { 1.0, 0.9, 0.0, 1.0 };
GLfloat mat_beige_diffuse[] = { 1.0, 1.0, 0.6, 1.0 };
GLfloat mat_brown_diffuse[] = { 0.5, 0.3, 0.0, 1.0 };

GLfloat rad_hat = 1.2;
GLfloat rad_head = 0.7;
GLfloat rad_shoulder = 0.45;
GLfloat rad_elbow = 0.3;
GLfloat rad_arm = 0.35;
GLfloat rad_hand = 0.3;
GLfloat rad_femoral = 0.45;
GLfloat rad_knee = 0.35;
GLfloat rad_leg = 0.35;
GLfloat rad_foot = 0.5;

GLfloat len_hat = 1.0;
GLfloat len_upper_body = 2.0;
GLfloat len_lower_body = 2.0;
GLfloat len_shoulder = 1.4;
GLfloat len_arm = 1.6;
GLfloat len_femoral = 1.8;
GLfloat len_leg = 2.3;

GLfloat ang_head = 0.0;
GLfloat ang_shoulders = 0.0;
GLfloat ang_left_shoulder = 0.0;
GLfloat ang_right_shoulder = 0.0;
GLfloat ang_left_arm = 0.0;
GLfloat ang_right_arm = 0.0;
GLfloat ang_left_femoral = 0.0;
GLfloat ang_right_femoral = 0.0;
GLfloat ang_left_leg = 0.0;
GLfloat ang_right_leg = 0.0;

bool nod = false;
bool shake = false;
bool tilt = false;
bool walk = false;
bool jump = false;
bool clap = false;

float delta_head = 0.05;
float delta_left_shoulder = 0.15;
float delta_right_shoulder = 0.15;
float delta_left_arm = 0.1;
float delta_right_arm = 0.1;
float delta_left_femoral = 0.15;
float delta_right_femoral = 0.15;
float delta_left_leg = 0.1;
float delta_right_leg = 0.1;

// Axes
void axes()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Tree
void tree()
{
    // Body Tree 1
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_brown_diffuse);
    glTranslatef(15.0, 3.0, -15.0);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();
    // Leaves Tree 1
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glTranslatef(15.0, 17.0, -15.0);
    glScalef(5.0, 5.0, 5.0);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();
    // Body Tree 2
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_brown_diffuse);
    glTranslatef(-15.0, 3.0, -15.0);
    glScalef(1.0, 10.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();
    // Leaves Tree 2
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glTranslatef(-15.0, 17.0, -15.0);
    glScalef(5.0, 5.0, 5.0);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();
}

// Robot
void head()
{
    // The hat
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_red_diffuse);
    glTranslatef(0.0, 5.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    if (nod) glRotatef(ang_head, 1.0, 0.0, 0.0);
    else if (shake) glRotatef(ang_head, 0.0, 1.0, 0.0);
    glutSolidCone(rad_hat, len_hat, 30, 30);
    glPopMatrix();
    // The head
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 4.6, 0.0);
    if (nod) glRotatef(ang_head, 1.0, 0.0, 0.0);
    else if (shake) glRotatef(-ang_head, 0.0, 0.0, 1.0);
    else if (tilt) glRotatef(ang_head, 0.0, 1.0, 0.0);
    glutSolidSphere(rad_head, 30, 30);
    // The left eye
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    glTranslatef(-rad_head / 2 - 0.01, 0, rad_head / 2 + 0.25);
    glRotatef(-25, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 0.1);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
    // The right eye
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    glTranslatef(rad_head / 2 + 0.01, 0, rad_head / 2 + 0.25);
    glRotatef(25, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 0.1);
    glutSolidSphere(0.2, 30, 30);
    glPopMatrix();
    // The nose
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_red_diffuse);
    glTranslatef(0.0, -rad_head / 2 + 0.1, rad_head / 2 + 0.3);
    glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
    glPopMatrix();
}

void body()
{
    // The upper body
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_yellow_diffuse);
    glTranslatef(0.0, 2.5, 0.0);
    glScalef(1.1, 1.5, 0.7);
    glutSolidCube(len_upper_body);
    glPopMatrix();

    // The lower body
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(1.0, 0.5, 0.7);
    glutSolidCube(len_lower_body);
    glPopMatrix();
}

void left_arm()
{
    // The left shoulder
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_yellow_diffuse);
    glTranslatef(-1.5, 4.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    if (walk) glRotatef(ang_left_shoulder, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_left_shoulder, 0.0, 1.0, 0.0);
    else if (clap) glRotatef(-60, 1.0, 0.0, 0.0);
    glutSolidCylinder(rad_shoulder, len_shoulder, 30, 30);
    // The left elbow
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_shoulder + (rad_elbow / 2) + 0.1);
    glutSolidSphere(rad_elbow, 30, 30);
    // The left arm
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, (rad_elbow / 2) + 0.1);
    if (walk) glRotatef(ang_left_arm, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_left_arm, 0.0, 1.0, 0.0);
    else if (clap)
    {
        glRotatef(-45, 1.0, 0.0, 0.0);
        glRotatef(ang_left_arm, 0.0, -1.0, 0.0);
    }
    glutSolidCylinder(rad_arm, len_arm, 30, 30);
    // The left hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_arm + (rad_hand / 2) + 0.1);
    glutSolidSphere(rad_hand, 30, 30);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void right_arm()
{
    // The right shoulder
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_yellow_diffuse);
    glTranslatef(1.5, 4.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    if (walk) glRotatef(ang_right_shoulder, 1.0, 0.0, 0.0);
    else if (jump)glRotatef(ang_right_shoulder, 0.0, 1.0, 0.0);
    else if (clap) glRotatef(-60, 1.0, 0.0, 0.0);
    glutSolidCylinder(rad_shoulder, len_shoulder, 30, 30);
    // The right elbow
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_shoulder + (rad_elbow / 2) + 0.1);
    glutSolidSphere(rad_elbow, 30, 30);
    // The right arm
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, (rad_elbow / 2) + 0.1);
    if (walk) glRotatef(ang_right_arm, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_right_arm, 0.0, 1.0, 0.0);
    else if (clap)
    {
        glRotatef(-45, 1.0, 0.0, 0.0);
        glRotatef(ang_right_arm, 0.0, 1.0, 0.0);
    }
    glutSolidCylinder(rad_arm, len_arm, 30, 30);
    // The right hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_arm + (rad_hand / 2) + 0.1);
    glutSolidSphere(rad_hand, 30, 30);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void left_leg()
{
    // The left femoral
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    if (walk) glRotatef(ang_left_femoral, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_left_femoral, 0.0, -1.0, 0.0);

    glutSolidCylinder(rad_femoral, len_femoral, 30, 30);
    // The left knee
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_femoral + (rad_knee / 2) + 0.1);
    glutSolidSphere(rad_knee, 30, 30);
    // The left leg
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, (rad_knee / 2) + 0.1);
    if (walk) glRotatef(ang_left_leg, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_left_leg, 0.0, -1.0, 0.0);
    glutSolidCylinder(rad_leg, len_leg, 30, 30);
    // The left foot
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue2_diffuse);
    glTranslatef(0.0, 0.3, len_leg + (rad_foot / 2) - 0.1);
    glScalef(1.0, 1.5, 0.5);
    glutSolidSphere(rad_foot, 30, 30);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void right_leg()
{
    // The right femoral
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue_diffuse);
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    if (walk) glRotatef(ang_right_femoral, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_right_femoral, 0.0, -1.0, 0.0);
    glutSolidCylinder(rad_femoral, len_femoral, 30, 30);
    // The right knee
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, len_femoral + (rad_knee / 2) + 0.1);
    glutSolidSphere(rad_knee, 30, 30);
    // The right leg
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_beige_diffuse);
    glTranslatef(0.0, 0.0, (rad_knee / 2) + 0.1);
    if (walk) glRotatef(ang_right_leg, 1.0, 0.0, 0.0);
    else if (jump) glRotatef(ang_right_leg, 0.0, -1.0, 0.0);
    glutSolidCylinder(rad_leg, len_leg, 30, 30);
    // The right foot
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue2_diffuse);
    glTranslatef(0.0, 0.3, len_leg + (rad_foot / 2) - 0.1);
    glScalef(1.0, 1.5, 0.5);
    glutSolidSphere(rad_foot, 30, 30);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void robot() {
    head();
    body();
    left_arm();
    right_arm();
    left_leg();
    right_leg();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    axes();
    tree();
    robot();
    glFlush();
    glutSwapBuffers();
}

void idle() {
    if (nod) {
        ang_head += delta_head;
        if (ang_head > 5.0 || ang_head < -3.0) {
            delta_head = -delta_head;
        }
    }
    else if (shake) {
        ang_head += delta_head;
        if (ang_head > 5.0 || ang_head < -5.0) {
            delta_head = -delta_head;
        }
    }
    else if (tilt) {
        ang_head += delta_head;
        if (ang_head > 5.0 || ang_head < -5.0) {
            delta_head = -delta_head;
        }
    }
    if (walk) {
        // arm for walk
        ang_left_shoulder += delta_left_shoulder;
        if (ang_left_shoulder > 25.0 || ang_left_shoulder < -25.0) {
            delta_left_shoulder = -delta_left_shoulder;
        }
        ang_left_arm += delta_left_arm;
        if (ang_left_arm > 10.0 || ang_left_arm < -10.0) {
            delta_left_arm = -delta_left_arm;
        }
        ang_right_shoulder -= delta_right_shoulder;
        if (ang_right_shoulder > 25.0 || ang_right_shoulder < -25.0) {
            delta_right_shoulder = -delta_right_shoulder;
        }
        ang_right_arm -= delta_right_arm;
        if (ang_right_arm > 10.0 || ang_right_arm < -10.0) {
            delta_right_arm = -delta_right_arm;
        }
        // leg for walk
        ang_left_femoral -= delta_left_femoral;
        if (ang_left_femoral > 25.0 || ang_left_femoral < -25.0) {
            delta_left_femoral = -delta_left_femoral;
        }
        ang_left_leg -= delta_left_leg;
        if (ang_left_leg > 10.0 || ang_left_leg < -5.0) {
            delta_left_leg = -delta_left_leg;
        }
        ang_right_femoral += delta_right_femoral;
        if (ang_right_femoral > 25.0 || ang_right_femoral < -25.0) {
            delta_right_femoral = -delta_right_femoral;
        }
        ang_right_leg += delta_right_leg;
        if (ang_right_leg > 10.0 || ang_right_leg < -5.0) {
            delta_right_leg = -delta_right_leg;
        }
    }
    if (jump) {
        // arm for jump
        ang_left_shoulder += 3 * delta_left_shoulder;
        if (ang_left_shoulder > 0.0 || ang_left_shoulder < -160.0) {
            delta_left_shoulder = -delta_left_shoulder;
        }
        ang_left_arm += 3 * delta_left_arm;
        if (ang_left_arm > 0.0 || ang_left_arm < -5.0) {
            delta_left_arm = -delta_left_arm;
        }
        ang_right_shoulder -= 3 * delta_right_shoulder;
        if (ang_right_shoulder > 160.0 || ang_right_shoulder < 0.0) {
            delta_right_shoulder = -delta_right_shoulder;
        }
        ang_right_arm -= 3 * delta_right_arm;
        if (ang_right_arm > 5.0 || ang_right_arm < 0.0) {
            delta_right_arm = -delta_right_arm;
        }
        // leg for jump
        ang_left_femoral += delta_left_femoral;
        if (ang_left_femoral > 30.0 || ang_left_femoral < 0.0) {
            delta_left_femoral = -delta_left_femoral;
        }
        ang_left_leg += delta_left_leg;
        if (ang_left_leg > 5.0 || ang_left_leg < 0.0) {
            delta_left_leg = -delta_left_leg;
        }
        ang_right_femoral -= delta_right_femoral;
        if (ang_right_femoral > 0.0 || ang_right_femoral < -30.0) {
            delta_right_femoral = -delta_right_femoral;
        }
        ang_right_leg -= delta_right_leg;
        if (ang_right_leg > 5.0 || ang_right_leg < 0.0) {
            delta_right_leg = -delta_right_leg;
        }
    }
    if (clap)
    {
        ang_left_arm += 3 * delta_left_arm;
        if (ang_left_arm > 0.0 || ang_left_arm < -45) {
            delta_left_arm = -delta_left_arm;
        }
        ang_right_arm += 3 * delta_right_arm;
        if (ang_right_arm > 0.0 || ang_right_arm < -45) {
            delta_right_arm = -delta_right_arm;
        }
    }
    glutPostRedisplay();
}

void stop()
{
    ang_left_shoulder = 0.0;
    ang_right_shoulder = 0.0;
    ang_left_arm = 0.0;
    ang_right_arm = 0.0;
    ang_left_femoral = 0.0;
    ang_right_femoral = 0.0;
    ang_left_leg = 0.0;
    ang_right_leg = 0.0;
}

void menu(int value)
{
    switch (value)
    {
    case 1:
        shake = false;
        tilt = false;
        nod = !nod;
        break;
    case 2:
        nod = false;
        tilt = false;
        shake = !shake;
        break;
    case 3:
        nod = false;
        shake = false;
        tilt = !tilt;
        break;
    case 4:
        stop();
        jump = false;
        clap = false;
        walk = !walk;
        break;
    case 5:
        stop();
        walk = false;
        clap = false;
        jump = !jump;
        break;
    case 6:
        stop();
        walk = false;
        jump = false;
        clap = !clap;
        break;
    case 7:
        nod = false;
        shake = false;
        tilt = false;
        walk = false;
        jump = false;
        clap = false;
        ang_head = 0.0;
        stop();
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        camera_x -= 0.5;
        break;
    case GLUT_KEY_RIGHT:
        camera_x += 0.5;
        break;
    case GLUT_KEY_UP:
        camera_y += 0.5;
        break;
    case GLUT_KEY_DOWN:
        camera_y -= 0.5;
        break;
    case GLUT_KEY_PAGE_UP:
        camera_z -= 0.5;
        break;
    case GLUT_KEY_PAGE_DOWN:
        camera_z += 0.5;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1000) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - 700) / 2);
    glutCreateWindow("Computer Graphics");
    glutCreateMenu(menu);
    glutAddMenuEntry("Nod", 1);
    glutAddMenuEntry("Shake", 2);
    glutAddMenuEntry("Tilt", 3);
    glutAddMenuEntry("Walk", 4);
    glutAddMenuEntry("Jump", 5);
    glutAddMenuEntry("Clap", 6);
    glutAddMenuEntry("Stop", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    glutIdleFunc(idle);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
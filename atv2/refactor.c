#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Face and feature constants
enum {
    NUM_FACE_CONTOURS = 6,
    NUM_HAIR_STYLES = 6,
    NUM_EYE_SHAPES = 6,
    NUM_MOUTH_SHAPES = 6,
    NUM_BROW_SHAPES = 6,
    NUM_NOSE_SHAPES = 6
};

int faceContour = 1;
int hairStyle = 1;
int eyeShape = 1;
int mouthShape = 1;
int browShape = 1;
int noseShape = 1;

void display(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void drawText(const char *string);
void changeFaceContour(int contour);
void changeHair(int hairstyle);
void changeEyes(int eyeShape);
void changeMouth(int mouthShape);
void changeEyebrows(int browShape);
void changeNose(int noseShape);
void clearAndRedraw(int newContour, int newHair, int newEyes, int newMouth, int newBrows, int newNose);

const char *controlsText = "Controles: F1-F6 (Cabelos), 1-6 (Olhos), q-y (Boca), a-h (Sobrancelha), z-n (Nariz)";

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MiniMii - Modifique com as teclas!");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    return 0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    changeFaceContour(faceContour);
    changeHair(hairStyle);
    changeEyes(eyeShape);
    changeMouth(mouthShape);
    changeEyebrows(browShape);
    changeNose(noseShape);

    drawText(controlsText);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Tecla ESC
            exit(0);
        case ' ': // Tecla Espaço para redefinir
            glClear(GL_COLOR_BUFFER_BIT);
            faceContour = 1;
            hairStyle = 1;
            eyeShape = 1;
            mouthShape = 1;
            browShape = 1;
            noseShape = 1;
            drawText(controlsText);
            glFlush();
            break;
        case 'q': // Boca - Exemplo
            mouthShape = 1;
            break;
        case 'w':
            mouthShape = 2;
            break;
        case 'e':
            mouthShape = 3;
            break;
        case 'r':
            mouthShape = 4;
            break;
        case 't':
            mouthShape = 5;
            break;
        case 'y':
            mouthShape = 6;
            break;
        case 'a': // Sobrancelha - Exemplo
            browShape = 1;
            break;
        case 's':
            browShape = 2;
            break;
        case 'd':
            browShape = 3;
            break;
        case 'f':
            browShape = 4;
            break;
        case 'g':
            browShape = 5;
            break;
        case 'h':
            browShape = 6;
            break;
        case 'z': // Nariz - Exemplo
            noseShape = 1;
            break;
        case 'x':
            noseShape = 2;
            break;
        case 'c':
            noseShape = 3;
            break;
        case 'v':
            noseShape = 4;
            break;
        case 'b':
            noseShape = 5;
            break;
        case 'n':
            noseShape = 6;
            break;
        case '1': // Olhos - Exemplo
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
            eyeShape = key - '0';
            break;
    }
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1...GLUT_KEY_F6: // Face contours
            faceContour = key - GLUT_KEY_F1 + 1;
            break;
        case GLUT_KEY_F7...GLUT_KEY_F12: // Hair styles
            hairStyle = key - GLUT_KEY_F7 + 1;
            break;
    }
    glutPostRedisplay();
}

void drawText(const char *string) {
    glColor3ub(0, 0, 0); // Black color
    glRasterPos2f(-0.9, 0.8); // Text position
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string); // Display character by character
        string++;
    }
}

// Implementação das funções para modificar as partes do rosto
void changeFaceContour(int contour) {
    switch (contour) {
        case 1:
            // Contorno facial tipo 1: Círculo completo suave
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.4 * cos(theta); // Raio reduzido para manter dentro do círculo
                    float y = 0.4 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 2:
            // Contorno facial tipo 2: Círculo com "quinas"
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.4 * cos(theta); // Raio reduzido para manter dentro do círculo
                    float y = 0.4 * sin(theta);
                    if (i < 90 || (i > 180 && i < 270)) {
                        x += 0.1;
                    } else {
                        x -= 0.1;
                    }
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 3:
            // Contorno facial tipo 3: Quadrado
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(-0.4, -0.4);
                glVertex2f(0.4, -0.4);
                glVertex2f(0.4, 0.4);
                glVertex2f(-0.4, 0.4);
            glEnd();
            break;
        case 4:
            // Contorno facial tipo 4: Triângulo
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(0.0, 0.4);
                glVertex2f(-0.4, -0.4);
                glVertex2f(0.4, -0.4);
            glEnd();
            break;
        case 5:
            // Contorno facial tipo 5: coração
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(0.0, 0.4);
                glVertex2f(-0.4, 0.0);
                glVertex2f(-0.2, -0.4);
                glVertex2f(0.0, -0.2);
                glVertex2f(0.2, -0.4);
                glVertex2f(0.4, 0.0);
            glEnd();
            break;
        case 6:
            // Contorno facial tipo 6: Losango
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
                glVertex2f(0.0, 0.4);
                glVertex2f(-0.4, 0.0);
                glVertex2f(0.0, -0.4);
                glVertex2f(0.4, 0.0);
            glEnd();
            break;
    }
}

void changeHair(int hairstyle) {
    switch (hairstyle) {
        case 1:
            // Cabelo tipo 1: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.4);
                glVertex2f(-0.3, 0.35);
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 2:
            // Cabelo tipo 2: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.3, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.25, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.3, 0.4);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 3:
            // Cabelo tipo 3: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.3, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.3, 0.4);
            glEnd();
            break;
        case 4:
            // Cabelo tipo 4: Linhas verticais e horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.3, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.25, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.3, 0.4);
                glVertex2f(0.3, 0.3);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.35); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 5:
            // Cabelo tipo 5: Linhas diagonais e horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.4); // Mais próximo do contorno facial
                glVertex2f(-0.2, 0.3);
                glVertex2f(-0.25, 0.4);
                glVertex2f(-0.15, 0.3);
                glVertex2f(-0.2, 0.4);
                glVertex2f(-0.1, 0.3);
                glVertex2f(-0.15, 0.4);
                glVertex2f(-0.05, 0.3);
                glVertex2f(-0.1, 0.4);
                glVertex2f(0.0, 0.3);
                glVertex2f(-0.05, 0.4);
                glVertex2f(0.05, 0.3);
                glVertex2f(0.0, 0.4);
                glVertex2f(0.1, 0.3);
                glVertex2f(0.05, 0.4);
                glVertex2f(0.15, 0.3);
                glVertex2f(0.1, 0.4);
                glVertex2f(0.2, 0.3);
                glVertex2f(0.15, 0.4);
                glVertex2f(0.25, 0.3);
                glVertex2f(0.2, 0.4);
                glVertex2f(0.3, 0.3);
                glVertex2f(0.25, 0.4);
                glVertex2f(0.3, 0.4);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.35); // Mais próximo do contorno facial
                glVertex2f(0.3, 0.35);
                glVertex2f(-0.3, 0.3);
                glVertex2f(0.3, 0.3);
            glEnd();
            break;
        case 6:
            // Cabelo tipo 6: bolinhas
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.3 + 0.1 * cos(theta);
                    float y = 0.4 + 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.1 + 0.1 * cos(theta);
                    float y = 0.4 + 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.1 + 0.1 * cos(theta);
                    float y = 0.4 + 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.3 + 0.1 * cos(theta);
                    float y = 0.4 + 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
    }
}

void changeEyes(int eyeShape) {
    // printf(">>> Alterando olhos para o tipo %d\n", eyeShape);
    switch (eyeShape) {
        case 1:
            // Olhos tipo 1: Círculos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.2 + 0.1 * cos(theta);
                    float y = 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.2 + 0.1 * cos(theta);
                    float y = 0.1 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 2:
            // Olhos tipo 2: Retângulos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(-0.1, -0.1);
                glVertex2f(-0.3, -0.1);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
                glVertex2f(0.3, -0.1);
                glVertex2f(0.1, -0.1);
            glEnd();
            break;
        case 3:
            // Olhos tipo 3: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, -0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, -0.1);
            glEnd();
            break;
        case 4:
            // Olhos tipo 4: Triângulos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(-0.2, -0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
                glVertex2f(0.2, -0.1);
            glEnd();
            break;
        case 5:
            // Olhos tipo 5: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.1);
                glVertex2f(-0.1, 0.1);
                glVertex2f(0.1, 0.1);
                glVertex2f(0.3, 0.1);
            glEnd();
            break;
        case 6:
            // Olhos tipo 6: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.2, 0.1);
                glVertex2f(-0.2, -0.1);
                glVertex2f(0.2, 0.1);
                glVertex2f(0.2, -0.1);
            glEnd();
            break;
    }
}
void changeMouth(int mouthShape) {
        switch (mouthShape) {
        case 1:
            // Desenho da boca tipo 1 (linha reta)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(-0.2, -0.2);
                glVertex2f(0.2, -0.2);
            glEnd();
            break;
        case 2:
            // Desenho da boca tipo 2 (linha curva)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.2, -0.2);
                glVertex2f(-0.1, -0.25);
                glVertex2f(0.1, -0.25);
                glVertex2f(0.2, -0.2);
            glEnd();
            break;
        case 3:
            // Desenho da boca tipo 3 (triângulo)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.2, -0.2);
                glVertex2f(0.2, -0.2);
                glVertex2f(0.0, -0.3);
            glEnd();
            break;
        case 4:
            // Desenho da boca tipo 4 (retângulo)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(-0.2, -0.2);
                glVertex2f(0.2, -0.2);
                glVertex2f(0.2, -0.3);
                glVertex2f(-0.2, -0.3);
            glEnd();
            break;
        case 5:
            // Desenho da boca tipo 5 (linha horizontal)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(-0.2, -0.25);
                glVertex2f(0.2, -0.25);
            glEnd();
            break;
        case 6:
            // Desenho da boca tipo 6 (linha vertical)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(0.0, -0.2);
                glVertex2f(0.0, -0.3);
            glEnd();
            break;
        }
}

void changeEyebrows(int browShape) {
    switch (browShape) {
        case 1:
            // Sobrancelhas tipo 1: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 2:
            // Sobrancelhas tipo 2: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.22); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.27);
                glVertex2f(0.1, 0.27);
                glVertex2f(0.3, 0.22);
            glEnd();
            break;
        case 3:
            // Sobrancelhas tipo 3: Curvas
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.27);
                glVertex2f(0.0, 0.27);
                glVertex2f(0.2, 0.18);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 4:
            // Sobrancelhas tipo 4: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.3, 0.25);
                glVertex2f(-0.1, 0.25);
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.1, 0.25);
                glVertex2f(0.3, 0.25);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 5:
            // Sobrancelhas tipo 5: Zigzag
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.25);
                glVertex2f(-0.1, 0.18);
                glVertex2f(0.0, 0.25);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.2, 0.25);
                glVertex2f(0.3, 0.18);
            glEnd();
            break;
        case 6:
            // Sobrancelhas tipo 6: Linhas horizontais e verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.18); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.18);
                glVertex2f(-0.1, 0.25);
                glVertex2f(-0.3, 0.25);
                glVertex2f(0.1, 0.18);
                glVertex2f(0.3, 0.18);
                glVertex2f(0.3, 0.25);
                glVertex2f(0.1, 0.25);
            glEnd();
            break;
    }
}
void changeNose(int noseShape) {
    switch (noseShape) {
        case 1:
            // Nariz tipo 1: Triângulo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.1, 0.0);
                glVertex2f(0.1, 0.0);
                glVertex2f(0.0, -0.2);
            glEnd();
            break;
        case 2:
            // Nariz tipo 2: Linha vertical
            glColor3ub(255, 0, 0); // Cor vermelha
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(0.0, 0.0);
                glVertex2f(0.0, -0.2);
            glEnd();
            break;
        case 3:
            // Nariz tipo 3: Retângulo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(-0.1, 0.0);
                glVertex2f(0.1, 0.0);
                glVertex2f(0.1, -0.2);
                glVertex2f(-0.1, -0.2);
            glEnd();
            break;
        case 4:
            // Nariz tipo 4: Losango
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(0.0, 0.0);
                glVertex2f(-0.1, -0.1);
                glVertex2f(0.0, -0.2);
                glVertex2f(0.1, -0.1);
            glEnd();
            break;
        case 5:
            // Nariz tipo 5: Círculo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.05 * cos(theta); // Raio menor para formar um círculo
                    float y = -0.1 + 0.05 * sin(theta);
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 6:
            // Nariz tipo 6: Triângulo invertido
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.1, -0.2);
                glVertex2f(0.1, -0.2);
                glVertex2f(0.0, 0.0);
            glEnd();
            break;
        default:
            break;
    }
}


void clearAndRedraw(int newContour, int newHair, int newEyes, int newMouth, int newBrows, int newNose) {
    // Function to clear the display and redraw with new settings
    glClear(GL_COLOR_BUFFER_BIT);
    changeFaceContour(newContour);
    changeHair(newHair);
    changeEyes(newEyes);
    changeMouth(newMouth);
    changeEyebrows(newBrows);
    changeNose(newNose);
}

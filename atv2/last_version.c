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
        case 32: // Tecla Espaço para redefinir
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
        case 113: // Boca - Exemplo
            mouthShape = 1;
            break;
        case 119:
            mouthShape = 2;
            break;
        case 101:
            mouthShape = 3;
            break;
        case 114:
            mouthShape = 4;
            break;
        case 116:
            mouthShape = 5;
            break;
        case 121:
            mouthShape = 6;
            break;
        case 97: // Sobrancelha - Exemplo
            browShape = 1;
            break;
        case 115:
            browShape = 2;
            break;
        case 100:
            browShape = 3;
            break;
        case 102:
            browShape = 4;
            break;
        case 103:
            browShape = 5;
            break;
        case 104:
            browShape = 6;
            break;
        case 122: // Nariz - Exemplo
            noseShape = 1;
            break;
        case 120:
            noseShape = 2;
            break;
        case 99:
            noseShape = 3;
            break;
        case 118:
            noseShape = 4;
            break;
        case 98:
            noseShape = 5;
            break;
        case 110:
            noseShape = 6;
            break;
        case 49: // Olhos - Exemplo
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
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
                float x = 0.4 * cos(theta); // Aumenta o raio para uma cabeça maior
                float y = 0.4 * sin(theta); // Aumenta o raio para uma cabeça maior
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
                float x = 0.4 * cos(theta); // Aumenta o raio para uma cabeça maior
                float y = 0.4 * sin(theta); // Aumenta o raio para uma cabeça maior
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
            glVertex2f(-0.4, -0.4); // Ajuste para encaixar com o cabelo
            glVertex2f(0.4, -0.4);  // Ajuste para encaixar com o cabelo
            glVertex2f(0.4, 0.4);   // Ajuste para encaixar com o cabelo
            glVertex2f(-0.4, 0.4);  // Ajuste para encaixar com o cabelo
            glEnd();
            break;
        case 4:
            // Contorno facial tipo 4: hexágono
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
            glVertex2f(-0.4, 0.0);  // Ajuste para encaixar com o cabelo
            glVertex2f(-0.2, -0.4); // Ajuste para encaixar com o cabelo
            glVertex2f(0.2, -0.4);  // Ajuste para encaixar com o cabelo
            glVertex2f(0.4, 0.0);   // Ajuste para encaixar com o cabelo
            glVertex2f(0.2, 0.4);   // Ajuste para encaixar com o cabelo
            glVertex2f(-0.2, 0.4);  // Ajuste para encaixar com o cabelo
            glEnd();
            break;
        case 5:
            // Contorno facial tipo 5: Coração
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
            glVertex2f(0.0, 0.4);   // Ajuste para encaixar com o cabelo
            glVertex2f(-0.4, 0.0);  // Ajuste para encaixar com o cabelo
            glVertex2f(-0.2, -0.4); // Ajuste para encaixar com o cabelo
            glVertex2f(0.2, -0.4);  // Ajuste para encaixar com o cabelo
            glVertex2f(0.4, 0.0);    // Ajuste para encaixar com o cabelo
            glEnd();
            break;
        case 6:
            // Contorno facial tipo 6: Losango
            glLineWidth(2.0); // Define a largura da linha
            glBegin(GL_LINE_LOOP); // Desenha um contorno fechado (polígono)
            glVertex2f(0.0, 0.4);  // Ajuste para encaixar com o cabelo
            glVertex2f(-0.4, 0.0); // Ajuste para encaixar com o cabelo
            glVertex2f(0.0, -0.4);  // Ajuste para encaixar com o cabelo
            glVertex2f(0.4, 0.0);   // Ajuste para encaixar com o cabelo
            glEnd();
            break;
    }
}


void drawTexturedHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_LINES);
    for (float x = -0.35; x <= 0.35; x += 0.1) {
        glVertex2f(x, yOffset);     // Linha vertical para representar o cabelo
        glVertex2f(x, yOffset - 0.1); // Tamanho e espaçamento ajustáveis
    }
    glEnd();
}

void drawCurlyHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float theta = i * 3.14159265359 / 180.0;
        float x = -0.2 + 0.1 * cos(theta);
        float y = yOffset - 0.1 + 0.1 * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float theta = i * 3.14159265359 / 180.0;
        float x = 0.0 + 0.1 * cos(theta);
        float y = yOffset - 0.1 + 0.1 * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float theta = i * 3.14159265359 / 180.0;
        float x = 0.2 + 0.1 * cos(theta);
        float y = yOffset - 0.1 + 0.1 * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawWavyHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_LINE_STRIP);
    for (float x = -0.4; x <= 0.4; x += 0.05) {
        float y = yOffset - 0.05 + 0.025 * sin(4 * 3.14159265359 * x);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawPonytailHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, yOffset - 0.1);
    glVertex2f(-0.2, yOffset - 0.4);
    glVertex2f(-0.4, yOffset - 0.4);

    glVertex2f(0.2, yOffset - 0.1);
    glVertex2f(0.2, yOffset - 0.4);
    glVertex2f(0.4, yOffset - 0.4);
    glEnd();
}

void drawSpikyHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, yOffset - 0.1);
    glVertex2f(0.0, yOffset + 0.2);
    glVertex2f(0.2, yOffset - 0.1);

    glVertex2f(-0.1, yOffset - 0.1);
    glVertex2f(0.1, yOffset + 0.2);
    glVertex2f(0.3, yOffset - 0.1);

    glVertex2f(-0.3, yOffset - 0.1);
    glVertex2f(-0.1, yOffset + 0.2);
    glVertex2f(0.1, yOffset - 0.1);
    glEnd();
}

void drawBangsHair(float yOffset) {
    glColor3ub(0, 0, 0); // Cor preta
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, yOffset - 0.1);
    glVertex2f(0.2, yOffset - 0.1);
    glVertex2f(0.0, yOffset - 0.4);
    glEnd();
}

void changeHair(int hairstyle) {
    switch (hairstyle) {
        case 1:
            // Cabelo tipo 1: Cabelo liso
            drawTexturedHair(0.4);
            break;
        case 2:
            // Cabelo tipo 2: Cabelo encaracolado
            drawCurlyHair(0.4);
            break;
        case 3:
            // Cabelo tipo 3: Cabelo ondulado
            drawWavyHair(0.4);
            break;
        case 4:
            // Cabelo tipo 4: Rabo de cavalo
            drawPonytailHair(0.4);
            break;
        case 5:
            // Cabelo tipo 5: Cabelo espetado
            drawSpikyHair(0.4);
            break;
        case 6:
            // Cabelo tipo 6: Franja
            drawBangsHair(0.4);
            break;
        default:
            break;
    }
}


void changeEyes(int eyeShape) {
    switch (eyeShape) {
        case 1:
            // Olhos tipo 1: Círculos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.2 + 0.05 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.2 + 0.05 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 2:
            // Olhos tipo 2: Círculos com "pupila"
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.2 + 0.05 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.2 + 0.05 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            glColor3ub(255, 255, 255); // Cor branca
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = -0.2 + 0.02 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.2 + 0.02 * cos(theta); // Raio menor para um olho menor
                    float y = 0.05 * sin(theta);       // Raio menor para um olho menor
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 3:
            // Olhos tipo 3: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.25, 0.1); // Ajuste para olhos menores
                glVertex2f(-0.15, -0.1); // Ajuste para olhos menores
                glVertex2f(0.15, 0.1); // Ajuste para olhos menores
                glVertex2f(0.25, -0.1); // Ajuste para olhos menores
            glEnd();
            break;
        case 4:
            // Olhos tipo 4: Triângulos
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.25, 0.1); // Ajuste para olhos menores
                glVertex2f(-0.15, 0.1); // Ajuste para olhos menores
                glVertex2f(-0.2, -0.1); // Ajuste para olhos menores
                glVertex2f(0.15, 0.1); // Ajuste para olhos menores
                glVertex2f(0.25, 0.1); // Ajuste para olhos menores
                glVertex2f(0.2, -0.1); // Ajuste para olhos menores
            glEnd();
            break;
        case 5:
            // Olhos tipo 5: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.25, 0.1); // Ajuste para olhos menores
                glVertex2f(-0.15, 0.1); // Ajuste para olhos menores
                glVertex2f(0.15, 0.1); // Ajuste para olhos menores
                glVertex2f(0.25, 0.1); // Ajuste para olhos menores
            glEnd();
            break;
        case 6:
            // Olhos tipo 6: Linhas verticais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.2, 0.1); // Ajuste para olhos menores
                glVertex2f(-0.2, -0.1); // Ajuste para olhos menores
                glVertex2f(0.2, 0.1); // Ajuste para olhos menores
                glVertex2f(0.2, -0.1); // Ajuste para olhos menores
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
                glVertex2f(-0.15, -0.15); // Posição um pouco mais acima
                glVertex2f(0.15, -0.15);  // Posição um pouco mais acima
            glEnd();
            break;
        case 2:
            // Desenho da boca tipo 2 (linha curva)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.15, -0.15); // Posição um pouco mais acima
                glVertex2f(-0.1, -0.2);
                glVertex2f(0.1, -0.2);
                glVertex2f(0.15, -0.15);  // Posição um pouco mais acima
            glEnd();
            break;
        case 3:
            // Desenho da boca tipo 3 (triângulo)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.15, -0.15); // Posição um pouco mais acima
                glVertex2f(0.15, -0.15);  // Posição um pouco mais acima
                glVertex2f(0.0, -0.2);    // Posição um pouco mais acima
            glEnd();
            break;
        case 4:
            // Desenho da boca tipo 4 (retângulo)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(-0.15, -0.15); // Posição um pouco mais acima
                glVertex2f(0.15, -0.15);  // Posição um pouco mais acima
                glVertex2f(0.15, -0.2);   // Posição um pouco mais acima
                glVertex2f(-0.15, -0.2);  // Posição um pouco mais acima
            glEnd();
            break;
        case 5:
            // Desenho da boca tipo 5 (linha horizontal)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(-0.15, -0.175); // Posição um pouco mais acima
                glVertex2f(0.15, -0.175);  // Posição um pouco mais acima
            glEnd();
            break;
        case 6:
            // Desenho da boca tipo 6 (linha vertical)
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_LINES);
                glVertex2f(0.0, -0.15);
                glVertex2f(0.0, -0.2); // Posição um pouco mais acima
            glEnd();
            break;
        default:
            break;
    }
}



void changeEyebrows(int browShape) {
    switch (browShape) {
        case 1:
            // Sobrancelhas tipo 1: Linhas horizontais
            glColor3ub(0, 0, 0); // Cor preta
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.15); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.15);
                glVertex2f(0.1, 0.15);
                glVertex2f(0.3, 0.15);
            glEnd();
            break;
        case 2:
            // Sobrancelhas tipo 2: Linhas diagonais
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0);   // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.19); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.24);
                glVertex2f(0.1, 0.24);
                glVertex2f(0.3, 0.19);
            glEnd();
            break;
        case 3:
            // Sobrancelhas tipo 3: Curvas suaves
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0);   // Largura da linha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.15); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.21);
                glVertex2f(0.0, 0.24);
                glVertex2f(0.2, 0.21);
                glVertex2f(0.3, 0.15);
            glEnd();
            break;
        case 4:
            // Sobrancelhas tipo 4: Linhas verticais com espessura variável
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0);   // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.15); // Mais próximo dos olhos
                glVertex2f(-0.3, 0.22);
                glVertex2f(-0.15, 0.22);
                glVertex2f(-0.15, 0.15);
                glVertex2f(0.0, 0.22);
                glVertex2f(0.0, 0.15);
                glVertex2f(0.15, 0.22);
                glVertex2f(0.15, 0.15);
                glVertex2f(0.3, 0.22);
                glVertex2f(0.3, 0.15);
            glEnd();
            break;
        case 5:
            // Sobrancelhas tipo 5: Zigzag
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(2.0);   // Largura da linha
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, 0.15); // Mais próximo dos olhos
                glVertex2f(-0.2, 0.21);
                glVertex2f(-0.1, 0.15);
                glVertex2f(0.0, 0.21);
                glVertex2f(0.1, 0.15);
                glVertex2f(0.2, 0.21);
                glVertex2f(0.3, 0.15);
            glEnd();
            break;
        case 6:
            // Sobrancelhas tipo 6: Linhas horizontais e verticais com espessura variável
            glColor3ub(0, 0, 0); // Cor preta
            glLineWidth(3.0);   // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(-0.3, 0.15); // Mais próximo dos olhos
                glVertex2f(-0.1, 0.15);
                glVertex2f(-0.1, 0.22);
                glVertex2f(-0.3, 0.22);
                glVertex2f(0.1, 0.15);
                glVertex2f(0.3, 0.15);
                glVertex2f(0.3, 0.22);
                glVertex2f(0.1, 0.22);
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
                glVertex2f(-0.05, 0.0); // Ajuste para um nariz menor
                glVertex2f(0.05, 0.0);  // Ajuste para um nariz menor
                glVertex2f(0.0, -0.1);   // Ajuste para um nariz menor
            glEnd();
            break;
        case 2:
            // Nariz tipo 2: Linha vertical
            glColor3ub(255, 0, 0); // Cor vermelha
            glLineWidth(2.0); // Largura da linha
            glBegin(GL_LINES);
                glVertex2f(0.0, 0.0);
                glVertex2f(0.0, -0.1); // Ajuste para um nariz menor
            glEnd();
            break;
        case 3:
            // Nariz tipo 3: Retângulo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(-0.05, 0.0); // Ajuste para um nariz menor
                glVertex2f(0.05, 0.0);  // Ajuste para um nariz menor
                glVertex2f(0.05, -0.1);  // Ajuste para um nariz menor
                glVertex2f(-0.05, -0.1); // Ajuste para um nariz menor
            glEnd();
            break;
        case 4:
            // Nariz tipo 4: Losango
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                glVertex2f(0.0, 0.0);
                glVertex2f(-0.05, -0.05); // Ajuste para um nariz menor
                glVertex2f(0.0, -0.1);     // Ajuste para um nariz menor
                glVertex2f(0.05, -0.05);   // Ajuste para um nariz menor
            glEnd();
            break;
        case 5:
            // Nariz tipo 5: Círculo
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_POLYGON);
                for (int i = 0; i < 360; ++i) {
                    float theta = i * 3.14159265359 / 180.0;
                    float x = 0.025 * cos(theta); // Raio menor para um círculo menor
                    float y = -0.05 + 0.025 * sin(theta); // Ajuste para um nariz menor
                    glVertex2f(x, y);
                }
            glEnd();
            break;
        case 6:
            // Nariz tipo 6: Triângulo invertido
            glColor3ub(255, 0, 0); // Cor vermelha
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.05, -0.1); // Ajuste para um nariz menor
                glVertex2f(0.05, -0.1);  // Ajuste para um nariz menor
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

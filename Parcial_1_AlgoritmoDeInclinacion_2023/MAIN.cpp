


/* DDA (Digital Differential Analyzer)

1. Calcula la diferencia entre las coordenadas x e y de dos puntos dados.

2. Determina el número de pasos necesarios para dibujar la línea, tomando la diferencia más grande entre las coordenadas x e y.

3. Calcula los incrementos necesarios para avanzar en x e y en cada paso.

4. Utiliza un bucle para actualizar las coordenadas y dibujar píxeles a lo largo de la línea.


DESVENTAJAS
Sin embargo, la acumulación de erro-res de redondeo en las sucesivas sumas del incremento de coma flotante pueden hacer que las posiciones de
píxel sufran cierta deriva con respecto al verdadero trayecto lineal, para segmentos lineales largos.

*/




#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>


// Ancho y alto de la ventana
const int ventanaAncho = 1280;
const int ventanaAlto = 720;

// Función para centrar la ventana GLFW en la pantalla
void centrarVentana(GLFWwindow* window) {
    // Obtiene la resolución del monitor primario
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    // Calcula la posición en la que se debe colocar la ventana para que esté centrada
    int xPos = (mode->width - ventanaAncho) / 2;
    int yPos = (mode->height - ventanaAlto) / 2;

    // Establece la posición de la ventana
    glfwSetWindowPos(window, xPos, yPos);
}




//           ( x0  ,  y0  , ------ COLOR ------)
void setPixel(int x, int y, int r, int g, int b) {
    //INICIAMOS DIBUJO PUNTO
    glPointSize(3.0f);

    glBegin(GL_POINTS);
    //COLOR
    glColor3f(r, g, b);

    //DEFINIMOS PUNTO
    glVertex2i(x, y);

    //FINALIZAMOS DIBUJO PUNTO
    glEnd();
}


//ALGORITMO DDA PAA LINEA

//             ( x0, y0,     xend,     yend,      -------- COLOR ---------)
void lineDDA(int xO, int yO, int xEnd, int yEnd, float r, float g, float b) {

    //VARIABLES
    int dx = xEnd - xO, dy = yEnd - yO, steps, k;
    float xIncrement, yIncrement, x = xO, y = yO;


    //CÁLCULOS
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;

    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y), r, g, b);
    }
}



//ALGORITMO BRESENHAM


void lineaBresenham(int x0, int y0, int xEnd, int yEnd, float r, float g, float b) {
    int dx = fabs(xEnd - x0);
    int dy = fabs(yEnd - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    // Determinar qué extremo usar como posición inicial.
    if (x0 > xEnd) {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }
    else {
        x = x0;
        y = y0;
    }

    setPixel(x, y, r, g, b);

    while (x < xEnd) {
        x++;

        if (p < 0) {
            p += twoDy;
        }
        else {
            y++;
            p += twoDyMinusDx;
        }

        setPixel(x, y, r, g, b);
    }
}



// Clase PuntoPantalla
class PuntoPantalla {
private:
    GLint x, y;

public:
    PuntoPantalla() {
        x = y = 0;
    }

    void establecerCoordenadas(GLint valorX, GLint valorY) {
        x = valorX;
        y = valorY;
    }

    GLint obtenerX() const {
        return x;
    }

    GLint obtenerY() const {
        return y;
    }

    void incrementarX() {
        x++;
    }

    void decrementarY() {
        y--;
    }
};

// Función para trazar puntos del círculo
void trazarPuntosCirculo(int xc, int yc, PuntoPantalla puntoCirculo, float r, float g, float b) {
    setPixel(xc + puntoCirculo.obtenerX(), yc + puntoCirculo.obtenerY(), r, g, b);
    setPixel(xc - puntoCirculo.obtenerX(), yc + puntoCirculo.obtenerY(), r, g, b);
    setPixel(xc + puntoCirculo.obtenerX(), yc - puntoCirculo.obtenerY(), r, g, b);
    setPixel(xc - puntoCirculo.obtenerX(), yc - puntoCirculo.obtenerY(), r, g, b);
    setPixel(xc + puntoCirculo.obtenerY(), yc + puntoCirculo.obtenerX(), r, g, b);
    setPixel(xc - puntoCirculo.obtenerY(), yc + puntoCirculo.obtenerX(), r, g, b);
    setPixel(xc + puntoCirculo.obtenerY(), yc - puntoCirculo.obtenerX(), r, g, b);
    setPixel(xc - puntoCirculo.obtenerY(), yc - puntoCirculo.obtenerX(), r, g, b);
}

// Función para trazar un círculo utilizando el algoritmo de Punto Medio
void trazarCirculoPuntoMedio(int xc, int yc, int radio, float r, float g, float b) {
    PuntoPantalla puntoCirculo;
    int p = 1 - radio;

    puntoCirculo.establecerCoordenadas(0, radio);
    trazarPuntosCirculo(xc, yc, puntoCirculo, r, g, b);

    while (puntoCirculo.obtenerX() < puntoCirculo.obtenerY()) {
        puntoCirculo.incrementarX();
        if (p < 0) {
            p += 2 * puntoCirculo.obtenerX() + 1;
        }
        else {
            puntoCirculo.decrementarY();
            p += 2 * (puntoCirculo.obtenerX() - puntoCirculo.obtenerY()) + 1;
        }
        trazarPuntosCirculo(xc, yc, puntoCirculo, r, g, b);
    }
}




// Función para dibujar una elipse
void dibujarElipse(int xCentro, int yCentro, int Rx, int Ry, float r, float g, float b) {

    // Establecer el color de la LÍNEA a amarillo
    glColor3f(r, g, b);

    // Dibujo por puntos
    glBegin(GL_POINTS);

    // VARIABLES NECESARIAS
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int dosRx2 = 2 * Rx2;
    int dosRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = dosRx2 * y;

    // Región 1
    p = round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py) {
        x++;
        px += dosRy2;
        if (p < 0) {
            p += Ry2 + px;
        }
        else {
            y--;
            py -= dosRx2;
            p += Ry2 + px - py;
        }

        // DIBUJA EN LOS PUNTOS CALCULADOS
        glVertex2i(xCentro + x, yCentro + y);
        glVertex2i(xCentro - x, yCentro + y);
        glVertex2i(xCentro + x, yCentro - y);
        glVertex2i(xCentro - x, yCentro - y);
    }

    // Región 2
    p = round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
    while (y > 0) {
        y--;
        py -= dosRx2;
        if (p > 0) {
            p += Rx2 - py;
        }
        else {
            x++;
            px += dosRy2;
            p += Rx2 - py + px;
        }

        // DIBUJA EN LOS PUNTOS CALCULADOS
        glVertex2i(xCentro + x, yCentro + y);
        glVertex2i(xCentro - x, yCentro + y);
        glVertex2i(xCentro + x, yCentro - y);
        glVertex2i(xCentro - x, yCentro - y);
    }

    glEnd();
}



int main() {

    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Error: Fallo en la inicialización de GLFW." << std::endl;
        return -1;
    }

    // Crear una ventana con el ancho y alto definidos
    window = glfwCreateWindow(ventanaAncho, ventanaAlto, "DDA LINEA BÁSCIA", NULL, NULL);


    if (!window) {

        std::cerr << "Error: Fallo en la creación de la ventana GLFW." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Centrar la ventana en la pantalla
    centrarVentana(window);

    glfwMakeContextCurrent(window);

    glOrtho(0, ventanaAncho, 0, ventanaAlto, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);


        // Llama a la función lineDDA para dibujar una línea

        //     ( x0,  y0, xend, yend,----- COLOR -----)
        lineDDA(100, 100, 400, 300, 1.0f, 0.0f, 0.0f);


        // Llamar a lineaBresenham para dibujar una línea de (100, 100) a (700, 500) en azul (0.0, 0.0, 1.0)
        lineaBresenham(50, 50, 500, 100, 0.0f, 0.0f, 1.0f);

        // Llamar a trazarCirculoPuntoMedio para dibujar un círculo en el centro de la ventana

        //                       X    Y  RADIO          
        trazarCirculoPuntoMedio(400, 400, 100, 0.0f, 1.0f, 1.0f);


        // Llamar a dibujarElipse para dibujar una elipse de color amarillo
        dibujarElipse(400, 400, 100, 50, 1.0f, 1.0f, 0.0f);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

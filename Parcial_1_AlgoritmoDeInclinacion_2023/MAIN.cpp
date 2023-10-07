#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Inicializa GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // Crea una ventana GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Inclinaci�n de Rect�ngulo", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Establece el contexto de la ventana como el contexto actual
    glfwMakeContextCurrent(window);

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        // Borra el b�fer de color
        glClear(GL_COLOR_BUFFER_BIT);

        // Aplicar la transformaci�n de inclinaci�n en la direcci�n-x
        float shx = 0.5f; // Par�metro de inclinaci�n en la direcci�n-x
        float vertices[] = {
            -0.2f + shx * 0.2f, -0.2f,
            0.2f + shx * 0.2f, -0.2f,
            0.2f, 0.2f,
            -0.2f, 0.2f
        };

        // Dibujar el rect�ngulo inclinado
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);

        // Intercambiar los b�feres y procesar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminar GLFW
    glfwTerminate();
    //return�0;
}
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const GLchar* vertexSource =
    "#version 330\n"
    "in vec2 position;"
    "void main()"
    "{"
    "    gl_Position = vec4(position, 0.0, 1.0);"
    "}";
const GLchar* fragmentSource =
    "#version 330\n"
    "out vec4 fragColor;"
    "void main()"
    "{"
    "    fragColor = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";

void checkErr(const char* msg) {
    GLenum err = glGetError();

    if (err != 0) {
        printf("@ \"%s\": %d\n", msg, err);
        exit(1);
    } else {
        printf("@ \"%s\": successful\n", msg);
    }
}


GLuint createVertexBuffer(float vertices[], int numVertices) {

    for (int i = 0; i < numVertices * 2; i += 2) {
        printf("(%f, %f)\n", vertices[i], vertices[i+1]);
    }

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    checkErr("Gen VBO");

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    checkErr("Bind VBO");
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 2, vertices, GL_DYNAMIC_DRAW);
    checkErr("VBO data");

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkErr("Compile vert shader");

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkErr("Compile frag shader");

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    checkErr("Link program");
    glUseProgram(shaderProgram);
    checkErr("Use program");

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    checkErr("Gen VAO");
    glBindVertexArray(vao);
    checkErr("Bind VAO");

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    checkErr("Enable vertex attrib");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    checkErr("Describe vert data");

    return vao;
}


int createTriangle() {
    float vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };
    return createVertexBuffer(vertices, 3);
}

void graphicsDrawShape(int vao, int numVertices) {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void predraw() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int graphics_main(void (*game_init)(), void (*game_draw)()) {
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf ("Renderer:       %s\n", renderer);
    printf ("OpenGL version: %s\n", version);
    printf ("GLSL version:   %s\n", glslVersion);

    game_init();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Do rendering here
        predraw();
        game_draw();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

#endif

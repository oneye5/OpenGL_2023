

#include "Renderer.h"
#include "FileLoader.h"

GLFWwindow* window;
unsigned int buffer;
unsigned int shader;

int Renderer::Initialize()
{

    if (!glfwInit())
    {
        std::cout << "failed to initialize glfw";
        return -1;
    }



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "MY NAME IS OWAN AND IM COOL", NULL, NULL);
    if (!window)
    {
        std::cout << "failed to initialize window";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    //initialize glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew failed to initialize";
        return -1;
    }
    else
        std::cout << glGetString(GL_VERSION);



    //create buffer
    float verticies[6] =
    {

        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f

    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), verticies, GL_STATIC_DRAW);//buffer size


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2.0f, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //create shaders
    std::string path = FileLoader::GetWorkingDir() + "/Shaders/test.txt";
    FileLoader::GetFileContents(path);

    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 1.0, 0.0, 0.0);\n"
        "}\n";

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    shader = Renderer::createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    return 0;
}
void Renderer::Destroy()
{
    glDeleteProgram(shader);
    glfwTerminate();
}
int Renderer::Render() //returns -1 to quit window
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
    

    if (glfwWindowShouldClose(window))
        return -1;
    else
        return 0;
}

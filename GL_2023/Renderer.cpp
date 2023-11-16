

#include "Renderer.h"
#include "FileLoader.h"


GLFWwindow* window;
unsigned int vertexBuffer;
unsigned int indexBuffer;
unsigned int shader;

int Renderer::Initialize()
{

    if (!glfwInit())
    {
        std::cout << "failed to initialize glfw";
        return -1;
    }



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 400, "MY NAME IS OWAN AND IM COOL", NULL, NULL);
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
    float verticies[] =
    {

        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f,
        -0.5f,0.5f

    };

    unsigned int indicies[] =
    {
        0,1,2,
        2,3,0
    };

    //vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verticies, GL_STATIC_DRAW);//buffer size

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2.0f, 0);
    glEnableVertexAttribArray(0);


    //index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);//buffer size


    

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    
    //create shaders
    std::string path = FileLoader::GetWorkingDir() + "/Shaders/";
    
    std::string fragmentShader = FileLoader::GetFileContents(path + "defaultFragment.glsl");
    std::string vertexShader = FileLoader::GetFileContents(path + "defaultVertex.glsl");

    shader = Renderer::createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    if (location == -1)
        std::cout << "uniform not found";
    else
        glUniform4f(location, 0.2f, 0.3f, 0.5f, 1.0f);

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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
    

    if (glfwWindowShouldClose(window))
        return -1;
    else
        return 0;
}

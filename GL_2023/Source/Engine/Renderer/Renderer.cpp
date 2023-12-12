

#include "Renderer.h"
#include "ShaderWrapper.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SurfaceImage.h"

GLFWwindow* window;
unsigned int vertexBuffer;
unsigned int indexBuffer;
unsigned int vertexArrayObject;

const int screenWidth = 1600;
const int screenHeight = 900;

Camera cam(screenWidth,screenHeight);
ShaderWrapper shader;
 
//SurfaceImage* SurfaceImages;
SurfaceImage* surfaceImage = nullptr;

void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam)
{
    string sourceStr, severityStr;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API: sourceStr = "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "WINDOW";
    default: sourceStr = source;
    }


    std::cout << " source: " << sourceStr << " severity: " << severity << " mesage: " << message << "\n";
}

int Renderer::Initialize()
{

    if (!glfwInit())
    {
        std::cout << "failed to initialize glfw";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "MY NAME IS OWAN AND IM COOL", NULL, NULL);
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





    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessage, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

    //    \GL_2023\Source\Client_Assets\GraphicsAssets\Textures\texture.png
    ActiveCamera = &cam; 
    shader.LoadShaders();

   surfaceImage = new SurfaceImage(FileLoader::GetWorkingDir() + "/Source/Client_Assets/GraphicsAssets/Textures/texture.png");
   surfaceImage->Bind(0);
   shader.SetSurfaceImage(0, 0);
  
 

    return 0;
}
void Renderer::InitBuffers(std::vector<float> verticies,std::vector<unsigned int> indicies)
{
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);

    // Define the layout for the vertex buffer (positions, normals, UVs)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr); // Position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3)); // Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6)); // UVs

    // Index buffer
    /**/
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}
void Renderer::Destroy()
{
    glDeleteProgram(shader.Shader);
    glfwTerminate();
}
int Renderer::Render() //returns -1 to quit window
{
    glUseProgram(shader.Shader);
   
    ActiveCamera->updateRotation(); ActiveCamera->makeView();
    shader.UpdateMatricies(cam.projectionMatrix,glm::mat4(1.0f), cam.viewMatrix);
    surfaceImage->Bind(0);
    shader.SetSurfaceImage(0, 0);

    glBindVertexArray(vertexArrayObject); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw calls


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
   

   
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT,nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
    

    if (glfwWindowShouldClose(window))
        return -1;
    else
        return 0;
}

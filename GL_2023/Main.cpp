

#include "Main.h"

static unsigned int compileShader( unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cout <<"failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message;
        glDeleteShader(id);
        return 0;
    }
    std::cout << "\nshader compiled succesfully id:" << id << " src:\n" << src << " END OF SHADER SRC \n";
    return id;
}
static int createShader(const std::string& vertexShader, const std::string& pixelShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, pixelShader);

    glAttachShader(program, vs); glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteProgram(vs); glDeleteShader(fs);

    return program;

}
int main(void)
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;
  

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "MY NAME IS OWAN AND IM COOL", NULL, NULL);
    if (!window)
    {
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
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),verticies,GL_STATIC_DRAW);//buffer size

 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2.0f,0); 
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //create shaders
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
   
    unsigned int shader = createShader(vertexShader,fragmentShader);
    glUseProgram(shader);
  
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);




        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
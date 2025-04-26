#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>
#include <fstream>

//function definition
float blendShape(std::vector<float>&, std::vector<float>&);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "cube_solid", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 1/Assignment 1/Assignment 1/vertex_Shader.h", "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 1/Assignment 1/Assignment 1/fragment_Shader.h");
    
    //Blendweight Function call
    std::vector<float> vbuffer_new;
    std::vector<float> nbuffer_new;
    blendShape(vbuffer_new, nbuffer_new);
    
    
    //std::cout<<vbuffer_new.size();
    unsigned int vertexVBO, normalVBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexVBO);
    glGenBuffers(1, &normalVBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vbuffer_new.size() * sizeof(float), &vbuffer_new[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, nbuffer_new.size() * sizeof(float), &nbuffer_new[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        //Face Culling
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        
        //WireFrame
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);

        view = glm::lookAt(glm::vec3(20,50,200), glm::vec3(0,90,0), glm::vec3(0,1,0)); // Camera is at (0,0,10), in World Space
        ourShader.setMat4("view", view);

        projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f); // Camera is at (0,0,10), in World Space
        ourShader.setMat4("projection", projection);

        // render boxes
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vbuffer_new.size() / 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &normalVBO);


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
static unsigned int ss_id = 0;
void dump_framebuffer_to_ppm(std::string prefix, unsigned int width, unsigned int height) {
    int pixelChannel = 3;
    int totalPixelSize = pixelChannel * width * height * sizeof(GLubyte);
    GLubyte * pixels = new GLubyte [totalPixelSize];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    std::string file_name = prefix + std::to_string(ss_id) + ".ppm";
    std::ofstream fout(file_name);
    fout << "P3\n" << width << " " << height << "\n" << 255 << std::endl;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            size_t cur = pixelChannel * ((height - i - 1) * width + j);
            fout << (int)pixels[cur] << " " << (int)pixels[cur + 1] << " " << (int)pixels[cur + 2] << " ";
        }
        fout << std::endl;
    }
    ss_id ++;
    delete [] pixels;
    fout.flush();
    fout.close();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //press p to capture screen
    if(glfwGetKey(window, GLFW_KEY_P) ==GLFW_PRESS)
    {
        std::cout << "Capture Window " << ss_id << std::endl;
        int buffer_width, buffer_height;
        glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
        dump_framebuffer_to_ppm("Assignment1-ss", buffer_width, buffer_height);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//Blendshade Weight
float blendShape (std::vector<float>& vbuffer_new, std::vector<float>& nbuffer_new)
{
    std::string obj_path_base = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 2/data/faces/base.obj";
    std::string obj_path_i = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 2/data/faces";
    std::ifstream weight("/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 2/data/weights/11.weights");

    std::vector<float> vbuffer_i;
    std::vector<float> nbuffer_i;
    
    std::string tempWeight;
    int currentLineNum = 0;
    
//---------------- Base object----------------
    //tinyobj attribute
    tinyobj::attrib_t attrib_base;
    std::vector<tinyobj::shape_t> shapes_base;
    std::vector<tinyobj::material_t> materials_base;
        // tinyobj load obj
    std::string warn_base, err_base;
    bool bTriangulate_base = true;
    bool bSuc_base = tinyobj::LoadObj(&attrib_base, &shapes_base, &materials_base, &warn_base, &err_base, obj_path_base.c_str(), nullptr, bTriangulate_base);
    if (!bSuc_base)
    {
        std::cout << "tinyobj error: " << err_base.c_str() << std::endl;
        return -1;
    }
    
    for (const auto& shape : shapes_base) {
        for (auto face : shape.mesh.indices)
        {
            int vid_base = face.vertex_index;
            int nid_base = face.normal_index;
                
            //fill in vertex buffer with vertex positions
            //std::cout << attrib.vertices[vid*3];
            vbuffer_new.push_back(attrib_base.vertices[vid_base * 3]);//vertex vid's x
            vbuffer_new.push_back(attrib_base.vertices[vid_base * 3 + 1]);//vertex vid's y
            vbuffer_new.push_back(attrib_base.vertices[vid_base * 3 + 2]);//vertex vid's z
            
            //fill in normal buffer with normal directions
            nbuffer_new.push_back(attrib_base.normals[nid_base * 3]);
            nbuffer_new.push_back(attrib_base.normals[nid_base * 3 + 1]);
            nbuffer_new.push_back(attrib_base.normals[nid_base * 3 + 2]);
        }
    }
    
//---------------- i object----------------
    for (int i = 0; i < 35; i++)
    {
        std::string fileName = std::to_string(i) + ".obj";
        std::string filePath = obj_path_i + "/" + fileName;
        
        //tinyobj attribute
        tinyobj::attrib_t attrib_i;
        std::vector<tinyobj::shape_t> shapes_i;
        std::vector<tinyobj::material_t> materials_i;
            // tinyobj load obj
        std::string warn_i, err_i;
        bool bTriangulate_i = true;
        bool bSuc_i = tinyobj::LoadObj(&attrib_i, &shapes_i, &materials_i, &warn_i, &err_i, filePath.c_str(), nullptr, bTriangulate_i);
        if (!bSuc_i)
        {
            std::cout << "tinyobj error: " << err_i.c_str() << std::endl;
            return -1;
        }
        
        for (const auto& shape : shapes_i)
        {
            for (auto face : shape.mesh.indices)
            {
                int vid_i = face.vertex_index;
                int nid_i = face.normal_index;
                    
                //fill in vertex buffer with vertex positions
                vbuffer_i.push_back(attrib_i.vertices[vid_i * 3]);//vertex vid's x
                vbuffer_i.push_back(attrib_i.vertices[vid_i * 3 + 1]);//vertex vid's y
                vbuffer_i.push_back(attrib_i.vertices[vid_i * 3 + 2]);//vertex vid's z
                
                //fill in normal buffer with normal directions
                nbuffer_i.push_back(attrib_i.normals[nid_i * 3]);
                nbuffer_i.push_back(attrib_i.normals[nid_i * 3 + 1]);
                nbuffer_i.push_back(attrib_i.normals[nid_i * 3 + 2]);
            }
        }
        
        //Blendshape operations
        while (getline(weight, tempWeight) && i == currentLineNum){
            currentLineNum++;
            //std::cout << "i：  "<<i << '\n';
            //std::cout << "temp_weight:  "<<tempWeight << '\n';
            break;
        }
        
        assert(vbuffer_new.size() == vbuffer_i.size());
        //std::cout<<vbuffer_ba.size();
        for(int j = 0; j < vbuffer_new.size(); j++)
        {
            vbuffer_new[j] = vbuffer_new[j] + (std::stof(tempWeight) * (vbuffer_i[j] - vbuffer_new[j])); //calculate by adding the previous offset value and the current offset
        }
        
        vbuffer_i.clear();
    }
    
    weight.close();
    
    return 0.0f;
}

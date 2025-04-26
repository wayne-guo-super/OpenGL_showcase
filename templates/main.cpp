#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

std::string obj_path_1 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/floor.obj";
std::string tex_path_1 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/floor.jpeg";

std::string obj_path_2 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/bucket.obj";
std::string tex_path_2 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/bucket.jpg";

std::string obj_path_3 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/timmy.obj";
std::string tex_path_3 = "/Users/wayne/Library/CloudStorage/OneDrive-McMasterUniversity/School Year/2023 Fall Term/COMPSCI 3GC3/Assignment 3/asset/timmy.png";


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "A3", NULL, NULL);
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
 
    //tiny object 1
    tinyobj::attrib_t attrib_1;
    std::vector<tinyobj::shape_t> shapes_1;
    std::vector<tinyobj::material_t> materials_1;
    // tinyobj load obj
    std::string warn_1, err_1;
    bool bTriangulate_1 = true;
    bool bSuc_1 = tinyobj::LoadObj(&attrib_1, &shapes_1, &materials_1, &warn_1, &err_1, obj_path_1.c_str(), nullptr, bTriangulate_1);
    if (!bSuc_1)
    {
        std::cout << "tinyobj error: " << err_1.c_str() << std::endl;
        return -1;
    }
    
    //tiny object 2
    tinyobj::attrib_t attrib_2;
    std::vector<tinyobj::shape_t> shapes_2;
    std::vector<tinyobj::material_t> materials_2;
    // tinyobj load obj
    std::string warn_2, err_2;
    bool bTriangulate_2 = true;
    bool bSuc_2 = tinyobj::LoadObj(&attrib_2, &shapes_2, &materials_2, &warn_2, &err_2, obj_path_2.c_str(), nullptr, bTriangulate_2);
    if (!bSuc_2)
    {
        std::cout << "tinyobj error: " << err_2.c_str() << std::endl;
        return -1;
    }
    
    //tiny object 3
    tinyobj::attrib_t attrib_3;
    std::vector<tinyobj::shape_t> shapes_3;
    std::vector<tinyobj::material_t> materials_3;
    // tinyobj load obj
    std::string warn_3, err_3;
    bool bTriangulate_3 = true;
    bool bSuc_3 = tinyobj::LoadObj(&attrib_3, &shapes_3, &materials_3, &warn_3, &err_3, obj_path_3.c_str(), nullptr, bTriangulate_3);
    if (!bSuc_3)
    {
        std::cout << "tinyobj error: " << err_3.c_str() << std::endl;
        return -1;
    }
 
    //load image, create texture and generate mipmaps
    int width_1, height_1, nrChannels_1;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data_1 = stbi_load(tex_path_1.c_str(), &width_1, &height_1, &nrChannels_1, 0);
    
    int width_2, height_2, nrChannels_2;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data_2 = stbi_load(tex_path_2.c_str(), &width_2, &height_2, &nrChannels_2, 0);
    
    int width_3, height_3, nrChannels_3;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data_3 = stbi_load(tex_path_3.c_str(), &width_3, &height_3, &nrChannels_3, 0);
 
    std::vector<float> vbuffer_1;
    std::vector<float> nbuffer_1;
    std::vector<float> tbuffer_1;
    
    std::vector<float> vbuffer_2;
    std::vector<float> nbuffer_2;
    std::vector<float> tbuffer_2;
    
    std::vector<float> vbuffer_3;
    std::vector<float> nbuffer_3;
    std::vector<float> tbuffer_3;
 
    //Buffer setting
    for (const auto& shape : shapes_1) {
        for (auto face : shape.mesh.indices)
        {
            int vid = face.vertex_index;
            int nid = face.normal_index;
            int tid = face.texcoord_index;
            //fill in vertex buffer with vertex positions
            vbuffer_1.push_back(attrib_1.vertices[vid * 3]);//vertex vid’s x
            vbuffer_1.push_back(attrib_1.vertices[vid * 3 + 1]);//vertex vid’s y
            vbuffer_1.push_back(attrib_1.vertices[vid * 3 + 2]);//vertex vid’s z
            //fill in normal buffer with normal directions
            nbuffer_1.push_back(attrib_1.normals[nid * 3]);
            nbuffer_1.push_back(attrib_1.normals[nid * 3 + 1]);
            nbuffer_1.push_back(attrib_1.normals[nid * 3 + 2]);
 
            tbuffer_1.push_back(attrib_1.texcoords[tid * 2]);
            tbuffer_1.push_back(attrib_1.texcoords[tid * 2 + 1]);
        }
    }
    
    for (const auto& shape : shapes_2) {
        for (auto face : shape.mesh.indices)
        {
            int vid = face.vertex_index;
            int nid = face.normal_index;
            int tid = face.texcoord_index;
            //fill in vertex buffer with vertex positions
            vbuffer_2.push_back(attrib_2.vertices[vid * 3]);//vertex vid’s x
            vbuffer_2.push_back(attrib_2.vertices[vid * 3 + 1]);//vertex vid’s y
            vbuffer_2.push_back(attrib_2.vertices[vid * 3 + 2]);//vertex vid’s z
            //fill in normal buffer with normal directions
            nbuffer_2.push_back(attrib_2.normals[nid * 3]);
            nbuffer_2.push_back(attrib_2.normals[nid * 3 + 1]);
            nbuffer_2.push_back(attrib_2.normals[nid * 3 + 2]);
 
            tbuffer_2.push_back(attrib_2.texcoords[tid * 2]);
            tbuffer_2.push_back(attrib_2.texcoords[tid * 2 + 1]);
        }
    }
    
    for (const auto& shape : shapes_3) {
        for (auto face : shape.mesh.indices)
        {
            int vid = face.vertex_index;
            int nid = face.normal_index;
            int tid = face.texcoord_index;
            //fill in vertex buffer with vertex positions
            vbuffer_3.push_back(attrib_3.vertices[vid * 3]);//vertex vid’s x
            vbuffer_3.push_back(attrib_3.vertices[vid * 3 + 1]);//vertex vid’s y
            vbuffer_3.push_back(attrib_3.vertices[vid * 3 + 2]);//vertex vid’s z
            //fill in normal buffer with normal directions
            nbuffer_3.push_back(attrib_3.normals[nid * 3]);
            nbuffer_3.push_back(attrib_3.normals[nid * 3 + 1]);
            nbuffer_3.push_back(attrib_3.normals[nid * 3 + 2]);
 
            tbuffer_3.push_back(attrib_3.texcoords[tid * 2]);
            tbuffer_3.push_back(attrib_3.texcoords[tid * 2 + 1]);
        }
    }
 
    //VAO and VBO
    unsigned int vertexVBO_1, normalVBO_1, textureVBO_1, VAO_1;
    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &vertexVBO_1);
    glGenBuffers(1, &normalVBO_1);
    glGenBuffers(1, &textureVBO_1);
 
 
    glBindVertexArray(VAO_1);
 
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_1);
    glBufferData(GL_ARRAY_BUFFER, vbuffer_1.size() * sizeof(float), &vbuffer_1[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO_1);
    glBufferData(GL_ARRAY_BUFFER, nbuffer_1.size() * sizeof(float), &nbuffer_1[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO_1);
    glBufferData(GL_ARRAY_BUFFER, tbuffer_1.size() * sizeof(float), &tbuffer_1[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int vertexVBO_2, normalVBO_2, textureVBO_2, VAO_2;
    glGenVertexArrays(1, &VAO_2);
    glGenBuffers(1, &vertexVBO_2);
    glGenBuffers(1, &normalVBO_2);
    glGenBuffers(1, &textureVBO_2);
 
 
    glBindVertexArray(VAO_2);
 
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_2);
    glBufferData(GL_ARRAY_BUFFER, vbuffer_2.size() * sizeof(float), &vbuffer_2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO_2);
    glBufferData(GL_ARRAY_BUFFER, nbuffer_2.size() * sizeof(float), &nbuffer_2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO_2);
    glBufferData(GL_ARRAY_BUFFER, tbuffer_2.size() * sizeof(float), &tbuffer_2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int vertexVBO_3, normalVBO_3, textureVBO_3, VAO_3;
    glGenVertexArrays(1, &VAO_3);
    glGenBuffers(1, &vertexVBO_3);
    glGenBuffers(1, &normalVBO_3);
    glGenBuffers(1, &textureVBO_3);
 
 
    glBindVertexArray(VAO_3);
 
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_3);
    glBufferData(GL_ARRAY_BUFFER, vbuffer_3.size() * sizeof(float), &vbuffer_3[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO_3);
    glBufferData(GL_ARRAY_BUFFER, nbuffer_3.size() * sizeof(float), &nbuffer_3[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO_3);
    glBufferData(GL_ARRAY_BUFFER, tbuffer_3.size() * sizeof(float), &tbuffer_3[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
 
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO_3);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    //Texture loading
    unsigned int textureT_1;
    glGenTextures(1, &textureT_1);
    glBindTexture(GL_TEXTURE_2D, textureT_1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_1, height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, data_1);//define the texture using image data
    stbi_image_free(data_1);//don’t forget to release the image data
    
    unsigned int textureT_2;
    glGenTextures(1, &textureT_2);
    glBindTexture(GL_TEXTURE_2D, textureT_2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_2, height_2, 0, GL_RGB, GL_UNSIGNED_BYTE, data_2);//define the texture using image data
    stbi_image_free(data_2);//don’t forget to release the image data
    
    unsigned int textureT_3;
    glGenTextures(1, &textureT_3);
    glBindTexture(GL_TEXTURE_2D, textureT_3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_3, height_3, 0, GL_RGB, GL_UNSIGNED_BYTE, data_3);//define the texture using image data
    stbi_image_free(data_3);//don’t forget to release the image data

 
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // ------------------------------------------------------------------------------------------
    
    ourShader.use();
    //ambient color
    ourShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    
    //diffuse color
    ourShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    /*
    ourShader.setVec3("light[0].diffuse", 1.0f, 0.0f, 0.0f);
    ourShader.setVec3("light[1].diffuse", 0.0f, 1.0f, 0.0f);
    ourShader.setVec3("light[2].diffuse", 0.0f, 0.0f, 1.0f);
     */
    
    //spot direction
    /*
    ourShader.setVec3("light[0].direction", 50.0f, -200.0f, -50.0f);
    ourShader.setVec3("light[1].direction", -50.0f, -200.0f, -50.0f);
    ourShader.setVec3("light[2].direction", 0.0f, -200.0f, -50.0f);
     */
    
    //kc, kl, kq
    ourShader.setFloat("kc", 1.0f);
    ourShader.setFloat("kl", 0.35 * 1e-4);
    ourShader.setFloat("kq", 0.44 * 1e-4);
 
    //position
    float theta = 0.0f;
    glm::vec3 lightPos(30.0f , -10.0f, -100.0f );
    
    ourShader.setVec3("light.position", lightPos);
    ourShader.setFloat("cutoff", cos(M_PI/6));
    
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
 
        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
 
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);
 
        view = glm::lookAt(glm::vec3(50, 100, 200), glm::vec3(0, 80, 0), glm::vec3(0, 1, 0));
        ourShader.setMat4("view", view);
 
        glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
        ourShader.setMat4("projection", proj);
        
        ourShader.use();
        
        //lighting
        //glm::vec3 lightPos(300.0f * sin(theta), -10.0f, -100.0f * cos(theta));
        //theta += 0.05f;
        //ourShader.setVec3("light.position", lightPos);
        
        // render boxes
            //obj1
        ourShader.setInt("myTexture", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureT_1);
        glBindVertexArray(VAO_1);
        //glDrawArrays(GL_TRIANGLES, 0, vbuffer_1.size() / 3);

            //obj2
        ourShader.setInt("myTexture", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureT_2);
        glBindVertexArray(VAO_2);
        //glDrawArrays(GL_TRIANGLES, 0, vbuffer_2.size() / 3);
        
            //obj3
        ourShader.setInt("myTexture", 2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureT_3);
        glBindVertexArray(VAO_3);
        glDrawArrays(GL_TRIANGLES, 0, vbuffer_3.size() / 3);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO_1);
    glDeleteBuffers(1, &vertexVBO_1);
    glDeleteBuffers(1, &normalVBO_1);
 
    glDeleteBuffers(1, &textureVBO_1);
    glDeleteTextures(1, &textureT_1);  // Added line
    
    glDeleteVertexArrays(1, &VAO_2);
    glDeleteBuffers(1, &vertexVBO_2);
    glDeleteBuffers(1, &normalVBO_2);
 
    glDeleteBuffers(1, &textureVBO_2);
    glDeleteTextures(1, &textureT_2);  // Added line
 
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

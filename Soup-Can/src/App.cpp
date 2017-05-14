#include "App.h"
#include <iostream>

namespace basicgraphics{

using namespace std;
using namespace glm;

App::App(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight) {

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    
    //TODO: Initialize the _mesh variable with a triangle mesh uploaded to the GPU.
//    vector<Mesh::Vertex> cpuVertexArray;
//    vector<int> cpuIndexArray;
//    vector<shared_ptr<Texture>> textures;
//    shared_ptr<Texture> tex = Texture::create2DTextureFromFile("tex.jpg");
//    textures.push_back(tex);
    
    
    //Sphere(const glm::vec3 &position, const float radius, const glm::vec4 &color);
    
//    Mesh::Vertex vert;
//    vert.position = vec3(0,0,0);
//    vert.normal = vec3(0,0,1);
//    vert.texCoord0 = glm::vec2(0, 0);
//    cpuVertexArray.push_back(vert);
//    cpuIndexArray.push_back(0);
//    
//    vert.position = vec3(0,15,0);
//    cpuVertexArray.push_back(vert);
//    cpuIndexArray.push_back(1);
//    
//    vert.position = vec3(15,15,0);
//    cpuVertexArray.push_back(vert);
//    cpuIndexArray.push_back(2);

    
//    Mesh::Vertex vert;
//    vert.position = vec3(0,0,0);
//    vert.normal = vec3(0,0,1);
//    vert.texCoord0 = glm::vec2(0,0);
//    cpuVertexArray.push_back(vert);
//    cpuIndexArray.push_back(0);
//    
//    for(int i = 0; i <= 100; i++){
//        vert.position = vec3(cos(i * 2.0f * 3.1415/100), sin(i * 2.0f * 3.1415 / 100), 0);
//        vert.normal = vec3(0,0,1);
//        vert.texCoord0 = glm::vec2(vert.position.x, vert.position.y);
//        cpuVertexArray.push_back(vert);
//        cpuIndexArray.push_back(i+1);
//    }
    
    
    vector<Mesh::Vertex> topCircleVertexArray;
    vector<int> topCircleIndexArray;
    vector<Mesh::Vertex> bottomCircleVertexArray;
    vector<int> bottomCircleIndexArray;
    vector<Mesh::Vertex> canVertexArray;
    vector<int> canIndexArray;
    vector<shared_ptr<Texture>> textures;
    shared_ptr<Texture> tex = Texture::create2DTextureFromFile("campbells.jpg");
    textures.push_back(tex);
    
    Mesh::Vertex topVert;
    topVert.position = vec3(0,1,0);
    topVert.normal = vec3(0,1,0);
    topVert.texCoord0 = glm::vec2(0, 1);
    topCircleVertexArray.push_back(topVert);
    topCircleIndexArray.push_back(0);
    
    Mesh::Vertex bottomVert;
    bottomVert.position = vec3(0,-1,0);
    bottomVert.normal = vec3(0,-1,0);
    bottomVert.texCoord0 = glm::vec2(0, 1);
    bottomCircleVertexArray.push_back(bottomVert);
    bottomCircleIndexArray.push_back(0);
    
    Mesh::Vertex canVert;
    canVert.position = vec3(.5*cos(0 * 2.0f * 3.1415 / 100), 1, .5*sin(0 * 2.0f * 3.1415/100));
    canVert.normal = vec3(1,0,0);
    canVert.texCoord0 = glm::vec2(0, 1);
    canVertexArray.push_back(canVert);
    canIndexArray.push_back(0);
    
    for(int i = 0; i<=100; i++){
        //topVert.position = vec3(.5*cos(i * 2.0f * 3.1415/100), 1, .5*sin(i * 2.0f * 3.1415 / 100));
        //bottomVert.position = vec3(cos(i * 2.0f * 3.1415/100), -1, sin(i * 2.0f * 3.1415 / 100));
        topVert.position = vec3(.5*cos(i * 2.0f * 3.1415 / 100), 1, .5*sin(i * 2.0f * 3.1415/100));
        bottomVert.position = vec3(.5*sin(i * 2.0f * 3.1415 / 100), -1, .5*cos(i * 2.0f * 3.1415/100));
        
        
        topVert.texCoord0 = glm::vec2(topVert.position.x, topVert.position.z);
        bottomVert.texCoord0 = glm::vec2(bottomVert.position.z, bottomVert.position.x);
        
        topCircleVertexArray.push_back(topVert);
        topCircleIndexArray.push_back(i+1);
        bottomCircleVertexArray.push_back(bottomVert);
        bottomCircleIndexArray.push_back(i+1);
        
        float incre = i >= 75? float(i)/100 : float(75 - i)/100;  // offset for the tex-cord mapping
        //std::cout << incre << std::endl;
        //canVert.texCoord0 = glm::vec2(float(100-i)/100, 0);
        canVert.position = topVert.position;
        
        canVert.texCoord0 = glm::vec2(incre, 0);
        canVert.normal = glm::normalize(vec3(canVert.position.x, 0, canVert.position.z));
        canVertexArray.push_back(canVert);
        canIndexArray.push_back(2*i);
        
        canVert.position.y = -topVert.position.y;
        canVert.texCoord0 = glm::vec2(incre, 1);
        canVertexArray.push_back(canVert);
        canIndexArray.push_back(2*i+1);
    }

    const int numVertices = topCircleVertexArray.size();
    const int CircleVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int CircleIndexByteSize = sizeof(int) * topCircleIndexArray.size();
    
    const int numCanVertices = canVertexArray.size();
    const int canVertexByteSize = sizeof(Mesh::Vertex) * numCanVertices;
    const int canIndexByteSize = sizeof(int) * canIndexArray.size();
   
    _meshTop.reset(new Mesh(textures, GL_TRIANGLE_FAN, GL_STATIC_DRAW,
                         CircleVertexByteSize, CircleIndexByteSize, 0, topCircleVertexArray,
                         topCircleIndexArray.size(), CircleIndexByteSize, &topCircleIndexArray[0]));
    
    _meshBottom.reset(new Mesh(textures, GL_TRIANGLE_FAN, GL_STATIC_DRAW,
                         CircleVertexByteSize, CircleIndexByteSize, 0, bottomCircleVertexArray,
                         bottomCircleIndexArray.size(), CircleIndexByteSize, &bottomCircleIndexArray[0]));
    
    _meshCan.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW,
                               canVertexByteSize, canIndexByteSize, 0, canVertexArray,
                               canIndexArray.size(), canIndexByteSize, &canIndexArray[0]));

}
    
    
    

void App::onEvent(shared_ptr<Event> event)
{
}

void App::onRenderGraphics() {
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_NONE);
    vec3 eye_world(0,0,5);
    // Setup the camera with a good initial position and view direction to see the table
    glm::mat4 view = glm::lookAt(eye_world, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    
    // Setup the projection matrix so that things are rendered in perspective
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.1f, 100.0f);
    
    // Setup the model matrix
    glm::mat4 model(1.0);
    
    // Update shader variables
    _shader.setUniform("view_mat", view);
    _shader.setUniform("projection_mat", projection);
    _shader.setUniform("model_mat", model);
    _shader.setUniform("eye_world", eye_world);

	// Draw the mesh
	_meshTop->draw(_shader);
    _meshBottom->draw(_shader);
    _meshCan->draw(_shader);
}
}//namespace





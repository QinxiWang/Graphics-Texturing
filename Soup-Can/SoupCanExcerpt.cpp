std::vector<Mesh::Vertex> cpuVertexArray;
    std::vector<int>			 cpuIndexArray;
    std::vector<std::shared_ptr<Texture>> textures;
    
    
    Mesh::Vertex vert;
    vert.position = vec3(0,1,0);
    vert.normal = vec3(0,1,0);
    vert.texCoord0 = glm::vec2(0.43, 0.5);
    cpuVertexArray.push_back(vert);
    
    int numslices = 60;
    float r = 0.75;
    
    // Draw top
    for (int slice=0; slice<numslices; slice++) {
        float theta = (float)slice/(float)numslices * 2.0f * pi<float>();
        vec3 p(r*sin(theta), 1.0, r*cos(theta));
        vert.position = p;
        vert.texCoord0 = vec2(0,1);//sin(theta)/2.0+0.5, cos(theta)/2.0+0.5);
        cpuVertexArray.push_back(vert);
        
        if (slice > 0) {
            // add a triangle
            cpuIndexArray.push_back(0);
            cpuIndexArray.push_back(slice+1);
            cpuIndexArray.push_back(slice);
            
        }
    }
    // Add the last triangle connecting to the first vertex
    cpuIndexArray.push_back(0);
    cpuIndexArray.push_back(cpuVertexArray.size()-1);
    cpuIndexArray.push_back(1);
    
    
    int first = cpuVertexArray.size();
    //Draw bottom
    vert.position = vec3(0,-1,0);
    vert.normal = vec3(0,-1,0);
    vert.texCoord0 = vec2(0.43, 0.5);
    cpuVertexArray.push_back(vert);
    for (int slice=0; slice<numslices; slice++) {
        float theta = (float)slice/(float)numslices * 2.0 * pi<float>();
        vert.position = vec3(r*cos(theta), -1.0, r*sin(theta));
        vert.texCoord0 = vec2(0, 1);
        cpuVertexArray.push_back(vert);
        
        if (slice > 0) {
            // add a triangle
            cpuIndexArray.push_back(first);
            cpuIndexArray.push_back(first+slice);
            cpuIndexArray.push_back(first+slice+1);
        }
    }
    // Add the last triangle connecting to the first vertex
    cpuIndexArray.push_back(first);
    cpuIndexArray.push_back(cpuVertexArray.size()-1);
    cpuIndexArray.push_back(first+1);
    
    first = cpuVertexArray.size();
    // Make connections between top and bottom
    for (int slice=0; slice<=numslices; slice++) {
        float theta = (float)slice/(float)numslices * 2.0f * pi<float>() + pi<float>(); // Add pi to rotate the texture around. Could also have just modified the texture coordinates
        vec3 normal(r*sin(theta), 0.0, r*cos(theta));
        normal = normalize(normal);
        vert.normal = normal;
        vec3 pTop(r*sin(theta), 1.0, r*cos(theta));
        vert.position = pTop;
        float textureCoord = (float)slice/(float)numslices;
        vert.texCoord0 = vec2(textureCoord, 0);
        cpuVertexArray.push_back(vert);
        
        
        vec3 pBottom(r*sin(theta), -1.0, r*cos(theta));
        vert.position = pBottom;
        vert.texCoord0 = vec2(textureCoord, 1.0);
        cpuVertexArray.push_back(vert);
        
        if (slice > 0) {
            // add a triangle
            cpuIndexArray.push_back(first+(slice*2)+1);
            cpuIndexArray.push_back(first+(slice*2));
            cpuIndexArray.push_back(first+(slice*2)-2);
            
            cpuIndexArray.push_back(first+(slice*2)+1);
            cpuIndexArray.push_back(first+(slice*2)-2);
            cpuIndexArray.push_back(first+(slice*2)-1);
            
        }
    }

    
    std::shared_ptr<Texture> tex = Texture::create2DTextureFromFile("campbells.jpg");
    textures.push_back(tex);
    
    const int numVertices = cpuVertexArray.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
    _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray, cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
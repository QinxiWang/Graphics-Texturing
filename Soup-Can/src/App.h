#ifndef App_h
#define App_h

#include "BaseApp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace basicgraphics {
public:
  
    App(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
    ~App(){};
  
    void onRenderGraphics() override;
    void onEvent(std::shared_ptr<Event> event) override;

  
protected:
    
    std::unique_ptr<Mesh> _meshTop;
    std::unique_ptr<Mesh> _meshBottom;
    std::unique_ptr<Mesh> _meshCan;
      
}
#endif

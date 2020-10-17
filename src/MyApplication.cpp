#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Corrade/Utility/DebugStl.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Shaders/VertexColor.h>

using namespace Magnum;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void drawEvent() override;
        GL::Mesh _mesh;
        Shaders::VertexColor2D _shader;
};

MyApplication::MyApplication(const Arguments& arguments): 
    Platform::Application{arguments, Configuration{}.setTitle("Magnum Triangle Example")} {
    /* TODO: Add your initialization code here */
    using namespace Math::Literals;
    struct TriangleVertex {
        Vector2 position;
        Color3 color;
    };
    const TriangleVertex data[]{
        {{-0.5f,-0.5f},0xff0000_rgbf},
        {{ 0.5f, -0.5f}, 0x00ff00_rgbf},
        {{ 0.0f,  0.5f}, 0x0000ff_rgbf} 
    };
     GL::Buffer buffer;
    buffer.setData(data);
    
    _mesh.setCount(3)
         .addVertexBuffer(std::move(buffer), 0,
            Shaders::VertexColor2D::Position{},
            Shaders::VertexColor2D::Color3{});

    Debug{} << "Hello! This application is running on"
            << GL::Context::current().version() << "using"
            << GL::Context::current().rendererString();
}

void MyApplication::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    /* TODO: Add your drawing code here */

    _shader.draw(_mesh);

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)

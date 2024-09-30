
#include "WorldRenderer.hpp"

#include "Model.hpp"

#include <glad/glad.h>
// #include <GLFW/glfw3.h>


#include "WorldObject.hpp"
// #include "simulator.hpp"
#include "WorldScene.hpp"

#include "shader.hpp"

#include "bmp_loader.hpp"

#include "Simulation.hpp"

#include "Camera.hpp"

// WORLD OBJECT CLASSES
#include "SimWorldContainer.hpp"




extern WorldObject worldGround1;

extern WorldObject worldCube1;
extern WorldObject worldCube_spin;

extern WorldObject worldTriangle1Texture;
extern WorldObject worldTriangle2_bounce;


extern unsigned int mountainTexture;

Shader worldShader;
unsigned int transformLoc;
unsigned int viewLoc;
unsigned int sanityLoc;
unsigned int perspectiveLoc;
unsigned int colorLoc;
unsigned int hasTextureLoc;

Shader worldObjShader;
unsigned int modelObjLoc;
unsigned int viewObjLoc;
unsigned int sanityObjLoc;
unsigned int perspectiveObjLoc;

Shader wireframeShader;
unsigned int modelWireLoc;
unsigned int viewWireLoc;
unsigned int sanityWireLoc;
unsigned int perspectiveWireLoc;

// NEW GROUND


const float sanityMatrix16[16] = {
    0, -1, 0, 0,
    0, 0, 1, 0,
    -1, 0, 0, 0,
    0, 0, 0, 1,
};





// TEMP SIMULATION UPDATER
extern SimState simState;
void update_sim_timestep(){
    
}


// unsigned int transformLoc_;

void wr_init(){

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // shader_init_shaders();

    worldShader.buildShaderProgram("resources/shaders/worldShader.vs", "resources/shaders/worldShader.fs");

    glUseProgram(worldShader.ID);
    transformLoc = glGetUniformLocation(worldShader.ID, "transform");
    viewLoc = glGetUniformLocation(worldShader.ID, "view");
    sanityLoc = glGetUniformLocation(worldShader.ID, "sanityTransform");
    perspectiveLoc = glGetUniformLocation(worldShader.ID, "perspective");
    colorLoc = glGetUniformLocation(worldShader.ID, "vertexColor");
    hasTextureLoc = glGetUniformLocation(worldShader.ID, "hasTexture");

    glUniformMatrix4fv(sanityLoc, 1, GL_TRUE, sanityMatrix16);
    glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, cam_getViewMatrix());



    worldObjShader.buildShaderProgram("resources/shaders/worldObjShader_vs.glsl", "resources/shaders/worldObjShader_fs.glsl");

    glUseProgram(worldObjShader.ID);
    modelObjLoc = glGetUniformLocation(worldObjShader.ID, "model");
    viewObjLoc = glGetUniformLocation(worldObjShader.ID, "view");
    sanityObjLoc = glGetUniformLocation(worldObjShader.ID, "sanityTransform");
    perspectiveObjLoc = glGetUniformLocation(worldObjShader.ID, "perspective");
    // colorObjLoc = glGetUniformLocation(worldObjShader.ID, "vertexColor");
    // hasTextureObjLoc = glGetUniformLocation(worldObjShader.ID, "hasTexture");

    glUniformMatrix4fv(sanityObjLoc, 1, GL_TRUE, sanityMatrix16);
    glUniformMatrix4fv(perspectiveObjLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewObjLoc, 1, GL_TRUE, cam_getViewMatrix());

    
    wireframeShader.buildShaderProgram("resources/shaders/worldWireframeShader_vs.glsl", "resources/shaders/worldWireframeShader_fs.glsl");

    glUseProgram(wireframeShader.ID);
    modelWireLoc = glGetUniformLocation(wireframeShader.ID, "model");
    viewWireLoc = glGetUniformLocation(wireframeShader.ID, "view");
    sanityWireLoc = glGetUniformLocation(wireframeShader.ID, "sanityTransform");
    perspectiveWireLoc = glGetUniformLocation(wireframeShader.ID, "perspective");

    glUniformMatrix4fv(sanityWireLoc, 1, GL_TRUE, sanityMatrix16);
    glUniformMatrix4fv(perspectiveWireLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewWireLoc, 1, GL_TRUE, cam_getViewMatrix());
}



void wr_render(std::vector<WorldObject*> _worldObjects) {
    // glUseProgram(worldShader.ID);
    
    // glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    // glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    // glUniformMatrix4fv(viewLoc, 1, GL_TRUE, cam_getViewMatrix());




    // RENDER WORLD OBJECTS !
    for(WorldObject* _worldObject_p : _worldObjects){
        WorldObject& _worldObject = *_worldObject_p;
        // std::cout << "_worldObject.name = " << _worldObject.name << std::endl;
        
        if(!_worldObject.isActive){
            continue;
        }

        // // make sure the object is not rendered this way, occationally causes segfaults
        // if (_worldObject.name == "rendpipe_obj"){
        //     continue;
        // }


        /* 

            USING NEW RENDERER
        
        */
        // Try RTTI determination
        // WorldObject* _worldObject_ptr = &_worldObject;
        // try
        // {
        //     SimWorldContainer* sim = dynamic_cast<SimWorldContainer*>(&_worldObject);
        //     std::cout << "" << sim << std::endl;
            
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }

        // SimWorldContainer* sim_2 = dynamic_cast<SimWorldContainer*>(&_worldObject)
            
        // std::cout << "sim_2 = " << &sim_2 << std::endl;
        
        // std::cout << "&_worldObject = s" << &_worldObject << std::endl;
        
        // if (SimWorldContainer* sim_2 = dynamic_cast<SimWorldContainer*>(&_worldObject))
        //     std::cout << "RTTI WORKS!!!!!!" << std::endl;
        
        // std::cout << "YELLO"  << std::endl;
        
            
        if (_worldObject.name == "simContainer_1"){
            
            wr_renderSimContainer(*_worldObject_p);
            
            SimWorldContainer* container = static_cast<SimWorldContainer*>(_worldObject_p);

            // container->render();

            // SimWorldContainer& cont = *container;
            // std::cout << "container->simulator->simtype = " << container->simulator->simtype << std::endl;
            // std::cout << "container->simulator->nextTimeStep()->t = " << container->simulator->nextTimeStep()->t << std::endl;

            for (WorldObject& _wo : container->containerWorldObjects){
                // std::cout << "_wo.name = " << _wo.name << std::endl;

                Sim::TimeStep& _timeStep = *container->simulator->nextTimeStep();
                int sim_x = _timeStep.pos.x;
                int sim_y = _timeStep.pos.y;
                int sim_z = _timeStep.pos.z;

                // Assumes that the object being used in the simulator is zero-centered
                // Move object into sim-container, then shift according to simulator scale
                _wo.position.x = _wo.position_0.x + sim_x * container->simulationScale + container->position.x;
                _wo.position.y = _wo.position_0.x + sim_y * container->simulationScale + container->position.y;
                _wo.position.z = _wo.position_0.x + sim_z * container->simulationScale + container->position.z;

                // Scale the simulation realtive to container z-dimension + use Z
                _wo.scale.x = container->scale.z * container->simulationScale;
                _wo.scale.y = container->scale.z * container->simulationScale;
                _wo.scale.z = container->scale.z * container->simulationScale;

                glBindVertexArray(_wo.vao);
                _wo.SetModelMatrixRowMajor();

                wr_renderWorldShader(_wo);
                // wr_renderWorldObjShader(_wo);

            }
            
            // if (SimWorldContainer* container = dynamic_cast<SimWorldContainer*>(&_worldObject)) {
            //     std::cout << "1" << std::endl;
                
            // }
            
            // TODO : ACCESS AND RENDER THE SIM CONTAINER OBJECTS....

            // Force a sim container!
            // _worldObject* b2 = new SimWorldContainer;
            // SimWorldContainer& new_d = dynamic_cast<SimWorldContainer&>(_worldObject);
            // std::cout << "lfasjdfkasdhf kjshdka" << std::endl;


            // https://en.cppreference.com/w/cpp/language/static_cast
            // void * simContObj = &_worldObject;

            // SimWorldContainer& xx = 
            
            // SimWorldContainer& another_d = static_cast<SimWorldContainer&>(_worldObject);
            // No success...
            // std::cout << "lfasjdfkasdhf kjshdka" << std::endl;
            // std::cout << "another_d.containerWorldObjects.size() = " << another_d.containerWorldObjects.size() << std::endl;
            
            // for (WorldObject& _simContainerWorldObject : another_d.containerWorldObjects){
            //     std::cout << "lfasjdfkasdhf kjshdka"  << std::endl;
                
            //     wr_renderWorldObjShader(_simContainerWorldObject);
            // }

            continue;
        }
        


        
        _worldObject.shader->use();


        // Add wireframe
        if(_worldObject.hasRigidBody){

            wr_renderWireframeShader(_worldObject);
           
        }


        glBindVertexArray(_worldObject.vao);
        _worldObject.SetModelMatrixRowMajor();

        
        // WORLD SHADER
        if(_worldObject.shader->ID == worldShader.ID){
            wr_renderWorldShader(_worldObject);
            
        }
        // WORLD OBJ SHADER
        else if(_worldObject.shader->ID == worldObjShader.ID){
            // std::cout << "WORLD OBJ SHADER" << std::endl;

            wr_renderWorldObjShader(_worldObject);

            
        }

    }

}

void wr_renderWorldShader(WorldObject& _worldObject){

    _worldObject.shader->use();

    glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, cam_getViewMatrix());
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, _worldObject.modelMatrixRowMajor);

    if (_worldObject.hasTexture) {
        glUniform1i(hasTextureLoc, 1); // set texture bool
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _worldObject.glTexture);
    }
    else {
        glUniform1i(hasTextureLoc, 0); // unset texture bool
    }

    glDrawArrays(GL_TRIANGLES, 0, _worldObject.vertexCount);

    glUniform1i(hasTextureLoc, 0);

}


void wr_renderWorldObjShader(WorldObject& _worldObject){

    _worldObject.shader->use();

    glUniformMatrix4fv(perspectiveObjLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewObjLoc, 1, GL_TRUE, cam_getViewMatrix());
    glUniformMatrix4fv(modelObjLoc, 1, GL_TRUE, _worldObject.modelMatrixRowMajor);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _worldObject.model.glTexture);
    // if (_worldObject.hasTexture) {
    //     glUniform1i(hasTextureObjLoc, 1); // set texture bool

    // }
    // else {
    //     glUniform1i(hasTextureObjLoc, 0); // unset texture bool
    // }

    glDrawArrays(GL_TRIANGLES, 0, _worldObject.model.vertexCount);
    // std::cout << "_worldObject.name = " << _worldObject.name << std::endl;
    // std::cout << "_worldObject.model.glTexture = " << _worldObject.model.glTexture << std::endl;
    // std::cout << "_worldObject.model.vertexCount = " << _worldObject.model.vertexCount << std::endl;
    // std::cout << "_worldObject.model.vertices.size() = " << _worldObject.model.vertices.size() << std::endl;


    // glUniform1i(hasTextureObjLoc, 0);

}



void wr_renderWireframeShader(WorldObject& _worldObject){
    // std::cout << _worldObject.name << " : HAS WIREFRAME" << std::endl;
    _worldObject.rigidBody.shader->use();
    glUniformMatrix4fv(perspectiveWireLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewWireLoc, 1, GL_TRUE, cam_getViewMatrix());
    glUniformMatrix4fv(modelWireLoc, 1, GL_TRUE, _worldObject.modelMatrixRowMajor);
    glBindVertexArray(_worldObject.rigidBody.vao);
    glDrawArrays(GL_LINES, 0, _worldObject.rigidBody.vertices.size() / 3);
}


void wr_renderSimContainer(WorldObject& _worldObject){
    // std::cout << _worldObject.name << " : HAS WIREFRAME" << std::endl;

    _worldObject.renderer.shader->use();
    glBindVertexArray(_worldObject.renderer.vao);

    _worldObject.SetModelMatrixRowMajor();

    glUniformMatrix4fv(perspectiveWireLoc, 1, GL_TRUE, cam_getPerspectiveMatrix());
    glUniformMatrix4fv(viewWireLoc, 1, GL_TRUE, cam_getViewMatrix());
    glUniformMatrix4fv(modelWireLoc, 1, GL_TRUE, _worldObject.modelMatrixRowMajor);
    glBindVertexArray(_worldObject.renderer.vao);
    glDrawArrays(GL_LINES, 0, _worldObject.vertices.size() / 3);
}















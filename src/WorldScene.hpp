#ifndef WORLD_SCENE_HPP
#define WORLD_SCENE_HPP

#include <vector>

#include "WorldObject.hpp"


void ws_init();

void ws_createSimulators();

void ws_createWorldObjects();
void ws_resetWorldObjects();

std::vector<WorldObject*> ws_getWorldObjects();

void ws_loadTextures();

void ws_physics();
int worldObjectCollidingWithGround_aabb_z(WorldObject& ground, WorldObject& wo2);

void ws_update();

void ws_update_objects();
void ws_render();



#endif
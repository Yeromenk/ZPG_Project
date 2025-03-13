# ZPG (Základy počítačové grafiky) - OpenGL 3D Game Engine

## Project Overview

This project is a 3D game engine developed in C++ using OpenGL as part of the ZPG course. The engine implements various computer graphics concepts to create an interactive 3D environment.

## Core Technologies and Techniques

- **OpenGL** - Core graphics API for rendering
- **GLSL** - Shader programming for vertex and fragment shaders
- **SOIL** - Simple OpenGL Image Library for texture loading
- **Assimp** - Open Asset Import Library for 3D model loading
- **GLM** - OpenGL Mathematics library for vector/matrix operations

## Key Features Implemented

### Rendering System
- 3D model loading and rendering via Assimp
- Shader-based rendering pipeline with customizable shader programs
- Support for different drawing modes (GL_TRIANGLES, etc.)

### Lighting
- Multiple light types supported through Light base class
- Directional light implementation
- Light intensity and color management
- Observer pattern for light updates

### Materials
- Material system with ambient, diffuse, and specular components
- Material properties for realistic object appearance

### Camera System
- First-person camera controls
- Camera movement (forward, backward, left, right)
- Mouse-based look controls with pitch and yaw
- View and projection matrix management

### Scene Management
- Scene graph for organizing 3D objects
- Special object handling (rotating trees, random bush movement)
- Skybox implementation

### Texturing
- 2D texture support for models
- Cubemap support for skyboxes
- Texture unit management

### Transformations
- Object transformations (translation, rotation, scaling)
- Model, view, and projection matrix management
- Normal matrix calculations for lighting

## Architecture

The project follows an object-oriented architecture with DrawableObject as the base class for all renderable objects, and specialized classes for models, lights, materials, and scene management.

## Advanced Techniques

- Observer pattern for updating components when changes occur
- Dynamic shader uniform management
- Normal matrix calculation for correct lighting
- Seamless cubemap for skybox environments
- Dynamic scene management with specialized object behaviors

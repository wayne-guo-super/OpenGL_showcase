# About
This project is a showcase created for the 3GC3 [Computer Graphics](https://www.opengl.org) course.  
It utilizes **OpenGL** and **C++** to generate models, set up ambient and directional lighting, and implement animated visual effects.

# Features
- Procedural model generation
- Object placement and transformation
- Ambient and directional lighting
- Real-time rendering with OpenGL
- Basic user interactions (where applicable)
- Object animations

# Images
### Scene Preview
![Scene at Disco](/asset/images/at_disco.jpg)

# Requirements
- C++
- [OpenGL](https://www.opengl.org)
- [glad](https://github.com/Dav1dde/glad) (OpenGL function loader)
- [glm](https://github.com/g-truc/glm) (Math library for OpenGL)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) (OBJ model loader)

# Structure & Usage
- The template includes the basic setup for the scene, including vertex shaders, fragment shaders, object loaders, and more.
- To switch scenes, replace the `main` function in the template with the corresponding version from the `scene_variants` folder.
- Some `scene_variants` may also include custom shaders, which can be swapped into the template as needed.
- Each assignment folder contains some demo images for reference.

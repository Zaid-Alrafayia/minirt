***This project has been created as part of the 42 curriculum by jalghamd & zaalrafa***

# miniRT

## Description
**miniRT** is a minimalist Ray Tracing rendering engine developed in C for the 42 school curriculum using the MiniLibX graphical library. The goal of this project is to explore computer graphics fundamentals, vector mathematics, light physics simulation, and 3D surface mapping algorithms.


## Features

### Mandatory Part
- **Primitives**: Support for Spheres (`sp`), Planes (`pl`), and finite Capped Cylinders (`cy`).
- **Camera System**: Configurable camera position, direction vector, and Field of View (FOV).
- **Lighting & Shading**:
  - Ambient lighting with configurable brightness ratio and color.
  - Point light source with diffuse illumination (Lambertian shading).
  - Hard shadows calculated via shadow rays.
  - Proper normal orientation for inside and outside surface rendering.
- **Window Management**: Smooth window creation, event hooks for graceful termination (`ESC` key or window close button `X`), and image buffer rendering.
- **Parsing**: Robust `.rt` file validation, error handling, and complete memory leak prevention.


### Bonus Part
- **Additional Primitive**: Finite Cone (`co`) with base cap mapping.
- **Advanced Lighting**:
  - Specular highlights based on the **Phong Reflection Model**.
  - **Multi-spot Lighting**: Multiple light sources casting overlapping shadows.
- **Textures & Surface Mapping**:
  - **Procedural Pattern**: Customizable Checkerboard pattern (`checked`) for all object types.
  - **XPM Textures**: Surface texture mapping with **Bilinear Interpolation** filtering for smooth rendering.
  - **Bump Mapping**: Normal map simulation using height maps to render realistic surface relief and micro-details.
  - **Cap Mapping**: Seamless UV mapping on planar caps for Cylinders and Cones.

## Technical Specifications & Math
- **Ray-Primitive Intersection**: Analytical quadratic equation solving ($\Delta = B^2 - 4AC$) for spheres, cylinders, and cones, and planar ray-plane intersections.
- **UV Coordinates Calculation**:
  - Spherical UV mapping: $u = 0.5 + \frac{\text{atan2}(x, -z)}{2\pi}$, $v = 0.5 + \frac{\text{asin}(y)}{\pi}$.
  - Planar & Cap mapping: Projected tangent-bitangent 2D coordinate system.
  - Cylindrical & Conical UV mapping: Azimuthal angle around axis and normalized height ratio.
- **TBN Space**: Tangent, Bitangent, Normal coordinate system for applying normal perturbation in Bump Mapping.

## Instructions 

### Compilation and Usage

### Prerequisites
- GCC / Clang compiler
- `make`
- X11 graphics libraries (`libXext`, `libX11`, `libm`)

### Building the Project

To build the **mandatory** version:
```bash
make
```

To build the **bonus** version:
```bash
make bonus
```

To clean object files and executables:
```bash
make fclean
```

### Running Scenes

**Mandatory:**
```bash
./miniRT scenes/mandatory/sphere.rt
```

**Bonus:**
```bash
./miniRT_bonus scenes/bonus/chess.rt
```


## Scene File Format (`.rt`)

Scene files define elements line-by-line separated by spaces:

```rt
# Ambient Light: A [ratio in 0.0,1.0] [R,G,B]
A 0.2 255,255,255

# Camera: C [x,y,z] [dir_x,dir_y,dir_z] [FOV in 0,180]
C 0,3,-12 0,-0.05,1 70

# Light: L [x,y,z] [brightness in 0.0,1.0] [R,G,B]
L -8,12,-4 0.8 255,255,255

# Plane: pl [x,y,z] [normal_x,y,z] [R,G,B] [texture/checked optional]
pl 0,0,0 0,1,0 70,140,60

# Sphere: sp [x,y,z] [diameter] [R,G,B] [texture/checked optional]
sp 0,0.5,2.78 0.6 80,40,20

# Cylinder: cy [x,y,z] [axis_x,y,z] [diameter] [height] [R,G,B] [texture/checked optional]
cy 0,1,4 0,1,0 2.4 2.0 240,230,210 textures/marble.xpm

# Cone (Bonus): co [x,y,z] [axis_x,y,z] [diameter] [height] [R,G,B] [texture/checked optional]
co 0,2.8,4 0,-1,0 3.0 1.6 180,50,40 textures/red.xpm
```

## Controls
- **`ESC` / Window `X` button**: Safely exit the program and free all allocated memory resources.


## Resources & AI Usage

### References
1. [Ray Tracing in One Weekend Series](https://raytracing.github.io/)
2. [Scratchapixel](https://www.scratchapixel.com/)
3. [Phong Reflection Model](https://en.wikipedia.org/wiki/Phong_reflection_model)
4. [Ray Tracing Graphics](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
5. [Graphics Pipeline](https://en.wikipedia.org/wiki/Graphics_pipeline)
6. [MiniRT: mini Ray Tracer (a 42 The Network Graphical Project)](https://m4nnb3ll.medium.com/minirt-mini-ray-tracer-a-42-the-network-graphical-project-d909bef10025)
7. [Computer Graphics From Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/)
8. [A Pixel Is Not A Little Square](https://www.researchgate.net/publication/244986797_A_Pixel_Is_Not_A_Little_Square_A_Pixel_Is_Not_A_Little_Square_A_Pixel_Is_Not_A_Little_Square)
9. [Ray Tracing Noise](https://stackoverflow.com/questions/23417736/ray-tracing-noise)
10. [Some guy explaining his work :)](https://www.fredcharbonnier.com/projects/minirt)
11. [Mathematics Behind miniRT](https://medium.com/@mansurimohamad92/the-mathematics-behind-the-minirt-42-project-a-comprehensive-exploration-213e149c85d8)
12. [another medium article](https://medium.com/@iremoztimur/building-a-minirt-42-project-part-1-ae7a00aebdb9)
13. [for Normal Mapping theory and TBN matrix calculations](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)
14. [Bump Mapping](https://en.wikipedia.org/wiki/Bump_mapping)
15. [Pixel drawing with the minilibx](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx#finding-the-pixels-first-bytes-address)

### AI Usage
- Acted as a learning roadmap to structure the development phases sequentially
- Helped demystify complex 3D graphics and linear algebra concepts by grounding them in real-world physical analogies
- Assisted in refactoring long or complex functions into smaller, modular sub-functions to strictly adhere to the 42 Norm guidelines without compromising readability or logic

# miniRT Progress and Work Plan

## Current status

The project currently has the initial mandatory-project foundation in place.
The build succeeds with `make`, and the program can open a MiniLibX window after
reading a `.rt` scene file.

Estimated progress:

- Mandatory project: approximately **15-20%**
- Bonus project: **0%**

This estimate is based on the required functionality, not on the number of
source lines. The central ray-tracing and rendering work is still remaining.

## Work completed

### Project setup

- [x] Makefile exists and builds `miniRT`.
- [x] `42_libft` is linked.
- [x] MiniLibX is linked.
- [x] Math and X11 libraries are linked.
- [x] Mandatory and bonus structure headers have been started.

### Program startup and validation

- [x] Checks the number of command-line arguments.
- [x] Checks that the scene filename ends in `.rt`.
- [x] Checks that the file exists and can be opened.
- [x] Rejects empty or unreadable files.

### Scene parsing

The parser currently recognizes:

- [x] `A` ambient lighting
- [x] `C` camera
- [x] `L` light
- [x] `sp` sphere
- [x] `pl` plane
- [x] `cy` cylinder

It also has initial support for:

- [x] Parsing floating-point values.
- [x] Parsing vectors in `x,y,z` form.
- [x] Parsing colors in `R,G,B` form.
- [x] Allocating scene objects.
- [x] Cleaning object and light lists.
- [x] Cleaning remaining `get_next_line` data on an early parse failure.

The parser also currently includes checks for duplicate ambient and camera
declarations, required token counts, missing ambient/camera/light elements,
basic ambient/light ranges, and basic color ranges. These checks still need
stricter numeric and format validation.

### Window and event handling

- [x] Initializes MiniLibX.
- [x] Creates a window and image buffer.
- [x] Displays the image buffer.
- [x] Handles the window close event.
- [x] Handles the Escape key.
- [x] Frees the scene and MiniLibX resources on exit.

### Initial math helpers

The `mathlib` directory contains early versions of:

- [x] Vector addition.
- [x] Vector subtraction.
- [x] Vector magnitude.
- [x] Vector normalization with a zero-vector guard.
- [x] A scalar dot product helper named `dotprod`.
- [x] A normalization/range helper.

The normalization helper is currently used when parsing camera, plane, and
cylinder directions. These helpers still need focused tests, Norminette
cleanup, and integration with the renderer.

## Known incomplete or incorrect areas

### Rendering is not implemented

The current window displays an unrendered image. There is no implementation
for:

- Camera ray generation.
- Ray/object intersections.
- Selecting the nearest visible object.
- Computing surface normals.
- Lighting.
- Shadows.
- Writing calculated colors into the image buffer.

### Parsing validation is incomplete

The parser still needs to validate:

- [x] Exactly one ambient-light declaration. Duplicate and missing declarations
  are checked.
- [x] Exactly one camera declaration. Duplicate and missing declarations are
  checked.
- [x] At least one light. The final light count is checked.
- [x] Required token counts for every supported identifier.
- [x] Unknown identifiers.
- [x] Malformed numeric values. Scalar fields and vector/color components are
  format-checked, but invalid vector data can still become a zero vector.
- [x] Extra characters after numeric values. Most fields reject them through
  `is_num()`/`is_int()`, but invalid vector data is not propagated as an error.
- [ ] Vector component ranges and requirements.
- [x] Positive sphere diameter.
- [x] Positive cylinder diameter and height.
- [x] Color values as valid integer RGB values. Integer syntax, component
  count, range, and invalid-input rejection are checked.
- [x] Allocation failures from list-node creation.

### Math library needs correction

- A cross-product helper is needed.
- Scalar multiplication and vector scaling are needed.
- Zero-length vector handling needs dedicated tests.
- Every helper should have focused tests.
- Math source files currently need Norminette cleanup.

### Build and style issues

- Norminette currently reports errors in several existing project files.
- The Makefile references `includes`, while the current headers are at the
  project root.
- Object files and locally generated binaries should not be committed.
- Error handling for MiniLibX initialization and image/window creation needs to
  be completed.

## Remaining mandatory requirements

1. Finish testing and clean up the vector/math library.
2. Implement camera setup and ray generation.
3. Implement sphere intersections.
4. Implement plane intersections.
5. Implement finite-cylinder intersections, including caps if required by the
   project specification.
6. Select the nearest valid intersection.
7. Compute normals for every supported object.
8. Implement ambient and diffuse lighting.
9. Implement hard shadows.
10. Convert colors to the MiniLibX pixel format.
11. Render every pixel into the image buffer.
12. Complete scene-file validation.
13. Add robust cleanup for every error path.
14. Add test scenes for valid and invalid input.
15. Make the mandatory source pass Norminette.
16. Verify clean builds with `make`, `make clean`, `make fclean`, and `make re`.

## Suggested two-person work split

The split below minimizes conflicts by assigning different primary areas while
keeping clear shared interfaces.

### Person A: math, camera, and rendering pipeline

Primary responsibilities:

- Finalize `t_vec3` operations.
- Implement dot product, cross product, scaling, length, and normalization.
- Define ray-generation helpers.
- Initialize camera basis vectors.
- Implement the pixel loop.
- Implement ray casting and nearest-hit selection.
- Implement image-buffer pixel writes.
- Implement color conversion and clamping.
- Add the first end-to-end render using spheres.

Suggested files/directories:

- `mathlib/`
- New renderer files, for example `render/` or `mandatory/render/`
- Camera and ray-related declarations in the main header
- Image-pixel helpers

Deliverable:

- A valid scene containing a sphere renders a visible image.
- The renderer can distinguish background pixels from sphere pixels.
- Math and renderer unit/test scenes are documented.

### Person B: parser, geometry, lighting, and validation

Primary responsibilities:

- Strengthen scene parsing and token validation.
- Enforce required and unique scene elements.
- Validate all numeric ranges and vectors.
- Implement sphere, plane, and cylinder intersection functions.
- Implement object normals.
- Implement ambient, diffuse, and shadow calculations.
- Improve error-path cleanup.
- Create valid and invalid parser test scenes.

Suggested files/directories:

- `mandatory/parsing/`
- `mandatory/utils/`
- New geometry files, for example `objects/` or `mandatory/intersections/`
- New lighting files
- Test `.rt` scenes

Deliverable:

- Invalid scenes fail cleanly with `Error`.
- All mandatory object types return correct intersections and normals.
- Lighting and hard shadows work when connected to Person A's renderer.

## Shared interfaces to agree on first

Before implementing in parallel, agree on these signatures and data rules:

```c
typedef struct s_vec3	t_vec3;
typedef struct s_ray	t_ray;
typedef struct s_hit	t_hit;

double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_normalize(t_vec3 vec);
t_vec3	vec_scale(t_vec3 vec, double scalar);

int		intersect_sphere(t_ray ray, t_object *obj, t_hit *hit);
int		intersect_plane(t_ray ray, t_object *obj, t_hit *hit);
int		intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit);
int		find_closest_hit(t_ray ray, t_scene *scene, t_hit *hit);

t_color	trace_ray(t_ray ray, t_scene *scene);
void	put_pixel(t_img *img, int x, int y, int color);
```

The exact names may change, but both people should agree on:

- Ray direction normalization.
- Whether intersection functions return the nearest positive `t` or all
  possible roots.
- The meaning of `t_hit.t`.
- Normal direction conventions.
- Color range conventions: `0-255` or normalized `0.0-1.0`.
- Ownership and cleanup rules for objects and temporary allocations.

## Milestones

### Milestone 1: stabilize foundations

Target: both people can build from a clean checkout.

- Fix the Makefile include paths and source organization.
- Clean up the math headers and function names.
- Correct Norminette errors in files being actively modified.
- Add a small set of known valid and invalid scene files.
- Ensure `make`, `make clean`, and `make re` work.

### Milestone 2: first visible render

Target: a sphere is visible in the window.

- Person A completes vector operations, camera basis, ray generation, and pixel
  output.
- Person B completes strict enough parsing for a basic ambient/camera/light/
  sphere scene.
- Integrate sphere intersection and a flat test color.

### Milestone 3: mandatory geometry

Target: all mandatory objects render correctly.

- Add plane intersections and normals.
- Add finite-cylinder intersections and normals.
- Handle nearest-object selection.
- Test objects at different positions, rotations, and scales.

### Milestone 4: lighting and shadows

Target: rendered objects have correct basic illumination.

- Add ambient lighting.
- Add diffuse lighting.
- Add hard-shadow rays.
- Clamp colors and prevent light values from exceeding valid ranges.
- Test multiple lights and objects between a light and a surface.

### Milestone 5: validation and reliability

Target: the mandatory implementation is robust enough for evaluation.

- Reject malformed scenes without crashing.
- Verify duplicate and missing identifiers.
- Verify all ranges and vector constraints.
- Check every allocation and MiniLibX initialization.
- Verify cleanup with repeated failures and exits.
- Run Norminette over all submitted project files.
- Test with sanitizers or Valgrind where available.

### Milestone 6: final mandatory review

Target: submission-ready mandatory project.

- Review required behavior against the official subject.
- Test all sample scenes and edge cases.
- Check memory leaks.
- Check Makefile targets.
- Remove generated binaries and object files from version control.
- Ensure the final executable is named `miniRT`.

### Milestone 7: bonus, only after mandatory completion

Possible bonus work:

- Checkerboard patterns.
- Colored and multiple lights, if not already covered by mandatory work.
- Specular highlights.
- Bump mapping.
- Additional objects such as cones.
- Bonus parsing and a separate bonus executable.

Bonus should not begin until the mandatory renderer, parser, cleanup, and
Norminette checks are stable.

## Integration workflow

1. Keep commits focused on one feature.
2. Person A and Person B should avoid editing the same implementation file at
   the same time.
3. Merge math/header interface changes before dependent renderer or geometry
   changes.
4. After each merge, run:

   ```bash
   make re
   norminette miniRT.h miniRT_structs.h mandatory mathlib
   ```

5. Test at least one valid scene and one invalid scene after every milestone.
6. Do not commit `.o` files, `miniRT`, `a.out`, or temporary test binaries.

## Recommended immediate next tasks

1. Agree on the final vector API and fix `dotprod` to return a scalar.
2. Add a cross-product and normalization helper.
3. Fix the Makefile include path and source-list organization.
4. Add strict token-count and duplicate-element validation.
5. Implement a camera ray for each pixel.
6. Implement sphere intersection and render a single sphere.

# miniRT Two-Person Task Breakdown

This document expands the work split in `PROGRESS_PLAN.md` into concrete tasks.
It is written for the current repository state, where the parser and MiniLibX
startup exist but the ray-tracing pipeline is still incomplete.

## Shared Objective

The project is complete when a valid `.rt` scene can be parsed, rendered into a
MiniLibX image, displayed in a window, and released cleanly on normal exit or
any error path. Invalid scenes must fail with `Error` without crashes or leaks.

The work is split by ownership:

- **Person A:** vector mathematics, camera rays, rendering orchestration, image
  output, and the first end-to-end render.
- **Person B:** parser correctness, scene validation, geometry intersections,
  surface normals, lighting, shadows, and parser/error-path tests.

The split is not a strict dependency wall. Both people must agree on the shared
interfaces before adding callers or changing structures.

---

## Shared Contract Before Coding

Agree on these decisions first and record any changes in this document or the
main project plan.

### Data conventions

- A direction vector is normalized before it is used for ray generation or
  intersection calculations.
- A ray is represented by an origin and a normalized direction.
- An intersection is valid only when `t > EPSILON`.
- `t_hit.t` is the distance along the ray in `point = origin + dir * t`.
- The closest valid hit is selected; farther or negative roots are ignored.
- Surface normals are normalized and point away from the object surface.
- Colors use normalized doubles internally, normally in the range `0.0` to
  `1.0`, and are clamped before conversion to RGB bytes.
- Scene object and light lists remain owned by `t_scene` and are released by
  the existing cleanup path.

### Suggested shared declarations

```c
typedef struct s_vec3	t_vec3;
typedef struct s_ray	t_ray;
typedef struct s_hit	t_hit;

double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 vec, double scalar);
t_vec3	vec_normalize(t_vec3 vec);

int		intersect_sphere(t_ray ray, t_object *obj, t_hit *hit);
int		intersect_plane(t_ray ray, t_object *obj, t_hit *hit);
int		intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit);
int		find_closest_hit(t_ray ray, t_scene *scene, t_hit *hit);

t_color	trace_ray(t_ray ray, t_scene *scene);
void	put_pixel(t_img *img, int x, int y, int color);
```

The exact names may change, but the ownership, units, return values, and error
behavior must remain clear.

### Integration rule

Person A may use temporary flat colors while Person B is implementing lighting.
Person B may use direct test rays while Person A is implementing the pixel loop.
Neither person should silently change the meaning of `t_hit`, color ranges, or
object payloads after the other person has started depending on them.

---

# Person A: Math, Camera, and Rendering Pipeline

## A1. Stabilize the vector API

**Goal:** provide reliable operations for every later renderer and geometry
calculation.

### Tasks

- Audit the existing files in `mathlib/` and compare their names and return
  types with the shared API.
- Correct the dot product so it returns one scalar value, not a vector.
- Add vector cross product with the standard right-handed formula.
- Add scalar multiplication for vectors.
- Confirm vector addition and subtraction behavior.
- Confirm magnitude returns a non-negative scalar.
- Make normalization safe for a zero-length vector.
- Decide whether zero-vector normalization returns the zero vector or reports an
  error, then use that choice consistently.
- Avoid normalizing values that are meant to remain positions or colors.
- Keep floating-point tolerance logic in one place, such as an `EPSILON`
  constant or helper.

### Required checks

- Dot products of parallel, perpendicular, and opposite vectors.
- Cross products of the three basis axes and reversed operands.
- Addition, subtraction, and scaling with positive, negative, and zero values.
- Magnitude of the zero vector and a known 3-4-5 vector.
- Normalization of a known vector and the zero vector.
- Verify that no operation unexpectedly mutates its input.

### Definition of done

- The renderer and geometry code can include the math header without local
  duplicate implementations.
- The math source compiles with `-Wall -Wextra -Werror`.
- Focused checks demonstrate expected results within a small floating-point
  tolerance.

## A2. Define camera basis vectors

**Goal:** convert the parsed camera position, direction, and field of view into
an orthonormal basis for ray generation.

### Tasks

- Treat the parsed camera direction as the forward direction and normalize it.
- Choose a stable world-up vector, normally `(0, 1, 0)`.
- Handle the special case where the camera direction is parallel or nearly
  parallel to world-up by using another reference vector, such as `(1, 0, 0)`.
- Compute the right vector with a cross product.
- Compute the corrected up vector from the right and forward vectors.
- Normalize every basis vector after calculation.
- Verify the basis vectors are mutually perpendicular.
- Convert the horizontal or vertical field of view according to one documented
  convention; do not mix degrees and radians.
- Store the basis in the existing `t_camera` fields or update the structure in
  one coordinated header change.

### Definition of done

- A default forward-facing camera produces stable basis vectors.
- A camera aimed vertically does not create a zero basis vector.
- Changing the camera direction rotates the image in the expected direction.
- The camera setup has no hidden dependency on object or light data.

## A3. Generate one ray per pixel

**Goal:** generate a primary ray through the center of every output pixel.

### Tasks

- Use the existing `WIDTH` and `HEIGHT` constants, or replace them with one
  agreed configuration location.
- Map pixel coordinates to normalized screen coordinates.
- Account for the image aspect ratio so a sphere does not stretch on a wide
  window.
- Convert the field of view to a viewport scale using the agreed angle unit.
- Build the ray direction from camera right, camera up, and camera forward.
- Normalize the final direction.
- Use the camera position as the ray origin.
- Ensure the pixel center is sampled consistently, normally with `+ 0.5`.

### Cheap visual checks

- A sphere centered in front of the camera appears centered in the window.
- A sphere appears circular rather than elliptical.
- Moving the camera changes the view without changing object data.
- Reversing the camera direction makes the object disappear behind the camera.

## A4. Build the render loop

**Goal:** connect camera rays to scene tracing and image writes.

### Tasks

- Add a renderer entry point that receives `t_app` or the image and scene
  separately, following the existing ownership style.
- Iterate over every `y` row and every `x` column exactly once.
- Generate a primary ray for each pixel.
- Call `trace_ray` or the agreed scene-tracing function.
- Convert the returned color to a MiniLibX pixel value.
- Write the pixel through one image helper.
- Display the completed image after rendering, not once per pixel.
- Call the renderer from the existing startup path after scene parsing and image
  creation.

### Performance constraints

- Do not allocate memory inside the innermost pixel loop unless there is a
  demonstrated reason.
- Pass small structs by value only where that matches the project style and is
  cheaper than unnecessary heap allocation.
- Keep object traversal and color calculation deterministic.

## A5. Implement nearest-hit orchestration

**Goal:** make a ray return the closest visible object, independent of the
specific object formula.

### Tasks

- Traverse every node in `scene->objects`.
- Dispatch to the sphere, plane, or cylinder intersection function based on the
  object type.
- Keep the nearest positive intersection found so far.
- Initialize the hit state so a miss is unambiguous.
- Fill the hit point, normal, object pointer, and surface color after selecting
  the winning intersection.
- Do not let a farther object overwrite a closer hit.
- Do not accept intersections behind the ray origin.
- Define and use one epsilon to avoid self-intersection artifacts.

### Definition of done

- An empty ray returns the background color.
- A ray through one object returns that object.
- A ray through two objects returns the nearer object even if the farther object
  is encountered first in the linked list.
- A ray tangent to an object behaves consistently at the epsilon boundary.

## A6. Implement image and color conversion

**Goal:** safely write calculated colors into the MiniLibX image buffer.

### Tasks

- Confirm the byte order and bits-per-pixel values returned by
  `mlx_get_data_addr`.
- Create a single `put_pixel` helper that bounds-checks coordinates when useful.
- Clamp each color component before converting to an integer byte.
- Convert normalized colors to `0..255` exactly once.
- Pack red, green, and blue using the project and MiniLibX byte-order
  convention.
- Keep alpha handling consistent with the chosen image format.
- Make sure negative lighting results never wrap into large unsigned values.

### Definition of done

- A known red, green, and blue test pixel appears with the expected channel
  values.
- Values below zero become zero and values above one become the maximum byte.
- The renderer does not write beyond the image buffer.

## A7. First end-to-end milestone

**Goal:** prove the complete path with one sphere before integrating all objects
and lighting.

### Tasks

- Use one valid scene containing ambient light, camera, light, and sphere.
- Render a background color for misses.
- Render a contrasting flat color for sphere hits.
- Confirm the object silhouette and camera framing.
- Replace the flat color with the lighting result once Person B's lighting API is
  ready.
- Document the scene and expected visual result.

### Person A deliverable

- Stable math helpers.
- Camera basis and primary-ray generation.
- Pixel loop and image output.
- Closest-hit orchestration.
- A visible sphere rendered from a valid scene.
- Focused math and renderer checks or a repeatable manual test procedure.

---

# Person B: Parser, Geometry, Lighting, and Validation

## B1. Make scene parsing strict

**Goal:** every accepted scene has the required structure and valid values.

### Tasks

- Tokenize each non-empty input line without losing the identifier or values.
- Decide whether blank lines and whitespace-only lines are allowed, then apply
  that rule consistently.
- Reject unknown identifiers.
- Enforce exact token counts for `A`, `C`, `L`, `sp`, `pl`, and `cy`.
- Reject missing values and extra values.
- Reject malformed floating-point strings, including trailing characters that
  the numeric parser silently ignores.
- Validate vector syntax as exactly three numeric components separated by commas.
- Validate color syntax as exactly three integer RGB components.
- Reject colors outside `0..255`.
- Validate ambient ratio and light brightness against the subject's allowed
  range.
- Validate camera field of view against its allowed range.
- Require non-zero direction vectors where normalization is required.
- Validate positive sphere diameter, cylinder diameter, and cylinder height.
- Keep parsed values in the units expected by geometry and lighting code.

## B2. Track required and unique scene elements

**Goal:** reject incomplete or ambiguous scenes before rendering starts.

### Tasks

- Allow exactly one ambient-light declaration.
- Allow exactly one camera declaration.
- Require at least one light.
- Require at least one renderable object if that is the chosen project policy.
- Reject duplicate `A` and `C` declarations.
- Decide whether multiple `L` declarations are allowed; the mandatory subject
  permits multiple lights only if the implementation supports them consistently.
- Do not use list length alone to detect whether `A` or `C` was parsed, because
  those values live directly in `t_scene`.
- Add explicit parser state flags or counters for required declarations.
- Perform the final completeness check after the whole file is read.

### Definition of done

- A valid minimal scene reaches window initialization.
- Every missing or duplicated required declaration returns `Error`.
- Unknown identifiers and malformed lines fail before rendering.

## B3. Improve allocation and cleanup paths

**Goal:** parser failures leave no allocated lists, nodes, strings, or file state.

### Tasks

- Check every allocation for `NULL`.
- Check every list-node creation before adding it to the scene.
- Free temporary token arrays on every return path after tokenization.
- Free partially built object and light lists when a later line fails.
- Close the scene file on success and failure.
- Use the existing `free_scene`, `free_object`, and `clean_gnl` helpers rather
  than adding competing cleanup logic.
- Keep MiniLibX cleanup separate from scene cleanup so parser tests can run
  without opening a window.
- Ensure a failed parser does not leave stale pointers in `t_app`.

### Required checks

- Invalid first line.
- Invalid line after several valid objects.
- Allocation failure injection if practical.
- Empty file and whitespace-only file.
- File read failure after partial input.
- Repeated invalid-scene execution under Valgrind or a sanitizer.

## B4. Implement sphere intersections and normals

**Goal:** calculate the nearest valid hit for a sphere.

### Tasks

- Use the quadratic ray-sphere equation with the sphere center and radius.
- Convert the parsed diameter to radius exactly once.
- Handle negative, zero, one, and two real roots.
- Select the smallest root greater than `EPSILON`.
- Compute the hit point from the ray equation.
- Compute the outward normal as the normalized vector from sphere center to hit
  point.
- Copy the object's surface color into the hit result.

### Tests

- Ray misses the sphere.
- Ray enters and exits the sphere.
- Ray starts inside the sphere.
- Ray is tangent to the sphere.
- Sphere is translated away from the origin.
- Sphere with a small and a large diameter.

## B5. Implement plane intersections and normals

**Goal:** calculate infinite-plane hits with correct orientation.

### Tasks

- Use the plane point and normalized plane normal.
- Reject parallel rays using an epsilon comparison on the denominator.
- Calculate the ray parameter and reject negative or near-zero values.
- Compute the hit point.
- Return the plane normal consistently; if two-sided lighting is desired,
  orient it against the incoming ray in the lighting layer.
- Copy the plane color into the hit result.

### Tests

- Ray perpendicular to the plane.
- Ray parallel to the plane.
- Ray pointing away from the plane.
- Plane translated from the origin.
- Plane with a non-axis-aligned normal.

## B6. Implement finite-cylinder intersections

**Goal:** support the mandatory finite cylinder, including end caps if required
by the subject version being followed.

### Tasks

- Normalize the cylinder axis during parsing or before intersection.
- Project the ray and origin onto the plane perpendicular to the axis.
- Solve the side quadratic while removing the axis component.
- Reject side roots outside the finite height interval.
- Test both roots and retain the nearest positive valid root.
- Test the lower and upper caps when caps are required.
- Use a disk test for each cap: the hit must be within the radius from the cap
  center.
- Compare side and cap candidates and return the nearest valid candidate.
- Compute a side normal by removing the axis component from the hit-to-center
  vector and normalizing it.
- Use the axis direction, with the correct sign, for cap normals.
- Handle rays parallel to the cylinder axis without dividing by a value near
  zero.

### Tests

- Ray hits the curved side.
- Ray misses the side but hits a cap.
- Ray misses the finite height range.
- Ray parallel to the axis.
- Ray starts inside the cylinder.
- Cylinder is translated and rotated.
- A cap boundary hit behaves consistently at epsilon tolerance.

## B7. Implement normals through one object-facing API

**Goal:** keep renderer code independent from object-specific data layouts.

### Tasks

- Provide one normal-dispatch helper or keep normal calculation next to each
  intersection function, but choose one pattern consistently.
- Ensure every returned normal is normalized.
- Ensure the normal corresponds to the selected hit, not merely the object
  origin.
- Decide whether normals are flipped to face the ray in the normal helper or in
  the lighting helper.
- Document the choice because it affects diffuse and shadow calculations.

## B8. Implement ambient and diffuse lighting

**Goal:** turn a hit into a visible surface color.

### Tasks

- Start with the object's base color.
- Apply ambient contribution using the scene ambient ratio and ambient color.
- For each supported light, calculate the direction from hit point to light.
- Calculate the diffuse factor as the clamped dot product of the surface normal
  and light direction.
- Include light brightness and light color according to the chosen color model.
- Combine contributions without allowing components to exceed the internal
  range before final clamping.
- Keep color multiplication component-wise.
- Return ambient color for a surface that receives no direct light.

### Tests

- Surface facing the light is brighter than a surface turned away.
- Ambient light affects surfaces even when direct light is absent.
- Multiple lights add consistently.
- Red, green, and blue object/light combinations preserve channel behavior.
- A back-facing surface receives no negative diffuse contribution.

## B9. Implement hard shadows

**Goal:** prevent direct light from contributing when another object blocks it.

### Tasks

- Start the shadow ray at the hit point offset slightly along the surface normal.
- Point the shadow ray toward the light.
- Limit the shadow intersection distance to the light distance.
- Reuse the closest-hit or object-intersection helpers without treating the
  light itself as an object.
- Ignore the originating surface at the epsilon offset.
- Keep ambient contribution while suppressing blocked diffuse contribution.
- Test each light independently when multiple lights are supported.

### Tests

- An unobstructed point receives diffuse light.
- A second object between the point and light creates a hard shadow.
- A point does not shadow itself.
- An object behind the light does not cast a shadow on the point.
- Shadow behavior remains stable for planes and cylinders.

## B10. Build parser and geometry test scenes

**Goal:** make regressions reproducible without relying only on visual inspection.

### Valid scenes

- One centered sphere.
- A plane and sphere with ambient and direct light.
- A rotated cylinder with visible caps.
- Multiple objects at different distances.
- Multiple lights if supported by the chosen implementation.

### Invalid scenes

- Missing ambient light.
- Missing camera.
- Missing light.
- Duplicate ambient or camera.
- Unknown identifier.
- Wrong token count.
- Invalid vector or color syntax.
- Out-of-range color, ratio, or field of view.
- Zero direction vector.
- Non-positive diameter or height.
- Extra text after a numeric value.

### Person B deliverable

- Strict parser with explicit completeness checks.
- Sphere, plane, and finite-cylinder intersections and normals.
- Ambient, diffuse, and hard-shadow lighting.
- Complete cleanup on parser and rendering setup failures.
- Valid and invalid `.rt` scenes with documented expected outcomes.

---

# Integration Sequence

## Stage 1: interfaces and build

1. Agree on color units, epsilon, ray direction rules, and hit semantics.
2. Resolve header declarations and structure changes together.
3. Fix the Makefile include path if headers remain at the repository root rather
   than moving headers into `includes/`.
4. Confirm both people can run `make` from a clean object-file state.

## Stage 2: first visible sphere

1. Person B supplies a strict valid sphere scene.
2. Person A completes vector helpers, camera rays, and pixel output.
3. Person B supplies sphere intersection and a temporary flat-color hit result.
4. Person A connects nearest-hit selection and renders the sphere silhouette.
5. Verify background pixels, object pixels, camera centering, and aspect ratio.

## Stage 3: all mandatory geometry

1. Add plane intersection and normal.
2. Add finite-cylinder side intersection.
3. Add caps if required by the subject version.
4. Test nearest-object selection with overlapping objects.
5. Test rotated and translated objects.

## Stage 4: lighting and shadows

1. Person B adds ambient lighting.
2. Add diffuse lighting for one light.
3. Add hard shadows.
4. Add multiple-light behavior only after one-light behavior is correct.
5. Person A verifies normalized colors, clamping, and image packing.

## Stage 5: reliability and style

1. Run valid and invalid scene tests.
2. Test all error paths and cleanup.
3. Run `make`, `make clean`, `make fclean`, and `make re`.
4. Run Norminette on submitted project files.
5. Use Valgrind or sanitizers where available.
6. Remove generated executables and object files from version control.

---

# Definition of Complete Work

The split is complete only when all of the following are true:

- `make` succeeds from a clean state.
- A valid scene opens a window and displays a rendered image.
- Background, sphere, plane, and cylinder pixels are distinguishable.
- The nearest positive intersection is selected.
- Normals are correct and normalized.
- Ambient light, diffuse light, and hard shadows behave correctly.
- Colors are clamped and packed without channel corruption.
- Duplicate, missing, malformed, and out-of-range scene data returns `Error`.
- Parser, MiniLibX, file, list, and image resources are released on every exit
  path.
- The code passes the project's required compiler flags and Norminette checks.
- At least one valid and one invalid scene are repeatable regression tests.

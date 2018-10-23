#include "lib_internal.h"

id_scene num_current_scenes = 0;
struct scene * scenes[256] = {0};

id_scene
scene_create_basic()
{
  id_scene id_scene = scene_init();
  shape_triangle(id_scene, object_get(id_scene));
  return id_scene;
}

id_object
object_get(id_scene id)
{
  return SCENE(id)->num_objects_occupied++;
}

void
shape_triangle(id_scene id_scene, id_object id_object)
{
  size_t num_vertices = 3;
  float data_triangle[] = {
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.0f,  0.0f,
     0.0f,  0.5f,  0.0f,
  };
  id_data_vertices id_vertices = vertices_get(id_scene, num_vertices);
  data_vertices_write(VERTEX_POINTER(id_scene, id_vertices),
      sizeof(data_triangle), data_triangle);

  struct objects * objects = OBJECTS(id_scene);
  objects->x[id_object] = 0;
  objects->y[id_object] = 0;
  objects->z[id_object] = 0;
  objects->id_vertices[id_object] = id_vertices;
  objects->num_vertices[id_object] = num_vertices;
}

id_data_vertices
vertices_get(id_scene id_scene, size_t num_vertices)
{
  id_data_vertices start = SCENE(id_scene)->num_vertices_occupied;
  SCENE(id_scene)->num_vertices_occupied += num_vertices*SIZE_VERTEX;
  return start;
}

void
data_vertices_write(float * start, size_t size_data, float * data)
{
  memcpy(start, data, size_data);
}

void
scene_run(id_scene id)
{
  printf("Running scene %u\n", id);
  while (!glfwWindowShouldClose(SCENE(id)->window)) {
    glfwPollEvents();
  }
}

void
scene_destroy(id_scene id)
{
  free(SCENE(id));
  SCENE(id) = NULL;
  num_current_scenes--;
  if (num_current_scenes == 0) {
    graphicslib_terminate();
  }
}

id_scene
scene_init()
{
  id_scene id_new = ID_ENSURE_ZERO_IS_ERROR(num_current_scenes);
  if (SCENE(id_new) == NULL) {
    SCENE(id_new) = malloc(sizeof(struct scene));
    if (SCENE(id_new) == NULL) {
       return ID_SCENE_ERROR;
    }
    memset(SCENE(id_new),0,sizeof(struct scene));
  }
  if (num_current_scenes == 0) {
    /* Initialize GLFW library. */
    SCENE(id_new)->window = graphicslib_init();
  }
  num_current_scenes++;
  return id_new;
}

GLFWwindow *
graphicslib_init()
{
  if (!glfwInit()) {
    err("%s\n", "Could not initialize glfw.");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  uint16_t screen_width = 800;
  uint16_t screen_height = 600;
  const char * screen_title = "Main Dod.";

  GLFWwindow * window = glfwCreateWindow(screen_width, screen_height,
      screen_title, NULL, NULL);

  if (window == NULL) {
    err("%s\n", "Could not create a window.\n");
    return NULL;
  }

  glfwMakeContextCurrent(window);
  if (gl3wInit()) {
    err("%s\n", "Could not initialize gl3w.");
    graphicslib_terminate();
    return NULL;
  }
  return window;
}

void
graphicslib_terminate()
{
  glfwTerminate();
}

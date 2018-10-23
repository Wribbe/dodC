#ifndef FILE_LIB_H
#define  FILE_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

typedef uint8_t id_scene;
typedef uint16_t id_object;
typedef uint16_t id_matrix_transform;
typedef uint16_t id_data_vertices;
typedef uint16_t id_data_VAO;

typedef float m4[4][4];

#define LEN(x) (sizeof(x)/sizeof(x[0]))
#define err(fmt, ...) (fprintf(stderr, fmt, __VA_ARGS__))

#define NUM_MEMARENA_VERT 1024
#define SIZE_VERTEX 3

struct memarena_vertex {
  float data[NUM_MEMARENA_VERT];
};

#define NUM_OBJECTS 100

struct objects {
  int16_t x[NUM_OBJECTS];
  int16_t y[NUM_OBJECTS];
  int16_t z[NUM_OBJECTS];
  id_data_vertices id_vertices[NUM_OBJECTS];
  int16_t num_vertices[NUM_OBJECTS];
  id_data_VAO id_VAO[NUM_OBJECTS];
};

extern id_scene num_current_scenes;
extern struct scene * scenes[];

struct scene {
  uint8_t num_objects_occupied;
  uint16_t num_vertices_occupied;
  struct objects objects;
  struct memarena_vertex vertices;
  GLFWwindow * window;
};

id_scene
scene_create_basic();

#define ID_SCENE_ERROR 0

id_scene
scene_init();

void
scene_run(id_scene id);

void
scene_destroy(id_scene id);

#endif

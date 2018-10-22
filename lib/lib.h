#ifndef FILE_LIB_H
#define  FILE_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t id_scene;
typedef uint16_t id_object;
typedef uint16_t id_matrix_transform;
typedef uint16_t id_data_vertices;

typedef float m4[4][4];

#define NUM_MEMARENA_VERT 1024

struct memarena_vertex {
  uint32_t index_free;
  float data[NUM_MEMARENA_VERT];
};

#define NUM_OBJECTS 100

struct objects {
  uint8_t num_occupied;
  int16_t x[NUM_OBJECTS];
  int16_t y[NUM_OBJECTS];
  int16_t z[NUM_OBJECTS];
  id_data_vertices id_vertices[NUM_OBJECTS];
  m4 matrix_transform[NUM_OBJECTS];
};

extern id_scene num_current_scenes;
extern struct scene * scenes[];

struct scene {
  struct objects objects;
  struct memarena_vertex vertices;
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

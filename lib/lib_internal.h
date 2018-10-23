#ifndef FILE_LIB_INTERNAL_H
#define FILE_LIB_INTERNAL_H

#define ID_ENSURE_ZERO_IS_ERROR(id) (id+1)
#define SCENE(id) (scenes[id-1])
#define VERTEX_POINTER(id_scene, id_vertices) (&(SCENE(id_scene)->vertices.data[id_vertices]))
#define OBJECTS(id_scene) (&(SCENE(id_scene)->objects))

id_object
object_get(id_scene id);

void
shape_triangle(id_scene id_scene, id_object id_object);

void
data_vertices_write(float * start, size_t size_data, float * data);

id_data_vertices
vertices_get(id_scene id_scene, size_t num_vertices);

#endif

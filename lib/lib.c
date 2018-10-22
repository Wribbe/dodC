#include "lib.h"
#include "lib_internal.h"

id_scene num_current_scenes = 0;
struct scene * scenes[256] = {0};

#define ID_ENSURE_ZERO_IS_ERROR(id) (id+1)
#define SCENE(id) (scenes[id-1])

id_scene
scene_create_basic()
{
  id_scene id = scene_init();
  return id;
}

void
scene_run(id_scene id)
{
  printf("Running scene %u\n", id);
}

void
scene_destroy(id_scene id)
{
  free(SCENE(id));
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
  num_current_scenes++;
  return id_new;
}

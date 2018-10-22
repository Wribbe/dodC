#include "lib.h"

int
main(void)
{
  id_scene id_scene_basic = scene_create_basic();
  printf("Got scene id: %u\n", id_scene_basic);
  scene_run(id_scene_basic);
  scene_destroy(id_scene_basic);
}

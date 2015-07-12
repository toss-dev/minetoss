#include "client/main.h"

static void	updateTerrainLoad(t_world *world)
{
	t_terrain	*terrain;
	t_point3	index;
	int			x;
	int 		z;
	t_point3	pos;
	double 		dist;

	pos = getTerrainIndexForPos(g_game->renderer.camera.pos);
	for (x = -TERRAIN_LOAD_DISTANCE ; x < TERRAIN_LOAD_DISTANCE ; x++)
	{
		for (z = -TERRAIN_LOAD_DISTANCE ; z < TERRAIN_LOAD_DISTANCE ; z++)
		{
			index.x = pos.x + x;
			index.y = 0;
			index.z = pos.z + z;
			dist = point3_dist(pos, index);
			if (dist < TERRAIN_LOAD_DISTANCE)
			{
				terrain = getTerrain(world, index);
				if (terrain == NULL)
				{
					terrain = createNewTerrain(world, index);
				}
				if (terrain == NULL)
				{
					logger_log(LOG_ERROR, "Not enough memory to allocate new terrain!");
					continue ;
				}
				if (!terrainHasState(terrain, TERRAIN_GENERATED))
				{
					generateTerrain(terrain);
				}
				loadTerrain(world, terrain);
			}
		}
	}
}

static void 	loopTerrainMesher(t_game *game)
{
	t_world	*world;

	world = &(game->world);
	while (isGameRunning(game))
	{
		updateTerrainLoad(world);
		updateTerrains(world);
		usleep(10000);
	}
}

void 			startTerrainMesher(t_game *game)
{
	if (pthread_create(game->threads + THRD_MESHER, NULL, (t_pthread_start)loopTerrainMesher, game) != 0)
	{
		logger_log(LOG_ERROR, "Couldnt start mesher thread");
		exit(EXIT_FAILURE);
	}
}
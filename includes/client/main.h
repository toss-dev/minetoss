/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 22:58:24 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:44 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "common/common.h"
# include "client/network/client.h"
# include "client/opengl.h"
# include "client/texture.h"
# include "client/font.h"
# include "client/sound.h"
# include "client/view.h"

/** file has to be added in the same order as these enum are declared */
enum e_sounds
{
	SOUND_KALIMBA,
	SOUND_MAX
};

enum e_sound_sources
{
	SOUND_SOURCE_MUSIC,
	SOUND_SOURCE_MAX
};

enum e_program_id
{
	PROGRAM_TERRAIN,
	PROGRAM_SKYBOX,
	PROGRAM_FONT,
	PROGRAM_QUAD,
	PROGRAM_MAX
};

enum	e_camera_config
{
	C_MOVE_LEFT = 1,
	C_MOVE_RIGHT = 2,
	C_MOVE_FORWARD = 4,
	C_MOVE_BACKWARD = 8,
	C_SNEAK = 16
};

typedef t_model	(*t_load_model)(void);

enum e_models
{
	MODEL_MAX
};

typedef struct	s_camera
{
	float	*view_matrix;
	float	*project_matrix;
	t_vec3	pos;
	t_vec3	vec_pos;
	t_vec3	vec_rot;
	t_vec3	look_vec;
	float	fov;
	float	near_dist;
	float	far_dist;
	float	pitch;
	float	yaw;
	float 	roll;
	int		state;
}				t_camera;

enum e_cumebap_id
{
    CUBEMAP_DAY,
    CUBEMAP_NIGHT,
    CUBEMAP_MAX
};

typedef struct  s_sky
{
	GLuint		vaoID;
	GLuint		vboID;
	unsigned	vertex_count;
    GLuint		cubemaps[CUBEMAP_MAX];
    t_vec3		rot;
}				t_sky;

enum e_renderer_config
{
	RENDERER_CONFIG_DEBUG = 1
};

typedef struct 	s_renderer
{
	t_timer			*timer;
	unsigned int 	fps;
	t_camera		camera;
	t_program		programs[PROGRAM_MAX];
	t_sky			sky;
	t_block			blocks[BLOCK_MAX];
	GLuint			block_atlas[RESOLUTION_BLOCK_ATLAS_MAX];
	GLuint			textures[T_MAX];
	t_model			quad_model;
	size_t			config;
	t_view			views[VIEW_MAX]; //every views are store in this array, loaded on initialization
	t_list 			views_list; //this list contains the ID of using views
}				t_renderer;

/**
**	world is made of 16*128*16 terrains at a given index (x, y, z)
**	it render is spread in 16x16x16 block meshes
*/

enum e_terrain_state
{
	TERRAIN_GENERATED = 1,
	TERRAIN_LOADED = 2
};

typedef struct 	s_terrain	//16x256x16
{
	t_point3	index;
	char		blocks[TERRAIN_SIZEX][TERRAIN_SIZEY][TERRAIN_SIZEZ];
	t_model		meshes[MESH_PER_TERRAIN];	//the index correspond to the y chunk component
	int 		state;
}				t_terrain;

typedef struct 	s_world_renderer
{
	t_world 	*world;
	t_renderer 	*renderer;
	t_program	*program;
}				t_world_renderer;

//main thread is for rendering ONLY
enum e_thread_name
{
	THRD_TERRAIN,
	THRD_NETWORK,
	THRD_MAX
};

enum e_game_state
{
	GAME_RUNNING = 1,
	GAME_MAIN_MENU = 2,
	GAME_INGAME = 4 
};

typedef struct 	s_game
{
	pthread_t		threads[THRD_MAX];
	t_world			world;
	t_renderer		renderer;
	t_window		window;
	t_sound_manager	sound_manager;
	t_timer			timer;
	t_client		*client;
	unsigned		state;
}				t_game;

extern t_game	*g_game;

/** core functions */
t_game			*gameNew(void);
void			gameLoop(t_game *game);
void			gameStop(t_game *game);
void			gameExit(t_game *game);
int				isGameRunning(t_game *game);
int				gameHasState(t_game *game, unsigned int state);
void			gameSetState(t_game *game, unsigned int state);
void			gameUnsetState(t_game *game, unsigned int state);

/** network*/
void			startNetwork(t_game *game);
void			initNetwork(t_game *game);
void			stopNetwork(t_game *game);


/** initiazers functions */
void			initArgs(t_game *game, int argc, char **argv);
void			initOpenGL(t_window *win, t_renderer *renderer);
void			initWindow(t_window *win);
void			initEvent(t_window *window);
void			initWorld(t_world *world);
void			initRenderer(t_renderer *renderer);
void			loadBlocks(t_renderer *renderer);
void 			initSound(t_sound_manager *manager);

/** sounds */
void 			updateSound(t_sound_manager *sound_manager, t_camera *camera);

/** events functions */
void			keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void			cursorMoveCallback(GLFWwindow *window, double x, double y);
void			mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

/** thread mains */
int				updateWorldGenerator(t_game *game);

/** memory clean */
void 			cleanWindow(t_window *window);

/** sky */
void        	skyDelete(t_sky *sky);
void       	 	loadSky(t_renderer *renderer);
void            updateSky(t_world *world, t_renderer *renderer, t_timer *timer);
t_vec3    		mix_color(t_vec3 a, t_vec3 b, float factor);
void			calculateSunColor(t_world *world, t_renderer *renderer, float day_ratio);

/** program / shader related functions */
void			loadPrograms(t_renderer *renderer);
GLuint			loadShader(char const *str, GLenum type);
void			shaderDelete(GLuint program_id, GLuint shader_id);
void			programDelete(t_program *program);

/** main world update functions, will update the world and all it components */
void 			startTerrainUpdate(t_game *game);
void			updateWorld(t_world *world);
void			updateMesh(t_world *world, t_terrain *terrain, unsigned meshID);
t_terrain		*createNewTerrain(t_world *world, t_point3 index);
void 			removeTerrain(t_world *world, t_point3 index);

void 			loadWeather(t_weather *weather);

t_block			*getBlockByID(unsigned id);
void			raycast(t_vec3 origin, t_vec3 direction, float radius, int (*callback)(), void *extra);

/** renderer config */
void 			rendererActiveConfig(t_renderer *renderer, unsigned config);
void 			rendererDisableConfig(t_renderer *renderer, unsigned config);
int				rendererHasConfig(t_renderer *renderer, unsigned config);
void 			rendererSwitchConfig(t_renderer *renderer, unsigned config);
void			rendererAddView(t_renderer *renderer, unsigned int viewID);
void			rendererRemoveView(t_renderer *renderer, unsigned int viewID);
t_view			*rendererGetView(t_renderer *renderer, unsigned int viewID);

/**	terrain functions
**
**	Terrain is a 16x128x16 blocks space of (128 / 16 = 8) 8 16x16x16 blocks chunks
*/
void			loadTerrains(t_world *world);
void 			loadTerrain(t_terrain *terrain);
void 			unloadTerrain(t_terrain *terrain);
void			terrainSetState(t_terrain *terrain, unsigned state);
void			terrainUnsetState(t_terrain *terrain, unsigned state);
int				terrainHasState(t_terrain *terrain, unsigned state);
t_terrain		*getTerrainAt(t_world *world, t_vec3 vec);
t_terrain		*getTerrain(t_world *world, t_point3 index);
void			generateTerrainKey(char *buffer, t_point3 index);

int				getTerrainHeightAt(t_terrain *terrain, float x, float z);
t_point3		getTerrainRelativePos(t_vec3 vec);
t_point3		getTerrainIndexForPos(t_vec3 pos);

unsigned		getBlock(t_world *world, t_vec3 pos);
void 			setBlock(t_world *world, unsigned blockID, t_vec3 pos);

/** terrain's mesh factory */
void 			loadTerrainMeshFactory(t_renderer *renderer);
void			updateTerrainMeshData(t_world *world, t_terrain *terrain, unsigned chunkID);
void			updateTerrainNeighborMeshesData(t_world *world, t_terrain *terrain);
void			updateTerrainMeshes(t_world *world, t_terrain *terrain);
void			updateMeshes(t_world *world, t_terrain *terrain, unsigned meshID);

/** main render functions, will render the whole world to default framebuffers */
void			render(t_game *game);
void			renderMainMenu(t_game *game);
void 			renderIngame(t_game *game);
void			renderSky(t_world *world, t_renderer *renderer);
void 			renderTerrains(t_world *world, t_renderer *renderer);
void			renderUI(t_world *world, t_renderer *renderer);

/** view functions */
void			renderView(t_renderer *renderer, t_view *view);
void 			loadViews(t_renderer *renderer);
void			loadViewMainMenu(t_view *view);

/** opengl function wrapper */

void			loadUniformMatrix(GLuint id, float *matrix);
void			loadUniformFloat(GLuint id, float value);
void			loadUniformVec(GLuint id, t_vec3 p);
void			loadUniformInt(GLuint id, GLuint integer);

/** camera related functions */
int				isInCameraFrustum(t_camera *camera, t_vec3 point, float impresicion);
void			cameraControlRelease(t_camera *camera, int key);
void			cameraControlPress(t_camera *camera, int key);
void			updateCamera(t_camera *camera);
void			loadCamera(t_renderer *renderer);

/** weather */
void			updateWeather(t_world *world, t_renderer *renderer, t_timer *timer);


/** blocks */
void			createBlockTextures(t_renderer *renderer);


/** world generator */
void 	startTerrainUpdate(t_game *game);
void	startWorldGenerator(t_game *game);
void   	generateTerrain(t_terrain *terrain);
void	loadWorldGenerator(void);
void	prepareNoise(void);
double	noise2(t_vec2 in);
double	noise3(t_vec3 in);


/** packets handler */
void			packetHandlerLive(t_game *game, t_packet *packet);

#endif

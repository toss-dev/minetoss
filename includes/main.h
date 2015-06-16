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

# include "libft.h"
# include "opengl.h"
# include "maths.h"

# include "texture.h"
# include "blocks.h"
# include "const.h"
# include "timer.h"

enum e_program_id
{
	PROGRAM_TERRAIN,
	PROGRAM_SKYBOX,
	PROGRAM_PARTICLE,
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

enum	e_particles
{
	ParticleMoving,
	PARTICLES_MAX_TYPE
};

typedef struct	s_particle
{
	t_vec3		rot;
	t_vec3		scale;
	t_vec3		pos;
	t_vec3		rot_vec;
	t_vec3		scale_vec;
	t_vec3		pos_vec;
	int			texture_id;
	unsigned	id;
	float		health;
	float 		speed;
	t_vec3		color;
	int 		texture_atlas_id;
	unsigned	timer;
	float 		camera_dist;
}				t_particle;

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

typedef struct	s_entity
{
	t_vec3	rot;
	t_vec3	scale;
	t_vec3	pos;
	t_vec3	rot_vec;
	t_vec3	scale_vec;
	t_vec3	pos_vec;
	int		textureID;
	float	health;
	float 	speed;
}				t_entity;

typedef struct 	s_renderer
{
	t_camera		camera;
	t_program		programs[PROGRAM_MAX];
	t_sky			sky;
	t_block			blocks[BLOCK_MAX];
	GLuint			block_atlas[RESOLUTION_BLOCK_ATLAS_MAX];
	t_array_list	particles;
	t_texture_atlas	textures_atlases[T_ATLAS_MAX];
	t_model			quad_model;	
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
	char 		blocks[TERRAIN_SIZEX][TERRAIN_SIZEY][TERRAIN_SIZEZ];
	t_model		meshes[MESH_PER_TERRAIN];	//the index correspond to the y chunk component
	t_point3	index;	//given x, y, z index (for hashtable)
	int 		state;
}				t_terrain;

typedef struct 	s_weather
{
	t_vec3	sun_pos;
	t_vec3	sun_color;
	t_vec3	fog_color;
	float 	fog_density;
	float 	fog_gradient;
}				t_weather;

typedef struct 	s_world
{
	t_htab		terrains;
	t_weather	weather;
}				t_world;


typedef struct 	s_world_renderer
{
	t_world 	*world;
	t_renderer 	*renderer;
	t_program	*program;
}				t_world_renderer;

//main thread is for rendering ONLY
enum e_thread_name
{
	THRD_GENERATOR,
	THRD_MAX
};

enum e_game_state
{
	GAME_STATE_RUNNING = 1
};

typedef struct 	s_game
{
	t_world		world;
	t_renderer	renderer;
	thrd_t		threads[THRD_MAX];
	t_window	window;
	t_timer		timer;
	unsigned	state;
}				t_game;

extern t_game	*g_game;

/** threads */
typedef bool	(*t_thread_callback)(t_game *);

typedef struct 	s_thread_param
{
	t_game				*game;
	unsigned			threadID;
	unsigned			ups;
	t_thread_callback	callback;
}				t_thread_param;

/** initiazers functions */
void			initArgs(t_game *game, int argc, char **argv);
void			initOpenGL(t_window *win, t_renderer *renderer);
void			initWindow(t_window *win);
void			initEvent(t_window *window);
void			initWorld(t_world *world);
void			initRenderer(t_renderer *renderer);
void			loadBlocks(t_renderer *renderer);

/** events functions */
void			keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void			cursorMoveCallback(GLFWwindow *window, double x, double y);
void			mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

/** core functions */
t_game			*gameNew(void);
void			gameLoop(t_game *game);
void			gameStop(t_game *game);
void			gameClean(t_game *game);
bool			isGameRunning(t_game *game);
void			startThread(t_game *game, unsigned threadID, unsigned ups, t_thread_callback callback);

/** thread mains */
bool			updateWorldGenerator(t_game *game);

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
void			updateWorld(t_world *world);
void			updateTerrains(t_world *world, t_vec3 pos);
void			updateMesh(t_world *world, t_terrain *terrain, unsigned meshID);
t_terrain		*createNewTerrain(t_world *world, t_point3 index);

void 			loadWeather(t_weather *weather);

t_block			*getBlockByID(unsigned id);
void			raycast(t_vec3 origin, t_vec3 direction, float radius, int (*callback)(), void *extra);


/**	terrain functions
**
**	Terrain is a 16x128x16 blocks space of (128 / 16 = 8) 8 16x16x16 blocks chunks
*/
void			loadTerrains(t_world *world);
void 			loadTerrain(t_terrain *terrain);
void 			unloadTerrain(t_terrain *terrain);
void			terrainSetState(t_terrain *terrain, unsigned state);
void			terrainUnsetState(t_terrain *terrain, unsigned state);
bool			terrainHasState(t_terrain *terrain, unsigned state);
void            loadWorldGenerator(void);
t_terrain		*getTerrainAt(t_world *world, t_vec3 vec);
t_terrain		*getTerrain(t_world *world, t_point3 index);
void   			generateTerrain(t_terrain *terrain);
void			generateTerrainKey(char *buffer, t_point3 index);

int				getTerrainHeightAt(t_terrain *terrain, float x, float z);
t_point3		getTerrainRelativePos(t_vec3 vec);
t_point3		getTerrainIndexForPos(t_vec3 pos);

unsigned		getBlock(t_world *world, t_vec3 pos);
void 			setBlock(t_world *world, unsigned blockID, t_vec3 pos);

/** terrain's mesh factory */
void 			loadTerrainMeshFactory(t_renderer *renderer);
void			updateTerrainMeshData(t_world *world, t_terrain *terrain, unsigned chunkID);
void			updateTerrainMeshesData(t_world *world, t_terrain *terrain);
void 			updateNeighborTerrainsMeshes(t_world *world, t_terrain *terrain);
void			updateMeshes(t_world *world, t_terrain *terrain, unsigned meshID);

/** main render functions, will render the whole world to default framebuffers */
void			render(t_world *world, t_renderer *renderer);
void			renderSky(t_world *world, t_renderer *renderer);
void 			renderTerrains(t_world *world, t_renderer *renderer);
void			renderUI(t_world *world, t_renderer *renderer);
void			renderParticles(t_world *world, t_renderer *renderer);

/** opengl function wrapper */

void			loadUniformMatrix(GLuint id, float *matrix);
void			loadUniformFloat(GLuint id, float value);
void			loadUniformVec(GLuint id, t_vec3 p);
void			loadUniformInt(GLuint id, GLuint integer);

/** camera related functions */
bool			isInCameraFrustum(t_camera *camera, t_vec3 point, float impresicion);
void			cameraControlRelease(t_camera *camera, int key);
void			cameraControlPress(t_camera *camera, int key);
void			updateCamera(t_camera *camera);
void			loadCamera(t_renderer *renderer);

/** weather */
void			updateWeather(t_world *world, t_renderer *renderer, t_timer *timer);


/** particles */
void			loadParticleTextures(t_renderer *renderer);
void 			loadParticles(t_renderer *renderer);
void 			updateParticles(t_renderer *renderer);
void 			addParticle(t_renderer *renderer, t_particle particle);
t_particle		new_particle(t_vec3 pos, t_vec3 scal, t_vec3 rot, t_vec3 color,
				int id, GLuint texture_id, float life);

#endif

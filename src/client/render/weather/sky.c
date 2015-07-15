/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 15:48:50 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/24 14:52:54 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/main.h"

static void	skyboxDelete(t_sky *sky)
{
    unsigned i;

    for (i = 0 ; i < CUBEMAP_MAX ; i++)
    {
        glDeleteTextures(1, &(sky->cubemaps[i]));
    }
}

void		skyDelete(t_sky *sky)
{
	skyboxDelete(sky);
    glhDeleteVAO(&(sky->vaoID));
    glhDeleteVBO(&(sky->vboID));
}

static void	loadCubemap(GLuint *id, char *identifier)
{
    char       *files[] = {"right", "left", "top", "bottom", "back", "front"};
    char       buffer[128];
	t_texture  texture;
	int        i;

    glGenTextures(1, id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *id);
    for (i = 0; i < 6; i++)
    {
        memset(buffer, 0, sizeof(buffer));
    	sprintf(buffer, "./assets/textures/skybox/%s_%s.bmp", files[i], identifier);
	    if (loadBmpFile(buffer, &texture) == -1)
    	{
    		logger_log(LOG_WARNING, "Couldnt get skybox face: %s", buffer);
    		continue ;
    	}
        logger_log(LOG_FINE, "Skybox face loaded: %s", buffer);
        bmpReverseYs(&texture);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.pixels);
        free(texture.pixels);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

static void loadSkyboxModel(t_renderer *renderer)
{
    GLfloat skybox_vertices[] = {
        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
        SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

         SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,

        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
        -SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

        -SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
        -SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
         SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE
    };
    renderer->sky.vertex_count = sizeof(skybox_vertices) / sizeof(GLfloat) / 3;
    renderer->sky.vaoID = glhGenVAO();
    glBindVertexArray(renderer->sky.vaoID);
    {
        renderer->sky.vboID = glhGenVBO();
        glBindBuffer(GL_ARRAY_BUFFER, renderer->sky.vboID);
        glhVBOData(GL_ARRAY_BUFFER, skybox_vertices, sizeof(skybox_vertices), GL_STATIC_DRAW);
        glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

void        loadSky(t_renderer *renderer)
{
    t_program   *program;

    loadSkyboxModel(renderer);
    program = renderer->programs + PROGRAM_SKYBOX;
    loadCubemap(renderer->sky.cubemaps + CUBEMAP_DAY, "day");
    loadCubemap(renderer->sky.cubemaps + CUBEMAP_NIGHT, "night");
    glUseProgram(program->id);
    loadUniformInt(program->cubemap_day, 0);
    loadUniformInt(program->cubemap_night, 1);
    glUseProgram(0);
    renderer->sky.rot = new_vec3(0, 0, 0);
}
# include "maths.h"
static void calculateSunPos(t_world *world, t_renderer *renderer, float tick_ratio)
{
    float   x;
    float   r;
    int     i;
    float   pi4;
    float   f;

    pi4 = M_PI / 4.0f;
    x = tick_ratio * M_PI * 2;
    f = 0;
    for (i = 1 ; i < 8 ; i++)
    {
        if (x < pi4 * i)
        {
            f = (x - pi4 * (i - 1)) / pi4;
            if (i % 2 == 0)
            {
                f = 1 - f;
            }
            break ;
        }
    }
    r = SKYBOX_SIZE + (SKYBOX_DIAGONAL - SKYBOX_SIZE) * (f * f * f);
    world->weather.sun_pos.x = cos(x) * r + renderer->camera.pos.x;
    world->weather.sun_pos.y = sin(x) * r + renderer->camera.pos.y;
    world->weather.sun_pos.z = renderer->camera.pos.z;
}


void        updateSky(t_world *world, t_renderer *renderer, t_timer *timer)
{
    calculateSunPos(world, renderer, timer->ratio);
    calculateSunColor(world, renderer, timer->ratio);
    renderer->sky.rot.y += 0.0001f;
}

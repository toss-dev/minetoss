/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/23 12:05:50 by rpereira          #+#    #+#             */
/*   Updated: 2015/04/23 12:17:46 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_GL_H
# define OPEN_GL_H

# ifdef __APPLE__
# 	define GLFW_INCLUDE_GLCOREARB
# endif

# ifdef _WIN32
# 	include <GL/glew.h>
# endif
# include <GLFW/glfw3.h>

# include "maths.h"

typedef struct 	s_glh_context
{
	unsigned		vaos;
	unsigned		vaos_total;
	unsigned        vbos;
	unsigned        vbos_total;
	unsigned long	memory;
	unsigned long	memory_total;
}				t_glh_context;

typedef struct 	s_window
{
	GLFWwindow	*ptr;
}				t_window;

typedef struct 	s_program
{
	GLuint	id;
	GLuint	vertex_shader;
	GLuint 	fragment_shader;

//	GLuint	*uniforms;
//	TODO: replace this bordel with an array

	GLuint	proj_matrix;
	GLuint	view_matrix;
	GLuint	transf_matrix;
	GLuint	fog_color;
	GLuint 	fog_density;
	GLuint 	fog_gradient;
	GLuint	sun_position;
	GLuint	sun_color;
	GLuint	particle_color;
	GLuint 	texture_atlas_cols;
	GLuint 	texture_atlas_lines;
	GLuint 	particle_texture_atlas_id;
	GLuint	cubemap_day;
	GLuint	cubemap_night;
	GLuint	day_ratio;
	GLuint	day_factor;
}				t_program;

/** opengl helper functions (see gl_helper.c) */
GLuint 			glhGenVAO(void);
void 			glhDeleteVAO(GLuint *vao);
GLuint			glhGenVBO(void);
void  			glhVBOData(GLenum dest, void *floats, GLsizeiptr size, GLenum gltype);
void   			glhVBOClear(GLenum dest, unsigned size, GLenum gltype);
void    		glhVertexAttribPointer(GLuint index, GLint vertex_size, GLuint stride, GLuint offset);
void  		  	glhDeleteVBO(GLuint *vbo, unsigned int size);
void   			glhUseProgram(t_program *program);
void    		glhStopUseProgram(void);
GLuint  		glhCheckError(char const *str);

/** has to be call on program initialization*/
void    glhSetContext(t_glh_context *context);

/** print current context informations */
void    glhPrintContext(char const *str);

/** vertex*/
typedef struct 	s_vertex
{
	t_vec3	pos;
	t_vec3	normal;
	t_vec2	uv;
}				t_vertex;

t_vertex		new_vertex(t_vec3 pos, t_vec3 normal, t_vec2 uv);
void			vertex_to_float_buffer(float buffer[3 + 3 + 2], t_vertex *vertex);


/** models */
enum 	e_vao_attr
{
	ATTR_POSITION,
	ATTR_NORMAL,
	ATTR_UV,
	ATTR_MAX
};

typedef struct 	s_model
{
	GLuint	vaoID;
	GLuint	vboID;
	GLuint	vertex_count;
	GLenum	glmode;
}				t_model;

t_model			new_model(GLenum glmode);
bool			initModel(t_model *model, t_vertex *vertices, unsigned vertex_count);
bool 			updateModelVBO(t_model *model, t_vertex *vertices, unsigned vertex_count);
void 			renderModel(t_model *model);
void 			modelDelete(t_model *model);

#endif

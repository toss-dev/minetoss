/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.h                                           :+:      :+:    :+:   */
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

# if defined(_WIN32) || defined(__CYGWIN__)
# 	include <windef.h>
#	define GLEW_STATIC
# 	include <GL/glew.h>
# endif

# include <GLFW/glfw3.h>

# include "maths.h"

typedef struct 	s_window
{
	GLFWwindow	*ptr;
}				t_window;

enum e_uniforms_variable
{
	U_PROJ_MATRIX,
	U_VIEW_MATRIX,
	U_TRANSF_MATRIX,
	U_FOG_COLOR,
	U_FOG_DENSITY,
	U_FOG_GRADIENT,
	U_SUN_POSITION,
	U_SUN_COLOR,
	U_CUBEMAP_DAY,
	U_CUBEMAP_NIGHT,
	U_DAY_RATIO,
	U_DAY_FACTOR,
	U_FONT_COLOR,
	U_USE_ANIMATION,
	U_ANIM_TRANSF_MATRIX,
	U_MAX
};

typedef struct 	s_program
{
	GLuint	id;
	GLuint	vertex_shader;
	GLuint 	fragment_shader;
	GLuint	uniforms[U_MAX];
}				t_program;

/** opengl helper functions (see gl_helper.c) */
GLuint 			glhGenVAO(void);
void 			glhDeleteVAO(GLuint *vao);
GLuint			glhGenVBO(void);
void  			glhVBOData(GLenum dest, void *floats, GLsizeiptr size, GLenum gltype);
void    		glhVertexAttribPointer(GLuint index, GLint vertex_size, GLuint stride, GLuint offset);
void  		  	glhDeleteVBO(GLuint *vbo);
void   			glhUseProgram(t_program *program);
void    		glhStopUseProgram(void);
GLuint			glhLoadTexture(char const *file);
GLuint  		glhCheckError(char const *str);

/** opengl function wrapper */

void			glhLoadUniformMatrix(t_program *program, unsigned int id, float *matrix);
void			glhLoadUniformFloat(t_program *program, unsigned int id, float value);
void			glhLoadUniformVec(t_program *program, unsigned int id, t_vec3 p);
void			glhLoadUniformInt(t_program *program, unsigned int id, GLuint integer);


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

enum e_model_state
{
	MODEL_INITIALIZED = 1,
	MODEL_UPDATE_TO_DATE = 2,
	MODEL_VERTICES_UP_TO_DATE = 4,
	MODEL_VBO_UP_TO_DATE = 8,
	MODEL_CLEARED = 16
};

typedef struct 	s_model
{
	GLuint	vaoID;
	GLuint	vboID;
	t_vertex *vertices;
	GLuint	vertex_count;
	GLenum	glmode;
	char	state;	
}				t_model;

t_model			new_model(GLenum glmode);
int 			updateModelVBO(t_model *model);
int				clearModelVBO(t_model *model);
void 			renderModel(t_model *model);
void 			modelDelete(t_model *model);
void 			modelSetState(t_model *model, unsigned state);
void 			modelUnsetState(t_model *model, unsigned state);
int 			modelHasState(t_model *model, unsigned state);
void 			setModelVertices(t_model *model, t_vertex *vertices, unsigned vertex_count);

#endif

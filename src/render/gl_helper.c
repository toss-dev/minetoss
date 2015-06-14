/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 02:09:13 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/05 02:09:17 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

# define BUFFER_OFFSET(X) (NULL + X)

t_glh_context   *g_context = NULL;

void    glhSetContext(t_glh_context *context)
{
    g_context = context;
    g_context->vaos = 0;
    g_context->vaos_total = 0;
    g_context->vbos = 0;
    g_context->vbos_total = 0;
    g_context->memory = 0;
    g_context->memory_total = 0;
}

void    glhPrintContext(char const *str)
{
    logger_log(LOG_FINE,
            "glh context: %s\
            \n\t\t\tcurrent number of vaos: %u\
            \n\t\t\ttotal vaos created: %u\
            \n\t\t\tcurrent number of vbos: %u\
            \n\t\t\ttotal vbos created: %u\
            \n\t\t\tgpu usage: %lu octets (%lu ko ; %lu mo)\
            \n\t\t\ttotal memory sent to gpu: %lu octets (%lu ko ; %lu mo)",
            str,
            g_context->vaos, g_context->vaos_total,
            g_context->vbos, g_context->vbos_total,
            g_context->memory, g_context->memory / 1024, g_context->memory / 1024 / 1024,
            g_context->memory_total, g_context->memory_total / 1024, g_context->memory_total / 1024 / 1024);
}

/** return a new vao id */
GLuint  glhGenVAO(void)
{
    GLuint  vao;

    glGenVertexArrays(1, &vao);
    g_context->vaos++;
    g_context->vaos_total++;
    return (vao);
}

/** return a new vbo id */
GLuint  glhGenVBO(void)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    g_context->vbos++;
    g_context->vbos_total++;
    return (vbo);
}

/** delete the given vao */
void    glhDeleteVAO(GLuint *vao)
{
    glDeleteBuffers(1, vao);
    g_context->vaos--;
}

/** delete given vbo, size is only important for memory checking, put 0 if you're not interesting in */
void    glhDeleteVBO(GLuint *vbo, unsigned int size)
{
    glDeleteBuffers(1, vbo);
    g_context->vbos--;
    g_context->memory -= size;
}

/**
**  set binded vbo ( `glBindBuffer(int vboID)` to vao attribute list at given index
** 
**  index: index in attribute list (see `ATTR_DEFINE`)
**  vertex_size: number of floats per vertex
*/
void    glhVertexAttribPointer(GLuint index, GLint vertex_size, GLuint stride, GLuint offset)
{
    glVertexAttribPointer(
        index,
        vertex_size,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * stride,
        BUFFER_OFFSET(offset * sizeof(GLfloat)));
}

/**
**  set data to binded vbo
**  
**  dest: GL_ARRAY_BUFFER ; GL_ELEMENT_ARRAY_BUFFER ...
**  size: size in byte of the given data
**  floats: data to set to the buffer
*/
void    glhVBOData(GLenum dest, void *floats, GLsizeiptr size, GLenum glmode)
{
    g_context->memory += size;
    g_context->memory_total += size;
    glBufferData(dest, size, floats, glmode);
}

/** size is the size of the current bounded vbo */
void    glhVBOClear(GLenum dest, unsigned size, GLenum glmode)
{
    g_context->memory -= size;
    glBufferData(dest, 0, NULL, glmode);
}

/** start using given program */
void    glhUseProgram(t_program *program)
{
    glUseProgram(program->id);
}

/** stop using program in use */
void    glhStopUseProgram(void)
{
    glUseProgram(0);
}


GLuint  glhCheckError(char const *str)
{
    static GLuint error[5] = {
        GL_NO_ERROR, GL_INVALID_ENUM, GL_INVALID_VALUE, GL_INVALID_OPERATION, GL_OUT_OF_MEMORY
    };
    static char *error_str[5] = {
        "GL_NO_ERROR", "GL_INVALID_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION", "GL_OUT_OF_MEMORY"
    };

    unsigned    err;
    int         i;

    err = glGetError();
    if (err != 0)
    {
        for (i = 0 ; i < 5 ; i++)
        {
            if (error[i] == err)
                break ;
        }
        logger_log(LOG_WARNING, "%s : OpenGL error occured : %d : %s", str, err, error_str[i]);
    }
    return (err);
}

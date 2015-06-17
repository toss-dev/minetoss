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


/** return a new vao id */
GLuint  glhGenVAO(void)
{
    GLuint  vao;

    glGenVertexArrays(1, &vao);
    return (vao);
}

/** return a new vbo id */
GLuint  glhGenVBO(void)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    return (vbo);
}

/** delete the given vao */
void    glhDeleteVAO(GLuint *vao)
{
    glDeleteBuffers(1, vao);
}

/** delete given vbo, size is only important for memory checking, put 0 if you're not interesting in */
void    glhDeleteVBO(GLuint *vbo)
{
    glDeleteBuffers(1, vbo);
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
    glBufferData(dest, size, floats, glmode);
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

/** load a texture to gl uint */
GLuint glhLoadTexture(char const *file)
{
    char        texture_file[256];
    t_texture   texture;
    GLuint      textureID;

    sprintf(texture_file, "./assets/textures/%s", file);
    logger_log(LOG_FINE, "Loading texture file: %s", texture_file);
    glGenTextures(1, &textureID);
    if (loadPngFile(texture_file, &texture) == -1)
    {
        return (0);
    }
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, texture.internalformat,
                    texture.width, texture.height, 0,
                    texture.format, GL_UNSIGNED_BYTE, texture.pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    free(texture.pixels);
    return (textureID);
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

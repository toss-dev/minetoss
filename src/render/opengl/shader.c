/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 12:55:18 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 17:49:06 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			shaderDelete(GLuint program_id, GLuint shader_id)
{
	glDetachShader(program_id, shader_id);
	glDeleteShader(shader_id);
}

static void		print_log(GLuint object)
{
	char 	*log;
	GLint	log_length;

	log_length = 0;
	if (glIsShader(object))
	{
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else if (glIsProgram(object))
	{
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else
	{
		logger_log(LOG_ERROR, "Not a shader program");
	}
	log = malloc(sizeof(char) * (log_length + 1));
	log[log_length] = 0;
	if (glIsShader(object))
	{
		glGetShaderInfoLog(object, log_length, NULL, log);
	}
	else if (glIsProgram(object))
	{
		glGetProgramInfoLog(object, log_length, NULL, log);
	}
	logger_log(LOG_ERROR, "Error on shader program:\n%s\n", log);
	free(log);
}

static GLchar	*map_file(char const *file)
{
	FILE	*fp;
	size_t	size;
	GLchar	*buffer;

	fp = fopen(file, "rb");
	if (fp == NULL)
		return (NULL);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	if ((buffer = malloc(size + 1)) == NULL)
		return (NULL);
	fread(buffer, size, 1, fp);
	buffer[size] = 0;
	fclose(fp);
	return (buffer);
}

GLuint			loadShader(char const *str, GLenum type)
{
	GLuint			shader;
	GLchar const	*file;
	GLint			compilation;

	logger_log(LOG_FINE, "Loading shader: %s", str);
	if ((file = map_file(str)) == NULL)
	{
		logger_log(LOG_ERROR, "Cant map shader program");
		return (0);
	}
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &file, NULL);
	free((void*)file);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation);
	if (compilation == GL_FALSE)
	{
		print_log(shader);
		return (0);
	}
	logger_log(LOG_FINE, "... loaded properly.");
	return (shader);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 09:38:33 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/09 22:01:25 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	read_header(int fd, t_bmp *bmp, t_texture *texture)
{
	if (read(fd, bmp->header, sizeof(bmp->header)) != BMP_HEADER_SIZE)
		return ;
	if (bmp->header[0] != 'B' || bmp->header[1] != 'M')
		return ;
	bmp->data_idx = *((int*)(bmp->header + 0x0A));
	texture->width = *((int*)(bmp->header + 0x12));
	texture->height = *((int*)(bmp->header + 0x16));
	if (bmp->data_idx < BMP_HEADER_SIZE)
		bmp->data_idx = BMP_HEADER_SIZE;
}

static void	read_file(int fd, t_bmp *bmp, t_texture *texture)
{
	unsigned char	tmp[bmp->data_idx - BMP_HEADER_SIZE];
	size_t			size;

	read(fd, tmp, sizeof(tmp));
	size = texture->width * texture->height * 3;
	texture->pixels = (GLubyte*)malloc(size);
	if (texture->pixels == NULL)
		return ;
	read(fd, texture->pixels, size);
}

int			loadBmpFile(char const *file, t_texture *texture)
{
	t_bmp	bmp;
	int		fd;

	texture->internalformat = GL_RGB;
	texture->format = GL_BGR;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	read_header(fd, &bmp, texture);
	read_file(fd, &bmp, texture);
	close(fd);
	return (1);
}

void		bmpReverseYs(t_texture *texture)
{
	char			*buffer;
	unsigned int	i;
	int 			sizeline;
	int				top;
	int				bot;

	sizeline = texture->width * 3;
	buffer = (char*)malloc(sizeof(char) * sizeline);
	for (i = 0 ; i < texture->height / 2 ; i++)
	{
		bot = i * sizeline;
		top = (texture->height - 1 - i) * sizeline;
		memcpy(buffer, texture->pixels + bot, sizeline);
		memcpy(texture->pixels + bot, texture->pixels + top, sizeline);
		memcpy(texture->pixels + top, buffer, sizeline);
	}
	free(buffer);
}

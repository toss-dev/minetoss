/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:06:05 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/03 00:06:13 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define WIDTH 1000
# define HEIGHT (WIDTH / (16 / 9.0f))
# define TITLE ("Hello u")

# define CHUNK_HASHTABLE_SIZE 16384
# define PARTICLES_MAX 4096

# define MESH_PER_TERRAIN 4

# define TERRAIN_SIZEX 16
# define TERRAIN_SIZEY 64
# define TERRAIN_SIZEZ 16
# define MESH_SIZEY (TERRAIN_SIZEY / MESH_PER_TERRAIN)

# define CHUNK_ROUGHNESS (TERRAIN_SIZEY / 2)
# define CHUNK_BASE_HEIGHT (TERRAIN_SIZEY / 2)

# define TERRAIN_RENDER_DISTANCE 16
# define TERRAIN_LOAD_DISTANCE (TERRAIN_RENDER_DISTANCE + 4)
# define TERRAIN_KEEP_LOAD_DISTANCE (TERRAIN_RENDER_DISTANCE + 8)

# define SKYBOX_SIZE 100
# define SKYBOX_DIAGONAL (sqrt(SKYBOX_SIZE * SKYBOX_SIZE * 2))

#endif
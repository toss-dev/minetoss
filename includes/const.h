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

# define WORLD_MAX_HEIGHT 256
# define MESH_PER_TERRAIN 8

# define TERRAIN_SIZEX 32
# define TERRAIN_SIZEY WORLD_MAX_HEIGHT
# define TERRAIN_SIZEZ 32
# define MESH_SIZEY (WORLD_MAX_HEIGHT / MESH_PER_TERRAIN)

# define CHUNK_ROUGHNESS (TERRAIN_SIZEY / 4)
# define CHUNK_BASE_HEIGHT (TERRAIN_SIZEY / 2)

# define TERRAIN_RENDER_DISTANCE 6									//distance where the chunk keep rendered
# define TERRAIN_LOAD_DISTANCE (TERRAIN_RENDER_DISTANCE + 2)		//distance where the chunk keep being updated

# define SKYBOX_SIZE 100
# define SKYBOX_DIAGONAL (sqrt(SKYBOX_SIZE * SKYBOX_SIZE * 2))

# define GET_TERRAIN_KEY(X, Y) char Y[64]; generateTerrainKey(Y, terrain->index)

#endif

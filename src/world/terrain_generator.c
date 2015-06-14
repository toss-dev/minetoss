/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 11:42:21 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/06 22:43:43 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

# define F2 (0.5f * (sqrt(3.0f) - 1.0f))
# define G2 ((3.0f - sqrt(3.0f)) / 6.0f)

t_vec2	grad3[] = {
	{1, 1},
	{-1, 1},
	{1, -1},
	{-1, -1},
	{1, 0},
	{-1, 0},
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
	{0, 1},
	{0, -1}
};

short		temp[] = {
	151, 160, 137, 91, 90, 15, 8, 99, 37, 240, 21, 10, 23, 131, 13, 201,
	95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 190, 6, 148,
	247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
	57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 8, 175,
	74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
	60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
	65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
	200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
	3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82,
	85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183,
	170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167,
	43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
	185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191,
	179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181,
	199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138,
	236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

short	*p;
short	*perm;
short	*permMod12;

static void prepareNoise(void)
{
    int     i;
    int     from;
    int     to;
    short   tmp;

    memcpy(p, temp, sizeof(temp));
    for (i = 0 ; i < 400 ; i++)
    {
        from = rand() % (sizeof(temp) / sizeof(float));
        to = rand() % (sizeof(temp) / sizeof(float));
        tmp = p[from];
        p[from] = p[to];
        p[to] = tmp;
    }

    for (i = 0 ; i < 512 ; i++)
    {
        perm[i] = p[i & 255];
        permMod12[i] = (short)(perm[i] % 12);
    }
}

/** called at initialization */
void            loadWorldGenerator(void)
{
    srand(time(NULL));
	p = (short*)malloc(sizeof(temp));
	perm = (short*)malloc(sizeof(short) * 512);
	permMod12 = (short*)malloc(sizeof(short) * 512);
    prepareNoise();
}

static double noise(double xin, double yin)
{
	double n0, n1, n2;
	double s = (xin + yin) * F2;
	int i = fastfloor(xin + s);
	int j = fastfloor(yin + s);
	double t = (i + j) * G2;
	double X0 = i - t;
	double Y0 = j - t;
	double x0 = xin - X0;
	double y0 = yin - Y0;
	int i1 = (x0 > y0) ? 1 : 0;
	int j1 = (x0 > y0) ? 0 : 1;
    double x1 = x0 - i1 + G2;
    double y1 = y0 - j1 + G2;
    double x2 = x0 - 1.0 + 2.0 * G2;
    double y2 = y0 - 1.0 + 2.0 * G2;
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = permMod12[ii + perm[jj]];
    int gi1 = permMod12[ii + i1 + perm[jj + j1]];
    int gi2 = permMod12[ii + 1 + perm[jj + 1]];
    double t0 = 0.5f - x0 * x0 - y0 * y0;

    if(t0 < 0)
    {
    	n0 = 0.0f;
    }
    else
    {
      t0 *= t0;
      n0 = t0 * t0 * vec2_dot(grad3[gi0], new_vec2(x0, y0));
    }

    double t1 = 0.5 - x1 * x1 - y1 * y1;
    if (t1 < 0)
    {
    	n1 = 0.0f;
    }
    else
    {
    	t1 *= t1;
    	n1 = t1 * t1 * vec2_dot(grad3[gi1], new_vec2(x1, y1));
    }

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    if (t2 < 0)
    {
    	n2 = 0.0f;
    }
    else
    {
    	t2 *= t2;
    	n2 = t2 * t2 * vec2_dot(grad3[gi2], new_vec2(x2, y2));
    }
    return (70.0 * (n0 + n1 + n2));
}

static void	stabilizeNoise(t_terrain *terrain, float ys[TERRAIN_SIZEX][TERRAIN_SIZEZ])
{
    t_point3    pos;
    int         r;

	for (pos.x = 0 ; pos.x < TERRAIN_SIZEX ; pos.x++)
    {
    	for (pos.z = 0 ; pos.z < TERRAIN_SIZEZ ; pos.z++)
    	{
            ys[pos.x][pos.z] = clamp(ys[pos.x][pos.z], -1.5f, 1.5f);
            pos.y = clamp(CHUNK_BASE_HEIGHT + ys[pos.x][pos.z] * CHUNK_ROUGHNESS, 0, TERRAIN_SIZEY - 1);
            terrain->blocks[pos.x][pos.y][pos.z] = BLOCK_GRASS;
            r = rand() % 4 + 4;
            while (r && pos.y > 2)
            {
                --pos.y;
                terrain->blocks[pos.x][pos.y][pos.z] = BLOCK_DIRT;
                --r;
            }
            while (pos.y > 2)
            {
                terrain->blocks[pos.x][pos.y][pos.z] = BLOCK_STONE;
                pos.y--;
            }
            r = rand() % 2 + 2;
            while (r >= 0)
            {
                terrain->blocks[pos.x][r][pos.z] = BLOCK_BEDROCK;
                --r;
            }
        }
    }
}

/**
**  generate base height for terrain and fill the ground with dirt / stone / bedrock
*/
static void		generateTerrainSurface(t_terrain *terrain)
{
    float   ys[TERRAIN_SIZEX][TERRAIN_SIZEZ];
	float	layerF;
    float	weight;
    int 	i;
    int 	x;
    int 	z;
    int 	posx;
    int 	posz;

    layerF = 0.0005f;
    weight = 2.0f;
    memset(ys, 0, sizeof(ys));
    for (i = 0 ; i < 3 ; i++)
    {
        for (x = 0 ; x < TERRAIN_SIZEX ; x++)
        {
        	for (z = 0 ; z < TERRAIN_SIZEZ ; z++)
        	{
                posx = terrain->index.x * TERRAIN_SIZEX + x;
        		posz = terrain->index.z * TERRAIN_SIZEZ + z;
        		ys[x][z] += noise(posx * layerF, posz * layerF) * weight;
            }
        }
        layerF *= 3.5f;
        weight *= 0.5f;
    }
    stabilizeNoise(terrain, ys);
}

/** main terrain generation for terrain at height 0 */
void    generateTerrain(t_terrain *terrain)
{
    generateTerrainSurface(terrain);
    terrainSetState(terrain, TERRAIN_GENERATED);
}
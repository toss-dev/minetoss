/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_maths.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:33:12 by rpereira          #+#    #+#             */
/*   Updated: 2015/05/12 22:40:39 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATHS_H
# define LIBFT_MATHS_H

# include <math.h>
# include "libft.h"

# ifndef M_PI
#	define M_PI 3.1415926f
# endif

# define TO_DEGREE(x) ((int)(180 * x / M_PI) % 360)
# define TO_RADIAN(x) (x / 180.0f * M_PI)

typedef struct	s_vec2
{
	float	x;
	float	y;
}				t_vec2;

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef struct 	s_point2
{
	int x;
	int y;
}				t_point2;

typedef struct 	s_point3
{
	int x;
	int y;
	int z;
}				t_point3;

/*
**	Matrix loaders
*/
void	matrix_rotate(float *m, t_vec3 axis, float angle);
void	matrix_scale(float *m, t_vec3 scale);
void	matrix_translate(float *m, t_vec3 transformation);
void	matrix_identity(float *m);
void	matrix_view(float *matrix, float pitc, float yaw, float roll, t_vec3 pos);
float	*matrix_projection(float fov, float n, float f, float aspect);
t_vec3	vec3_pitch_yaw(float pitch, float yaw);

/** points*/
t_point2	new_point2(int x, int y);
int			point2_dist(t_point2 p1, t_point2 p2);

t_point3	new_point3(int x, int y, int z);
int			point3_dist(t_point3 p1, t_point3 p2);

t_vec2		to_vec2(t_point2 point);
t_vec3		to_vec3(t_point3 point);
t_point2	to_point2(t_vec2 vec);
t_point3	to_point3(t_vec3 vec);

/**
**	maths utils
*/
int		fastfloor(double x);
float	clamp(float val, float min, float max);

/*
**	vec2 functions
*/
t_vec2	new_vec2(float x, float y);
double	vec2_dist(t_vec2 a, t_vec2 b);
double 	vec2_dot(t_vec2 a, t_vec2 b);
double	vec2_dot_product(t_vec2 a, t_vec2 b);

/*
**	Matrix utils functions
*/
void	matrix_copy(float *dst, float *src);
float	*matrix_combine(float *m1, float *m2);
void	matrix_inverse(float *matrix);
float	*new_matrix(void);

/** math cos sin */
void	prepareCosSin(void);
float	ft_cosi(int i);
float	ft_sini(int i);
float	ft_cosf(float f);
float	ft_sinf(float f);

/*
**	vec3 | point4 functions
*/
t_vec3	new_vec3(float x, float y, float z);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_copy(t_vec3 point);
double	vec3_dist(t_vec3 v1, t_vec3 v2);
double	vec3_square_dist(t_vec3 v1, t_vec3 v2);
int		vec3_equals(t_vec3 v1, t_vec3 v2);
t_vec3	matrix_apply_vec3(float *m, t_vec3 p3);

/*
**	Vec functions (vec == t_vec3)
*/
double	vec3_norm(t_vec3 vec);
double	vec3_square_norm(t_vec3 vec);
t_vec3	vec3_normalize(t_vec3 vec);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_multiply(t_vec3 a, double r);
double	vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b);

float	barrycentric(t_vec3 v1, t_vec3 v2, t_vec3 p3, t_vec2 pos);

#endif

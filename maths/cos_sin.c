/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_sin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 18:26:56 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/04 18:29:22 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
**	Generate cos and sin buffer values, which will be accesed (and rounded) 
**	via ft_cos / ft_sin functions
**
**	prepareCosSin() function should be call if you want to use wrapper functions
*/

float		*g_cos_values = NULL;
float		*g_sin_values = NULL;
unsigned	g_values_count = 0;

void	prepareCosSin(void)
{
	float	cos_values[360] = {
		1.0000f, 0.9998f, 0.9994f, 0.9986f, 0.9976f, 0.9962f, 0.9945f, 0.9925f,
		0.9903f, 0.9877f, 0.9848f, 0.9816f, 0.9781f, 0.9744f, 0.9703f, 0.9659f,
		0.9613f, 0.9563f, 0.9511f, 0.9455f, 0.9397f, 0.9336f, 0.9272f, 0.9205f,
		0.9135f, 0.9063f, 0.8988f, 0.8910f, 0.8829f, 0.8746f, 0.8660f, 0.8572f,
		0.8480f, 0.8387f, 0.8290f, 0.8192f, 0.8090f, 0.7986f, 0.7880f, 0.7771f,
		0.7660f, 0.7547f, 0.7431f, 0.7314f, 0.7193f, 0.7071f, 0.6947f, 0.6820f,
		0.6691f, 0.6561f, 0.6428f, 0.6293f, 0.6157f, 0.6018f, 0.5878f, 0.5736f,
		0.5592f, 0.5446f, 0.5299f, 0.5150f, 0.5000f, 0.4848f, 0.4695f, 0.4540f,
		0.4384f, 0.4226f, 0.4067f, 0.3907f, 0.3746f, 0.3584f, 0.3420f, 0.3256f,
		0.3090f, 0.2924f, 0.2756f, 0.2588f, 0.2419f, 0.2250f, 0.2079f, 0.1908f,
		0.1736f, 0.1564f, 0.1392f, 0.1219f, 0.1045f, 0.0872f, 0.0698f, 0.0523f,
		0.0349f, 0.0175f, 0.0000f, -0.0175f, -0.0349f, -0.0523f, -0.0698f, -0.0872f,
		-0.1045f, -0.1219f, -0.1392f, -0.1564f, -0.1736f, -0.1908f, -0.2079f, -0.2250f,
		-0.2419f, -0.2588f, -0.2756f, -0.2924f, -0.3090f, -0.3256f, -0.3420f, -0.3584f,
		-0.3746f, -0.3907f, -0.4067f, -0.4226f, -0.4384f, -0.4540f, -0.4695f, -0.4848f,
		-0.5000f, -0.5150f, -0.5299f, -0.5446f, -0.5592f, -0.5736f, -0.5878f, -0.6018f,
		-0.6157f, -0.6293f, -0.6428f, -0.6561f, -0.6691f, -0.6820f, -0.6947f, -0.7071f,
		-0.7193f, -0.7314f, -0.7431f, -0.7547f, -0.7660f, -0.7771f, -0.7880f, -0.7986f,
		-0.8090f, -0.8192f, -0.8290f, -0.8387f, -0.8480f, -0.8572f, -0.8660f, -0.8746f,
		-0.8829f, -0.8910f, -0.8988f, -0.9063f, -0.9135f, -0.9205f, -0.9272f, -0.9336f,
		-0.9397f, -0.9455f, -0.9511f, -0.9563f, -0.9613f, -0.9659f, -0.9703f, -0.9744f,
		-0.9781f, -0.9816f, -0.9848f, -0.9877f, -0.9903f, -0.9925f, -0.9945f, -0.9962f,
		-0.9976f, -0.9986f, -0.9994f, -0.9998f, -1.0000f, -0.9998f, -0.9994f, -0.9986f,
		-0.9976f, -0.9962f, -0.9945f, -0.9925f, -0.9903f, -0.9877f, -0.9848f, -0.9816f,
		-0.9781f, -0.9744f, -0.9703f, -0.9659f, -0.9613f, -0.9563f, -0.9511f, -0.9455f,
		-0.9397f, -0.9336f, -0.9272f, -0.9205f, -0.9135f, -0.9063f, -0.8988f, -0.8910f,
		-0.8829f, -0.8746f, -0.8660f, -0.8572f, -0.8480f, -0.8387f, -0.8290f, -0.8192f,
		-0.8090f, -0.7986f, -0.7880f, -0.7771f, -0.7660f, -0.7547f, -0.7431f, -0.7314f,
		-0.7193f, -0.7071f, -0.6947f, -0.6820f, -0.6691f, -0.6561f, -0.6428f, -0.6293f,
		-0.6157f, -0.6018f, -0.5878f, -0.5736f, -0.5592f, -0.5446f, -0.5299f, -0.5150f,
		-0.5000f, -0.4848f, -0.4695f, -0.4540f, -0.4384f, -0.4226f, -0.4067f, -0.3907f,
		-0.3746f, -0.3584f, -0.3420f, -0.3256f, -0.3090f, -0.2924f, -0.2756f, -0.2588f,
		-0.2419f, -0.2250f, -0.2079f, -0.1908f, -0.1736f, -0.1564f, -0.1392f, -0.1219f,
		-0.1045f, -0.0872f, -0.0698f, -0.0523f, -0.0349f, -0.0175f, -0.0000f, 0.0175f,
		0.0349f, 0.0523f, 0.0698f, 0.0872f, 0.1045f, 0.1219f, 0.1392f, 0.1564f,
		0.1736f, 0.1908f, 0.2079f, 0.2250f, 0.2419f, 0.2588f, 0.2756f, 0.2924f,
		0.3090f, 0.3256f, 0.3420f, 0.3584f, 0.3746f, 0.3907f, 0.4067f, 0.4226f,
		0.4384f, 0.4540f, 0.4695f, 0.4848f, 0.5000f, 0.5150f, 0.5299f, 0.5446f,
		0.5592f, 0.5736f, 0.5878f, 0.6018f, 0.6157f, 0.6293f, 0.6428f, 0.6561f,
		0.6691f, 0.6820f, 0.6947f, 0.7071f, 0.7193f, 0.7314f, 0.7431f, 0.7547f,
		0.7660f, 0.7771f, 0.7880f, 0.7986f, 0.8090f, 0.8192f, 0.8290f, 0.8387f,
		0.8480f, 0.8572f, 0.8660f, 0.8746f, 0.8829f, 0.8910f, 0.8988f, 0.9063f,
		0.9135f, 0.9205f, 0.9272f, 0.9336f, 0.9397f, 0.9455f, 0.9511f, 0.9563f,
		0.9613f, 0.9659f, 0.9703f, 0.9744f, 0.9781f, 0.9816f, 0.9848f, 0.9877f,
		0.9903f, 0.9925f, 0.9945f, 0.9962f, 0.9976f, 0.9986f, 0.9994f, 0.9998f
	};

	float	sin_values[360] = {
		0.0000f, 0.0175f, 0.0349f, 0.0523f, 0.0698f, 0.0872f, 0.1045f, 0.1219f,
		0.1392f, 0.1564f, 0.1736f, 0.1908f, 0.2079f, 0.2250f, 0.2419f, 0.2588f,
		0.2756f, 0.2924f, 0.3090f, 0.3256f, 0.3420f, 0.3584f, 0.3746f, 0.3907f,
		0.4067f, 0.4226f, 0.4384f, 0.4540f, 0.4695f, 0.4848f, 0.5000f, 0.5150f,
		0.5299f, 0.5446f, 0.5592f, 0.5736f, 0.5878f, 0.6018f, 0.6157f, 0.6293f,
		0.6428f, 0.6561f, 0.6691f, 0.6820f, 0.6947f, 0.7071f, 0.7193f, 0.7314f,
		0.7431f, 0.7547f, 0.7660f, 0.7771f, 0.7880f, 0.7986f, 0.8090f, 0.8192f,
		0.8290f, 0.8387f, 0.8480f, 0.8572f, 0.8660f, 0.8746f, 0.8829f, 0.8910f,
		0.8988f, 0.9063f, 0.9135f, 0.9205f, 0.9272f, 0.9336f, 0.9397f, 0.9455f,
		0.9511f, 0.9563f, 0.9613f, 0.9659f, 0.9703f, 0.9744f, 0.9781f, 0.9816f,
		0.9848f, 0.9877f, 0.9903f, 0.9925f, 0.9945f, 0.9962f, 0.9976f, 0.9986f,
		0.9994f, 0.9998f, 1.0000f, 0.9998f, 0.9994f, 0.9986f, 0.9976f, 0.9962f,
		0.9945f, 0.9925f, 0.9903f, 0.9877f, 0.9848f, 0.9816f, 0.9781f, 0.9744f,
		0.9703f, 0.9659f, 0.9613f, 0.9563f, 0.9511f, 0.9455f, 0.9397f, 0.9336f,
		0.9272f, 0.9205f, 0.9135f, 0.9063f, 0.8988f, 0.8910f, 0.8829f, 0.8746f,
		0.8660f, 0.8572f, 0.8480f, 0.8387f, 0.8290f, 0.8192f, 0.8090f, 0.7986f,
		0.7880f, 0.7771f, 0.7660f, 0.7547f, 0.7431f, 0.7314f, 0.7193f, 0.7071f,
		0.6947f, 0.6820f, 0.6691f, 0.6561f, 0.6428f, 0.6293f, 0.6157f, 0.6018f,
		0.5878f, 0.5736f, 0.5592f, 0.5446f, 0.5299f, 0.5150f, 0.5000f, 0.4848f,
		0.4695f, 0.4540f, 0.4384f, 0.4226f, 0.4067f, 0.3907f, 0.3746f, 0.3584f,
		0.3420f, 0.3256f, 0.3090f, 0.2924f, 0.2756f, 0.2588f, 0.2419f, 0.2250f,
		0.2079f, 0.1908f, 0.1736f, 0.1564f, 0.1392f, 0.1219f, 0.1045f, 0.0872f,
		0.0698f, 0.0523f, 0.0349f, 0.0175f, 0.0000f, -0.0175f, -0.0349f, -0.0523f,
		-0.0698f, -0.0872f, -0.1045f, -0.1219f, -0.1392f, -0.1564f, -0.1736f, -0.1908f,
		-0.2079f, -0.2250f, -0.2419f, -0.2588f, -0.2756f, -0.2924f, -0.3090f, -0.3256f,
		-0.3420f, -0.3584f, -0.3746f, -0.3907f, -0.4067f, -0.4226f, -0.4384f, -0.4540f,
		-0.4695f, -0.4848f, -0.5000f, -0.5150f, -0.5299f, -0.5446f, -0.5592f, -0.5736f,
		-0.5878f, -0.6018f, -0.6157f, -0.6293f, -0.6428f, -0.6561f, -0.6691f, -0.6820f,
		-0.6947f, -0.7071f, -0.7193f, -0.7314f, -0.7431f, -0.7547f, -0.7660f, -0.7771f,
		-0.7880f, -0.7986f, -0.8090f, -0.8192f, -0.8290f, -0.8387f, -0.8480f, -0.8572f,
		-0.8660f, -0.8746f, -0.8829f, -0.8910f, -0.8988f, -0.9063f, -0.9135f, -0.9205f,
		-0.9272f, -0.9336f, -0.9397f, -0.9455f, -0.9511f, -0.9563f, -0.9613f, -0.9659f,
		-0.9703f, -0.9744f, -0.9781f, -0.9816f, -0.9848f, -0.9877f, -0.9903f, -0.9925f,
		-0.9945f, -0.9962f, -0.9976f, -0.9986f, -0.9994f, -0.9998f, -1.0000f, -0.9998f,
		-0.9994f, -0.9986f, -0.9976f, -0.9962f, -0.9945f, -0.9925f, -0.9903f, -0.9877f,
		-0.9848f, -0.9816f, -0.9781f, -0.9744f, -0.9703f, -0.9659f, -0.9613f, -0.9563f,
		-0.9511f, -0.9455f, -0.9397f, -0.9336f, -0.9272f, -0.9205f, -0.9135f, -0.9063f,
		-0.8988f, -0.8910f, -0.8829f, -0.8746f, -0.8660f, -0.8572f, -0.8480f, -0.8387f,
		-0.8290f, -0.8192f, -0.8090f, -0.7986f, -0.7880f, -0.7771f, -0.7660f, -0.7547f,
		-0.7431f, -0.7314f, -0.7193f, -0.7071f, -0.6947f, -0.6820f, -0.6691f, -0.6561f,
		-0.6428f, -0.6293f, -0.6157f, -0.6018f, -0.5878f, -0.5736f, -0.5592f, -0.5446f,
		-0.5299f, -0.5150f, -0.5000f, -0.4848f, -0.4695f, -0.4540f, -0.4384f, -0.4226f,
		-0.4067f, -0.3907f, -0.3746f, -0.3584f, -0.3420f, -0.3256f, -0.3090f, -0.2924f,
		-0.2756f, -0.2588f, -0.2419f, -0.2250f, -0.2079f, -0.1908f, -0.1736f, -0.1564f,
		-0.1392f, -0.1219f, -0.1045f, -0.0872f, -0.0698f, -0.0523f, -0.0349f, -0.0175f
	};

	g_cos_values = (float*)malloc(sizeof(float) * 360);
	memcpy(g_cos_values, cos_values, sizeof(cos_values));

	g_sin_values = (float*)malloc(sizeof(float) * 360);
	memcpy(g_sin_values, sin_values, sizeof(sin_values));
}

float	ft_cosi(int i)
{
	if (i >= 0)
		return (g_cos_values[i % 360]);
	return (g_cos_values[i % 360 + 360]);
}

float	ft_sini(int i)
{
	if (i >= 0)
		return (g_sin_values[i % 360]);
	return (g_sin_values[i % 360 + 360]);
}

float	ft_cosf(float f)
{
	return (ft_cosi(TO_DEGREE(f)));
}

float	ft_sinf(float f)
{
	return (ft_sini(TO_DEGREE(f)));
}
/*
 * A speed-improved simplex noise algorithm for 2D, 3D and 4D in Java.
 *
 * Based on example code by Stefan Gustavson (stegu@itn.liu.se).
 * Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
 * Better rank ordering method by Stefan Gustavson in 2012.
 *
 * This could be speeded up even further, but it's useful as it is.
 *
 * Version 2012-03-09
 *
 * This code was placed in the public domain by its original author,
 * Stefan Gustavson. You may use it as you see fit, but
 * attribution is appreciated.
 *
 */

#include "maths.h"

t_vec2  grad2[] = {
    {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
    {1, 0}, {-1, 0}, {1, 0}, {-1, 0},
    {0, 1}, {0, -1}, {0, 1}, {0, -1}
};

t_point3  grad3[] = {
  {1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0},
  {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1},
  {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}
};

short     p[] = {151,160,137,91,90,15,
                131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
                190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
                88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
                77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
                102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
                135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
                5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
                223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
                129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
                251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
                49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
                138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

short     *perm = NULL;
short     *permMod12 = NULL;
double    F2 = 0;
double    G2 = 0;
double    F3 = 0;
double    G3 = 0;

/** called on intialization */
void    prepareNoise(void)
{
    int i;
    int from;
    int to;
    short tmp;

    for (i = 0 ; i < 400 ; i++)
    {
        from = rand() % (sizeof(p) / sizeof(float));
        to = rand() % (sizeof(p) / sizeof(float));
        tmp = p[from];
        p[from] = p[to];
        p[to] = tmp;
    }
    
    perm = (short*)malloc(sizeof(short) * 512);
    permMod12 = (short*)malloc(sizeof(short) * 512);

    for (i = 0 ; i < 512 ; i++)
    {
      perm[i] = p[i & 255];
      permMod12[i] = (short)(perm[i] % 12);
    }
    F2 = 0.5f * (sqrt(3.0f) - 1.0f);
    G2 = (3.0f - sqrt(3.0f)) / 6.0f;
    F3 = 1.0f / 3.0f;
    G3 = 1.0f / 6.0f;
}

double  dot(t_point3 p, double x, double y, double z)
{
    return (p.x * x + p.y * y + p.z * z);
}


double noise2(t_vec2 in)
{
    double n0, n1, n2;
    double s = (in.x + in.y) * F2;
    int i = fastfloor(in.x + s);
    int j = fastfloor(in.y + s);
    double t = (i + j) * G2;
    double X0 = i - t;
    double Y0 = j - t;
    double x0 = in.x - X0;
    double y0 = in.y - Y0;
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
      n0 = t0 * t0 * vec2_dot(grad2[gi0], new_vec2(x0, y0));
    }

    double t1 = 0.5 - x1 * x1 - y1 * y1;
    if (t1 < 0)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * vec2_dot(grad2[gi1], new_vec2(x1, y1));
    }

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    if (t2 < 0)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * vec2_dot(grad2[gi2], new_vec2(x2, y2));
    }
    return (70.0 * (n0 + n1 + n2));
}


double  noise3(t_vec3 in)
{
    double n0, n1, n2, n3; // Noise contributions from the four corners
    // Skew the input space to determine which simplex cell we're in
    double s = (in.x + in.y + in.z) * F3; // Very nice and simple skew factor for 3D
    int i = fastfloor(in.x + s);
    int j = fastfloor(in.y + s);
    int k = fastfloor(in.z + s);
    double t = (i + j + k) * G3;
    double X0 = i - t; // Unskew the cell origin back to (x,y,z) space
    double Y0 = j - t;
    double Z0 = k - t;
    double x0 = in.x - X0; // The x,y,z distances from the cell origin
    double y0 = in.y - Y0;
    double z0 = in.z - Z0;
    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
    int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords
    if (x0 >= y0)
    {
        if (y0 >= z0)
        {
            i1 = 1;
            j1 = 0;
            k1 = 0; // X Y Z order
            i2 = 1;
            j2 = 1;
            k2 = 0;
        }
        else if (x0 >= z0)
        {
            i1=1;
            j1=0;
            k1=0;
            i2=1; // X Z Y order
            j2=0;
            k2=1;
        }
        else
        {
            i1 = 0;
            j1 = 0;
            k1 = 1; // Z X Y order
            i2 = 1;
            j2 = 0;
            k2 = 1;
        }
    }
    else // x0 < y0
    {
        if (y0 < z0)
        {
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 0;  // Z Y X order
            j2 = 1;
            k2 = 1;
        }
        else if (x0 < z0)
        {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        }
        else
        {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 1;  // Y X Z order
            j2 = 1;
            k2 = 0;
        }
    }
    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.
    double x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    double y1 = y0 - j1 + G3;
    double z1 = z0 - k1 + G3;
    double x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
    double y2 = y0 - j2 + 2.0f * G3;
    double z2 = z0 - k2 + 2.0f * G3;
    double x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
    double y3 = y0 - 1.0f + 3.0f * G3;
    double z3 = z0 - 1.0f + 3.0f * G3;
    // Work out the hashed gradient indices of the four simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int kk = k & 255;
    int gi0 = permMod12[ii + perm[jj + perm[kk]]];
    int gi1 = permMod12[ii + i1 + perm[jj + j1 + perm[kk + k1]]];
    int gi2 = permMod12[ii + i2 + perm[jj + j2 + perm[kk + k2]]];
    int gi3 = permMod12[ii + 1 + perm[jj + 1 + perm[kk + 1]]];
    // Calculate the contribution from the four corners
    double t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
    if (t0 < 0)
    {
        n0 = 0.0f;
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
    }

    double t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1;
    if (t1 < 0)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
    }

    double t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
    if (t2 < 0)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
    }

    double t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
    if (t3 < 0)
    {
        n3 = 0.0f;
    }
    else
    {
        t3 *= t3;
        n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return (32.0f * (n0 + n1 + n2 + n3));
}
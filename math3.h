#include <math.h>

float PI = 3.141592;

typedef struct {
	int x, y;
} point;

typedef struct {
	float x, y;
} vector2;

typedef struct {
	float x, y, z;
} vector3;

vector3 vec3add(vector3* a, vector3* b) {
	vector3 v = {
		a->x + b->x,
		a->y + b->y,
		a->z + b->z
	};
	return v;
}

vector3 vec3mul(vector3* a, vector3* b) {
	vector3 v = {
		a->x * b->x,
		a->y * b->y,
		a->z * b->z
	};
	return v;
}

typedef struct {
	vector3 org, dst;
} ray3;

typedef struct {
	float
		v11, v12, v13, v14,
		v21, v22, v23, v24,
		v31, v32, v33, v34,
		v41, v42, v43, v44;
} matrix4;

void mat4mul(matrix4* a, matrix4* b, matrix4* out) {
	out->v11 = a->v11 * b->v11 + a->v12 * b->v21 + a->v13 * b->v31 + a->v14 * b->v41;
	out->v12 = a->v11 * b->v12 + a->v12 * b->v22 + a->v13 * b->v32 + a->v14 * b->v42;
	out->v13 = a->v11 * b->v13 + a->v12 * b->v23 + a->v13 * b->v33 + a->v14 * b->v43;
	out->v14 = a->v11 * b->v14 + a->v12 * b->v24 + a->v13 * b->v34 + a->v14 * b->v44;
	out->v21 = a->v21 * b->v11 + a->v22 * b->v21 + a->v23 * b->v31 + a->v24 * b->v41;
	out->v22 = a->v21 * b->v12 + a->v22 * b->v22 + a->v23 * b->v32 + a->v24 * b->v42;
	out->v23 = a->v21 * b->v13 + a->v22 * b->v23 + a->v23 * b->v33 + a->v24 * b->v43;
	out->v24 = a->v21 * b->v14 + a->v22 * b->v24 + a->v23 * b->v34 + a->v24 * b->v44;
	out->v31 = a->v31 * b->v11 + a->v32 * b->v21 + a->v33 * b->v31 + a->v34 * b->v41;
	out->v32 = a->v31 * b->v12 + a->v32 * b->v22 + a->v33 * b->v32 + a->v34 * b->v42;
	out->v33 = a->v31 * b->v13 + a->v32 * b->v23 + a->v33 * b->v33 + a->v34 * b->v43;
	out->v34 = a->v31 * b->v14 + a->v32 * b->v24 + a->v33 * b->v34 + a->v34 * b->v44;
	out->v41 = a->v41 * b->v11 + a->v42 * b->v21 + a->v43 * b->v31 + a->v44 * b->v41;
	out->v42 = a->v41 * b->v12 + a->v42 * b->v22 + a->v43 * b->v32 + a->v44 * b->v42;
	out->v43 = a->v41 * b->v13 + a->v42 * b->v23 + a->v43 * b->v33 + a->v44 * b->v43;
	out->v44 = a->v41 * b->v14 + a->v42 * b->v24 + a->v43 * b->v34 + a->v44 * b->v44;
	//benri/mat4mul.cpp
}

void mat4mulp(matrix4* out, matrix4* mat) {
	matrix4 tmp = *out;
	mat4mul(mat, &tmp, out);
}

float toradian(float angle) {
	return fmod(angle, 360.0) * PI / 180.0;
}

const matrix4 identity4 = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void mat4scale (matrix4* mat, vector3* vec) {
	matrix4 m = identity4;
	m.v11 = vec->x;
	m.v22 = vec->y;
	m.v33 = vec->z;
	mat4mulp(mat, &m);
}

void mat4rotateX(matrix4* mat, float radian) {
	float c = cosf(radian);
	float s = sinf(radian);
	matrix4 m = identity4;
	m.v22 = +c;
	m.v23 = -s;
	m.v32 = +s;
	m.v33 = +c;
	mat4mulp(mat, &m);
}

void mat4rotateY(matrix4* mat, float radian) {
	float c = cosf(radian);
	float s = sinf(radian);
	matrix4 m = identity4;
	m.v11 = +c;
	m.v13 = +s;
	m.v31 = -s;
	m.v33 = +c;
	mat4mulp(mat, &m);
}

void mat4rotateZ(matrix4* mat, float radian) {
	float c = cosf(radian);
	float s = sinf(radian);
	matrix4 m = identity4;
	m.v11 = +c;
	m.v12 = +s;
	m.v21 = -s;
	m.v22 = +c;
	mat4mulp(mat, &m);
}

void mat4move(matrix4* mat, vector3* vec) {
	matrix4 m = identity4;
	m.v14 = vec->x;
	m.v24 = vec->y;
	m.v34 = vec->z;
	mat4mulp(mat, &m);
}

float FOV = 1.73205080757; //30;
point windowsize = { 640, 480 };
float size = 160;

point projection(vector3 vec) {
	float t = FOV * windowsize.y / 2 / vec.z; //temp
	point result = {
		.x = (int)(vec.x * t),
		.y = (int)(vec.y * t),
	};
	result.x += windowsize.x / 2;
	result.y += windowsize.y / 2;
	return result;
}

void mat4apply(matrix4* mat, vector3* vec) {
	vector3 v = *vec;
	vec->x = (v.x * mat->v11) + (v.y * mat->v12) + (v.z * mat->v13) + mat->v14;
	vec->y = (v.x * mat->v21) + (v.y * mat->v22) + (v.z * mat->v23) + mat->v24;
	vec->z = (v.x * mat->v31) + (v.y * mat->v32) + (v.z * mat->v33) + mat->v34;
}

ray3 QUBE[] = {
	{{ +1.0, +1.0, +1.0 }, { +1.0, +1.0, -1.0 }},
	{{ +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 }},
	{{ -1.0, -1.0, +1.0 }, { -1.0, -1.0, -1.0 }},
	{{ -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 }},

	{{ +1.0, +1.0, +1.0 }, { +1.0, -1.0, +1.0 }},
	{{ +1.0, +1.0, -1.0 }, { +1.0, -1.0, -1.0 }},
	{{ -1.0, +1.0, -1.0 }, { -1.0, -1.0, -1.0 }},
	{{ -1.0, +1.0, +1.0 }, { -1.0, -1.0, +1.0 }},

	{{ +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 }},
	{{ +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 }},
	{{ +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 }},
	{{ +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 }},
};

void render_qube_test() {
	int i;
	matrix4 mat = identity4;
	vector3 location = { 0.0, 0.0, 10.0 };
	vector3 size = { 3.0, 1.0, 2.0 };
	mat4scale(&mat, &size);
	mat4rotateY(&mat, toradian((float)frame / 6.0));
	mat4move(&mat, &location);
	
	
	for(i = 0; i < 12; i++) {
		ray3 line = QUBE[i];
		vector3 v1 = line.org;
		vector3 v2 = line.dst;
		mat4apply(&mat, &v1);
		mat4apply(&mat, &v2);
		point p1 = projection(v1);
		point p2 = projection(v2);
		dg_line(dvram, p1.x, p1.y, p2.x, p2.y, RGB(0,255,0));
	}
}


#version 430
mat4 buildTranslate(float, float, float);
mat4 buildRotateX(float);
mat4 buildRotateY(float);
mat4 buildRotateZ(float);
mat4 buildScale(float, float, float);

uniform float angle;
uniform float size;

void main(void){
  if (gl_VertexID == 0){
    gl_Position = buildRotateZ(angle)*buildScale(size, size, size)*vec4(0.25, -0.25, 0.0, 1.0);
  }else if (gl_VertexID == 1){
    gl_Position = buildRotateZ(angle)*buildScale(size, size, size)*vec4(-0.25, -0.25, 0.0, 1.0);
  }else {
    gl_Position = buildRotateZ(angle)*buildScale(size, size, size)*vec4(0.25, 0.25, 0.0, 1.0);
  }
}
mat4 buildTranslate(float x, float y, float z){
  /*
  1 0 0 x
  0 1 0 y
  0 0 1 z
  0 0 0 1
  */
  mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    x, y, z, 1.0);
  return trans;
}

mat4 buildRotateX(float rad){
  /*
  1   0     0     0
  0   cos   sin   0
  0   -sin  cos   0
  0   0     0     1
  */
  mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
                   0.0, cos(rad), -sin(rad), 0.0,
                   0.0, sin(rad), cos(rad), 0.0,
                   0.0, 0.0, 0.0, 1.0);
  return xrot;
}

mat4 buildRotateY(float rad){
  mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
                   0.0, 1.0, 0.0, 0.0,
                   -sin(rad), 0.0, cos(rad), 0.0,
                   0.0, 0.0, 0.0, 1.0);
  return yrot;
}

mat4 buildRotateZ(float rad){
  mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                   sin(rad), cos(rad), 0.0, 0.0,
                   0.0, 0.0, 1.0, 0.0,
                   0.0, 0.0, 0.0, 1.0);
  return zrot;
}

mat4 buildScale(float x, float y, float z){
  mat4 scale = mat4(x, 0.0, 0.0, 0.0,
                    0.0, y, 0.0, 0.0,
                    0.0, 0.0, z, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  return scale;
}

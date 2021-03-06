#version 430
layout(location=0) in vec3 position;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf; //Time factor

out vec4 varyingColor;

mat4 buildTranslate(float, float, float);
mat4 buildRotateX(float);
mat4 buildRotateY(float);
mat4 buildRotateZ(float);
mat4 buildScale(float, float, float);

void main(void){
    //Change for each cube
    float i = gl_InstanceID + tf/2;
    //Translation parameter
    float a = sin(2.0*i)*8.0;
    float b = sin(3.0*i)*8.0;
    float c = sin(4.0*i)*8.0;
    
    mat4 localRotX = buildRotateX(1.75*i);
    mat4 localRotY = buildRotateY(1.75*i);
    mat4 localRotZ = buildRotateZ(1.75*i);
    mat4 localTrans = buildTranslate(a, b, c);
    
    mat4 modified_m_matrix = m_matrix * localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * modified_m_matrix;
    
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
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

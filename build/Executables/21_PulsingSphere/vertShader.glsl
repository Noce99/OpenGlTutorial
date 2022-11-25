#version 430
layout(location=0) in vec3 position;
uniform float time;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;
double cosa, sina, cosb, sinb;
double r;
double Dx, Dy, Dz;
vec3 positionnew;

void main(void){
    cosa = sqrt(position.x*position.x+position.y*position.y)/sqrt(position.x*position.x+position.y*position.y+position.z*position.z);
    sina = position.z/sqrt(position.x*position.x+position.y*position.y+position.z*position.z);
    cosb = position.x/sqrt(position.x*position.x+position.y*position.y);
    sinb = position.y/sqrt(position.x*position.x+position.y*position.y);
    #1
    if(sin(time)>0){ 
        r = (1.5-sqrt(position.x*position.x+position.y*position.y+position.z*position.z))*abs(sin(time));
    }else{
        r = 0;
    }
    #2
    //r = (1.5-sqrt(position.x*position.x+position.y*position.y+position.z*position.z))*abs(sin(time));
    #3
    //r = (1.5-sqrt(position.x*position.x+position.y*position.y+position.z*position.z))*sin(time);
    
    Dx=r*cosa*cosb;
    Dy=r*cosa*sinb;
    Dz=r*sina;
    positionnew = vec3(position.x+Dx, position.y+Dy, position.z+Dz);
    gl_Position = proj_matrix * mv_matrix * vec4(positionnew, 1.0);
    varyingColor = vec4(cosa*cosb, cosa*sinb, sina, 1.0) *0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

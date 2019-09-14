#version 330 core

// https://www.shadertoy.com/view/4dc3D8
// update this guys work and make it more readable. explain the math

#define SCALE 20.
#define SPEED 9.
#define FREQUENCY .3

float d;
#define C(p)  min(1., sqrt(10.*abs(length(p-.5)-.4)))
#define D(p,o)  ( (d=length(p-o)*5.)<=.6 ? d:1. )

uniform float time;
uniform float deltaTime;
in vec4 gl_FragCoord;
out vec4 O;

void main()
{
  vec2 U = gl_FragCoord.xy;
  vec2 R = vec2(800.0f, 600.0f),
           p = SCALE*(U.xy+U.xy/R)/R.y,
           f = fract(p);
  p=floor(p);
  float t=(p.x+p.y)*FREQUENCY
         +time*SPEED;
  vec2 o=vec2(cos(t),sin(t))*.4+.5;
  O.xyz = vec3(C(f)*D(f,o));
}

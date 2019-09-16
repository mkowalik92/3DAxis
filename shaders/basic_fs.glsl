#version 330 core

//#define SCALE 20.
//#define SPEED 9.
//#define FREQUENCY .3

#define SCALE 2.0f
//#define

//#define C(p)  min(1., sqrt(10.*abs(length(p-.5)-.4)))
//#define D(p,o)  ( (d=length(p-o)*5.)<=.6 ? d:1. )

uniform float iTime; // time since engine start in seconds
uniform float iTimeDelta; // time since last frame in seconds
uniform vec2 iResolution; // updated once at glfw initialization and [when window is resized]

in vec4 gl_FragCoord;
out vec4 fragColor;

//float d;

float circle(vec2 UV, vec2 centerPoint, float radius)
{
  vec2 distance = UV - centerPoint;
  return 1.0f - smoothstep(
    radius - (radius * 0.01f),
    radius + (radius * 0.01f),
    dot(distance, distance) * 10.0f
    );
}

float XGreaterThanY(float x, float y)
{
  return max(sign(x - y), 0.0f);
}

void main()
{
  //vec2 U = gl_FragCoord.xy;
  //vec2 R = iResolution;
  //ec2 p = SCALE * (U.xy + U.xy / R ) / R.y;
  //vec2 f = fract(p);
  //p=floor(p);
  //float t = (p.x + p.y) * FREQUENCY + iTime * SPEED;
  //vec2 o = vec2(cos(t), sin(t)) * 0.4f + 0.5f;
  //fragColor.xyz = vec3(C(f) * D(f, o));

  vec2 UV = gl_FragCoord.xy/iResolution;
  UV.x *= iResolution.x/iResolution.y; // Account for screen resolution
  vec2 centerPoint = vec2(0.5f, 0.5f);
  centerPoint.x *= (iResolution.x / iResolution.y); // Account for screen resolution
  float radius = 0.25f;
  //float distanceFromCenter = distance(UV, centerPoint);
  float dist = circle(UV, centerPoint, 0.25f);
  float colorValue = XGreaterThanY(dist, radius);
  fragColor = vec4( colorValue * dist);
  //fragColor = vec4( vec3(colorValue), 1.0f );
  //fragColor = vec4(max(frac(vec3(0.0f, 1.0f, 0.0f) * colorValue), vec3(1.0f, 0.0f, 0.0f)), 1.0f) - colorValue;
  //abs(sign(colorValue))
  // if (dist > radius)
  // {
  //   fragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  // }
  // else
  // {
  //   //fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
  //   fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
  // }
}

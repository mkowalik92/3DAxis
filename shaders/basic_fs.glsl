#version 330 core

uniform float time;
in vec4 gl_FragCoord;
out vec4 FragColor;

float plot(vec2 st, float pct)
{
  return smoothstep(pct - 0.02f, pct, st.y) - smoothstep(pct, pct + 0.02f, st.y);
}

void main()
{
  vec2 resolution = vec2(800.0f, 600.0f);
  vec2 st = gl_FragCoord.xy/resolution;
  float y = smoothstep(0.1f, 0.9f, st.x);
  vec3 color = vec3(y);
  float pct = plot(st, y);
  color = (1.0f - pct) * color + pct * vec3(0.0f, 1.0f, 0.0f);
  FragColor = vec4(color, 1.0f);
}

attribute vec3 position;
attribute vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 mvpMatrix;

varying vec4 outColor;

void main(void)
{
	gl_Position = mvpMatrix * vec4(position, 1.0);
	outColor = color;
}
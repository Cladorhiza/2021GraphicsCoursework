#shader vertex
#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Colour;
layout(location = 2) in vec2 in_TexCoords;
out vec4 ex_Color;
out vec2 ex_TexCoords;

uniform vec3 worldPosition;
uniform mat4 ProjectionMatrix;



void main()
{

	//mat4 model = mat4(
	//	1.0f, 0.0f, 0.0f, worldPosition[0],
	//	0.0f, 1.0f, 0.0f, worldPosition[1],
	//	0.0f, 0.0f, 1.0f, worldPosition[2],
	//	0.0f, 0.0f, 0.0f, 1.0f
	//);

	gl_Position = ProjectionMatrix * vec4(in_Position + worldPosition, 1.0);
	ex_Color = vec4(in_Colour, 1.0);
	ex_TexCoords = in_TexCoords;
};

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec2 ex_TexCoords;
out vec4 out_Color;

uniform sampler2D diffuseMap;

void main()
{
	out_Color = texture(diffuseMap, ex_TexCoords);
};

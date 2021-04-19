#shader vertex
#version 330 core
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Colour;
layout(location = 2) in vec2 in_TexCoords;
layout(location = 3) in float in_TexID;
out vec4 ex_Color;
out vec2 ex_TexCoords;
out float ex_TexID;

uniform vec3 WorldPosition;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform float Rotation;



void main()
{
	mat3 ModelMatrix = mat3(cos(Rotation), -sin(Rotation), 0.f,
					        sin(Rotation), cos(Rotation) , 0.f,
					        0.f          , 0.f           , 1.f);

	gl_Position = ProjectionMatrix * ViewMatrix * vec4((ModelMatrix * in_Position) + WorldPosition, 1.0);
	ex_Color = vec4(in_Colour, 1.0);
	ex_TexCoords = in_TexCoords;
	ex_TexID = in_TexID;
};

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec2 ex_TexCoords;
in float ex_TexID;
out vec4 out_Color;

uniform sampler2D diffuseMap[32];

void main()
{
	int index = int(ex_TexID);
	out_Color = texture(diffuseMap[index], ex_TexCoords);
};

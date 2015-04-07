uniform vec4 rightDiffuseColor;
uniform vec4 leftDiffuseColor;
varying vec3 vertex;
varying vec3 normal;

void main() 
{
	int cubes = 10;
	vec4 white = vec4(1.0,1.0,1.0,1.0);
	vec4 used_color;
	if (vertex.x < 0)
	{
		used_color = leftDiffuseColor;
	}
	else
	{
		used_color = rightDiffuseColor;
	}
	int col = int(abs(vertex.x + 1.0) * cubes);
	int row = int(abs(vertex.y + 1.0) * cubes);
	if ((row + col) % 2 == 0) 
	{
		used_color = white - used_color;
	}
	
	vec3 light_dir = vec3(normalize(gl_LightSource[0].position - vertex));
	vec3 e = normalize(-vertex);
	vec3 reflection_dir = normalize(reflect(-light_dir , normal));
	
	float specPow = 10.0f;
	
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	vec4 diffuse = used_color * gl_LightSource[0].diffuse * max(dot(normal,light_dir), 0.0);
	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(dot(reflection_dir,e),0.0),0.3*specPow);
	
	gl_FragColor = clamp(ambient + diffuse, 0.0, 1.0);
}
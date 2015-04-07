varying vec4 vertex_color;

void main(void) {
	vec3 vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = ftransform();
	
	vec3 light_dir = vec3(normalize(gl_LightSource[0].position - vertex));
	vec3 e = normalize(-vertex);
	vec3 reflection_dir = normalize(reflect(-light_dir , normal));
	
	float specPow = 10.0f;
	
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
   	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * max(dot(normal,light_dir), 0.0);
   	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(max(dot(reflection_dir,e),0.0),0.3*specPow);
   	
   	vertex_color = clamp(ambient + diffuse + specular, 0.0, 1.0);	
}
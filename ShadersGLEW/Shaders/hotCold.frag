varying vec3 lightDir,normal;
uniform vec4 coldColor;
uniform vec4 hotColor;

void main()
{

	float intensity;	
	
	// normalizing the lights position to be on the safe side
	// normalizing the light direction to be on the safe side
	vec3 normalized_normal = normalize(normal);
	vec3 normalized_light_dir = normalize(lightDir);
	
	intensity = dot(normalized_light_dir, normalized_normal);
	
	vec4 color = hotColor * intensity + (1.0 - intensity) * coldColor;
	
	gl_FragColor = color;
} 

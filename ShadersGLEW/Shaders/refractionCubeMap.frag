varying vec3 Normal;
varying vec3 EyeDir;

uniform samplerCube cubeMap;

void main(void)
{
 	const float refractionRatio = 1.0 / 1.52;
    vec3 refractedDirection = normalize(refract(EyeDir, normalize(Normal), refractionRatio));
    refractedDirection.y = -refractedDirection.y;
    vec4 fragColor = textureCube(cubeMap, refractedDirection);
    gl_FragColor = fragColor;
}
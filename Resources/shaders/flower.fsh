varying vec4 v_color; // i“ü—ÍjF

uniform vec2 center;

void main(){

	vec2 p = gl_FragCoord.xy - center;
	float col;
	col = p.x;
	gl_FragColor = vec4(col/250,col/250,col/250 ,1);

	//gl_FragColor *= v_color;
}
varying vec4 v_color; // （入力）色

void main(){

	//                    0～1で指定
	gl_FragColor = vec4(gl_FragCoord.x/1280, gl_FragCoord.y/720, 0 ,1);

	//gl_FragColor *= v_color;
}
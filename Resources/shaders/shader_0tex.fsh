varying vec4 v_color; // （入力）色

void main(){

	gl_FragColor = v_color;

	//                   R    G    B    A
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
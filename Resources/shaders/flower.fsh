varying vec4 v_color; // �i���́j�F

void main(){

	//                    0�`1�Ŏw��
	gl_FragColor = vec4(gl_FragCoord.x/1280, gl_FragCoord.y/720, 0 ,1);

	//gl_FragColor *= v_color;
}
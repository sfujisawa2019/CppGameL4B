varying vec4 v_color; // �i���́j�F

// �i���́j�}�`�̒��S���W
uniform vec2 center;
// �i���́j�����A�c��/2
uniform vec2 size_div2;

void main(){
	// �`��s�N�Z���̍��W�Ɛ}�`�̒��S�_�̍��W�������v�Z(-250�`+250)
	vec2 p = gl_FragCoord.xy - center;
	float col;
	// ���l�͈̔͂�(-1.0�`+1.0)�ɕϊ�
	col = p.x / size_div2.x;
	gl_FragColor = vec4(col,col,col ,1);
}
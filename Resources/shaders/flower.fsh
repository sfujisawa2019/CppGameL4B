varying vec4 v_color; // �i���́j�F

// �i���́j�}�`�̒��S���W
uniform vec2 center;
// �i���́j�����A�c��/2
uniform vec2 size_div2;
// �i���́j�o�ߕb��
uniform float time;

void main(){
	// �`��s�N�Z���̍��W�Ɛ}�`�̒��S�_�̍��W�������v�Z(-250�`+250)
	vec2 p = gl_FragCoord.xy - center;
	// (-1�`+1)
	p /= size_div2;

	// ���S����̋���(0�`1)
	float len = length(p);

	float col = 1.0;

	float angle = atan(p.y, p.x);

	// �o�ߎ��ԂŐF�����߂�(-1�`+1)
	//float w = sin(sin(time*3.14)+3.14/2);
	float w = cos(sin(time*3.14));
	//(0�`1)
	w = w / 2.0 + 0.5;

	col = len;
	// �F���]
	col = 1 - col;
	// sin�ɂ��ϓ���������
	col *= w;

	gl_FragColor = vec4(col,col,col,1);
}
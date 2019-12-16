varying vec4 v_color; // �i���́j�F

// �i���́j�}�`�̒��S���W
uniform vec2 center;
// �i���́j�����A�c��/2
uniform vec2 size_div2;

void main(){
	// �`��s�N�Z���̍��W�Ɛ}�`�̒��S�_�̍��W�������v�Z(-250�`+250)
	vec2 p = gl_FragCoord.xy - center;
	// �`��s�N�Z���̍��W�Ɛ}�`�̒��S�_�̋������v�Z(0�`250)
	float len = length(p);
	float col;
	//(0.0�`1.0)�ɕϊ��@�������A�����̍ő�l�Ŋ���
	col = len / size_div2.x;

	// ���l�͈̔͂�(-1.0�`+1.0)�ɕϊ�
	//col = p.y / size_div2.y;
	// �}�C�i�X���v���X�ɕϊ�(1.0�`0.0�`1.0)
	//col = abs(col);
	// �������](0.0�`1.0�`0.0)
	col = 1.0 - col;

	gl_FragColor = vec4(col,col,col ,1);
}
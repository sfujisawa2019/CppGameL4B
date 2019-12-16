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
	float col = 1.0;
	float alpha = 1.0;
	float alpha2 = 1.0;
	//(0.0�`1.0)�ɕϊ��@�������A�����̍ő�l�Ŋ���
	alpha2 = len / size_div2.x;
	// �}�C�i�X���v���X�ɕϊ�(1.0�`0.0�`1.0)
	alpha2 = abs(alpha2);
	// �������](0.0�`1.0�`0.0)
	alpha2 = 1.0 - alpha2;
	// 0���傫�����̂͑S��1�ɂ���
	alpha2 = sign(alpha2);

	// X������̊p�x�����W�A���ŋ��߂�(-�΁`+��)
	float angle = atan(p.y, p.x);
	// �p�x��x���@�ɕϊ�����(-180�`+180)
	float deg = degrees(angle);
	// �}�C�i�X���v���X�ɕϊ�(180�`180)
	deg = abs(deg);
	// 30�x�ȏ�Ȃ�1�@�����Ȃ�0
	alpha = step(30, deg);
	// ���b�Ɖ~�ŋ���1�̕����̂݁A1�Ƃ��Ďc��
	alpha = alpha * alpha2;

	gl_FragColor = vec4(col,col,0,alpha);
}
varying vec4 v_color; // �i���́j�F
varying vec2 v_texCoord;

// �i���́j�}�`�̒��S���W
uniform vec2 center;
// �i���́j�����A�c��/2
uniform vec2 size_div2;
// �i���́j�o�ߕb��
uniform float time;

uniform sampler2D sampler;

float u(float x) 
{
	return (x > 0.0) ? 1.0 : 0.0;
}

void main(){
	// �`��s�N�Z���̍��W�Ɛ}�`�̒��S�_�̍��W�������v�Z(-250�`+250)
	vec2 p = gl_FragCoord.xy - center;
	// (-1�`+1)
	p /= size_div2;

	// ���S����̊p�x
	float a = atan(p.y, p.x);

	// ���S����̋���(0�`1)
	float r = length(p);

	float w = cos(time*3.14 - r * 2.0);
	
	float h = 0.5 + 0.5 * cos(12.0*a - w*7.0 + r*8.0);

	float d = 0.25 + 0.75 * pow(h,1.0*r)*(0.7+0.3*w);

	float col = u(d-r) * sqrt(1.0-r/d)*r*2.5;

	col *= 1.25+0.25*cos((12.0*a-w*7.0+r*8.0)/2.0);
	col *= 1.0 - 0.35*(0.5+0.5*sin(r*30))*(0.5+0.5*cos(12.0*a-w*7.0+r*8.0));

	// ���H�ׁ̈AUV���W���R�s�[
	vec2 texCoord = v_texCoord;
	// UV���W��������
	texCoord.y += sin(gl_FragCoord.x * 50) * 0.005;
	// ��������UV���W�Ńe�N�X�`���}�b�s���O
	vec4 texcolor = texture2D(sampler, texCoord);
	gl_FragColor = texcolor * v_color;

	//gl_FragColor = vec4(
	//col,
	//col-h*0.5+r*0.2+0.35*h*(1.0-r),
	//col-h*r + 0.1*h*(1.0-r),
	//1.0) * texcolor;
}
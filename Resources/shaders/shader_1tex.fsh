varying vec4 v_color; // �i���́j�F
varying vec2 v_texCoord; //(����)�e�N�X�`�����W
uniform sampler2D sampler;//(����)�e�N�X�`�����

void main(){

	vec4 texcolor = texture2D(sampler, v_texCoord);
	gl_FragColor = texcolor * v_color;
}
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;//(����)�e�N�X�`�����W
varying vec4 v_color; // �i�o�́j�F
varying vec2 v_texCoord;

void main(){
	gl_Position = a_position;
	v_color = a_color;
	v_texCoord = a_texCoord;
}
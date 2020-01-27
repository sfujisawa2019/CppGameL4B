attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

uniform mat4 u_wvp_matrix;

varying vec4 v_color; // （出力）色
varying vec2 v_texCoord;

void main(){
	gl_Position = u_wvp_matrix * a_position;
	v_color = a_color;
	v_texCoord = a_texCoord;
}
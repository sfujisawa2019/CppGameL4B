attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;//(入力)テクスチャ座標
varying vec4 v_color; // （出力）色
varying vec2 v_texCoord;

void main(){
	gl_Position = a_position;
	v_color = a_color;
	v_texCoord = a_texCoord;
}
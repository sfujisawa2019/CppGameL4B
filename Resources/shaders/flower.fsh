varying vec4 v_color; // （入力）色

// （入力）図形の中心座標
uniform vec2 center;
// （入力）横幅、縦幅/2
uniform vec2 size_div2;
// （入力）経過秒数
uniform float time;

void main(){
	// 描画ピクセルの座標と図形の中心点の座標を差を計算(-250～+250)
	vec2 p = gl_FragCoord.xy - center;
	// (-1～+1)
	p /= size_div2;

	float col = 1.0;

	float angle = atan(p.y, p.x);

	// 経過時間で色を決める(-1～+1)
	float w = sin(sin(time*3.14) - angle);
	//(0～1)
	col = w / 2.0 + 0.5;

	gl_FragColor = vec4(col,col,col,1);
}
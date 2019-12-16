varying vec4 v_color; // （入力）色

// （入力）図形の中心座標
uniform vec2 center;
// （入力）横幅、縦幅/2
uniform vec2 size_div2;

void main(){
	// 描画ピクセルの座標と図形の中心点の座標を差を計算(-250～+250)
	vec2 p = gl_FragCoord.xy - center;
	// 描画ピクセルの座標と図形の中心点の距離を計算(0～250)
	float len = length(p);
	float col;
	//(0.0～1.0)に変換　長さを、長さの最大値で割る
	col = len / size_div2.x;

	// 数値の範囲を(-1.0～+1.0)に変換
	//col = p.y / size_div2.y;
	// マイナスをプラスに変換(1.0～0.0～1.0)
	//col = abs(col);
	// 白黒反転(0.0～1.0～0.0)
	col = 1.0 - col;

	gl_FragColor = vec4(col,col,col ,1);
}
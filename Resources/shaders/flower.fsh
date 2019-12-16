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
	float col = 1.0;
	float alpha = 1.0;
	float alpha2 = 1.0;
	//(0.0～1.0)に変換　長さを、長さの最大値で割る
	alpha2 = len / size_div2.x;
	// マイナスをプラスに変換(1.0～0.0～1.0)
	alpha2 = abs(alpha2);
	// 白黒反転(0.0～1.0～0.0)
	alpha2 = 1.0 - alpha2;
	// 0より大きいものは全て1にする
	alpha2 = sign(alpha2);

	// X軸からの角度をラジアンで求める(-π～+π)
	float angle = atan(p.y, p.x);
	// 角度を度数法に変換する(-180～+180)
	float deg = degrees(angle);
	// マイナスをプラスに変換(180～180)
	deg = abs(deg);
	// 30度以上なら1　未満なら0
	alpha = step(30, deg);
	// 怪獣と円で共に1の部分のみ、1として残る
	alpha = alpha * alpha2;

	gl_FragColor = vec4(col,col,0,alpha);
}
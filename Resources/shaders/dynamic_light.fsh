varying vec4 v_color; // （入力）色
varying vec2 v_texCoord;

// （入力）図形の中心座標
uniform vec2 center;
// （入力）横幅、縦幅/2
uniform vec2 size_div2;
// （入力）経過秒数
uniform float time;

uniform sampler2D sampler;

float u(float x) 
{
	return (x > 0.0) ? 1.0 : 0.0;
}

void main(){
	// 描画ピクセルの座標と図形の中心点の座標を差を計算(-250～+250)
	vec2 p = gl_FragCoord.xy - center;
	// (-1～+1)
	p /= size_div2;

	// 中心からの角度
	float a = atan(p.y, p.x);

	// 中心からの距離(0～1)
	float r = length(p);

	float w = cos(time*3.14 - r * 2.0);
	
	float h = 0.5 + 0.5 * cos(12.0*a - w*7.0 + r*8.0);

	float d = 0.25 + 0.75 * pow(h,1.0*r)*(0.7+0.3*w);

	float col = u(d-r) * sqrt(1.0-r/d)*r*2.5;

	col *= 1.25+0.25*cos((12.0*a-w*7.0+r*8.0)/2.0);
	col *= 1.0 - 0.35*(0.5+0.5*sin(r*30))*(0.5+0.5*cos(12.0*a-w*7.0+r*8.0));

	// 加工の為、UV座標をコピー
	vec2 texCoord = v_texCoord;
	// UV座標をいじる
	texCoord.y += sin(gl_FragCoord.x * 50) * 0.005;
	// いじったUV座標でテクスチャマッピング
	vec4 texcolor = texture2D(sampler, texCoord);
	gl_FragColor = texcolor * v_color;

	//gl_FragColor = vec4(
	//col,
	//col-h*0.5+r*0.2+0.35*h*(1.0-r),
	//col-h*r + 0.1*h*(1.0-r),
	//1.0) * texcolor;
}
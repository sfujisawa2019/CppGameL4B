/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ShaderNode.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ShaderNodeScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShaderNode::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_pProgram = new GLProgram;
	m_pProgram->initWithFilenames("shaders/flower.vsh", "shaders/flower.fsh");

	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);

	m_pProgram->link();
	m_pProgram->updateUniforms();

	uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");
	m_pTexture = Director::getInstance()->getTextureCache()->addImage("texture.jpg");

	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(), "u_wvp_matrix");
	uniform_center = glGetUniformLocation(m_pProgram->getProgram(), "center");
	uniform_size_div2 = glGetUniformLocation(m_pProgram->getProgram(), "size_div2");
	uniform_time = glGetUniformLocation(m_pProgram->getProgram(), "time");

	Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

	counter = 0;

    return true;
}

// LayerColorの構造を真似て、
// drawとonDrawに分離する
void ShaderNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	// 「onDrawを呼び出す」というカスタムコマンドを予約
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	Size size = getContentSize();

	m_pos[0] = Vec3(-size.width / 2.0f, -size.height / 2.0f, 0);
	m_pos[1] = Vec3(-size.width / 2.0f,  size.height / 2.0f, 0);
	m_pos[2] = Vec3( size.width / 2.0f, -size.height / 2.0f, 0);
	m_pos[3] = Vec3( size.width / 2.0f,  size.height / 2.0f, 0);

	m_color[0] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[1] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[2] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[3] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);

	m_uv[0] = Vec2(0, 1);
	m_uv[1] = Vec2(0, 0);
	m_uv[2] = Vec2(1, 1);
	m_uv[3] = Vec2(1, 0);

	Mat4 matProjection;

	matProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

	m_matWVP = matProjection * transform;

	unsigned int total = _director->getTotalFrames();
	float inter = _director->getAnimationInterval();
	m_time = total * inter;
}

void ShaderNode::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	// 半透明合成
	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//GL::blendFunc(GL_ONE, GL_ONE);

	//GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR|GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	m_pProgram->use();

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, m_pos);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, m_color);
	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, m_uv);

	//glUniform1i(uniform_sampler, 0);
	//GL::bindTexture2D(m_pTexture->getName());

	glUniformMatrix4fv(uniform_wvp_matrix, 1, GL_FALSE, m_matWVP.m);
	Vec2 center = this->getPosition();
	glUniform2f(uniform_center, center.x, center.y);
	//glUniform2fv(uniform_center, 1, (float*)&center);
	Size size = this->getContentSize();
	glUniform2f(uniform_size_div2, size.width / 2.0f, size.height / 2.0f);
	glUniform1f(uniform_time, m_time);

	// 描画命令
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}


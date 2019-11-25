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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        //this->addChild(sprite, 0);
    }

	m_pProgram = new GLProgram;
	m_pProgram->initWithFilenames("shaders/shader_0tex.vsh", "shaders/shader_0tex.fsh");

	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);

	m_pProgram->link();
	m_pProgram->updateUniforms();

	uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");
	m_pTexture = Director::getInstance()->getTextureCache()->addImage("texture.jpg");

	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(), "u_wvp_matrix");

	Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

	counter = 0;

    return true;
}

// LayerColor�̍\����^���āA
// draw��onDraw�ɕ�������
void HelloWorld::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	// �uonDraw���Ăяo���v�Ƃ����J�X�^���R�}���h��\��
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	counter++;

	const float x = 50.0f;
	const float y = 50.0f;
	const float z = 50.0f;

	m_pos[0] = Vec3(-x, -y, 0);
	m_pos[1] = Vec3(-x, y, 0);
	m_pos[2] = Vec3(x, -y, 0);
	m_pos[3] = Vec3(x, y, 0);

	m_color[0] = Vec4(1, 0, 0, 1);
	m_color[1] = Vec4(1, 0, 0, 1);
	m_color[2] = Vec4(1, 0, 0, 1);
	m_color[3] = Vec4(1, 0, 0, 1);

	m_uv[0] = Vec2(0, 1);
	m_uv[1] = Vec2(0, 0);
	m_uv[2] = Vec2(1, 1);
	m_uv[3] = Vec2(1, 0);

	static float yaw = 0.0f;
	yaw += CC_DEGREES_TO_RADIANS(3.0f);
	Mat4 matProjection;
	Mat4 matView;
	
	Mat4 matTrans, matScale, matRot;
	Mat4 matRotX, matRotY, matRotZ;
	Mat4 matWorld = Mat4::IDENTITY;

	matProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	matView = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	Mat4::createTranslation(Vec3(1280 / 2.0f, 720 / 2.0f, 0.0f), &matTrans);

	//CC_DEGREES_TO_RADIANS(30.0f)
	Mat4::createRotationZ(0, &matRotZ); // ���[��
	Mat4::createRotationX(0, &matRotX); // �s�b�`�i�p�j
	Mat4::createRotationY(yaw, &matRotY); // ���[�i���ʊp�j
	matRot = matRotY * matRotX * matRotZ;

	Mat4::createScale(Vec3(2.0f, 2.0f, 2.0f), &matScale);

	matWorld = matTrans * matRot * matScale;

	m_matWVP = matProjection * matView * matWorld;
}

void HelloWorld::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	//GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR|GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	m_pProgram->use();

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, m_pos);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, m_color);
	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, m_uv);

	//glUniform1i(uniform_sampler, 0);
	//GL::bindTexture2D(m_pTexture->getName());

	glUniformMatrix4fv(uniform_wvp_matrix, 1, GL_FALSE, m_matWVP.m);

	// �`�施��
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


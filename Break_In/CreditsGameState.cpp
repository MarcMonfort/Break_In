#include "CreditsGameState.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Game.h"


void CreditsGameState::init()
{
	initShaders();

	spritesheet.loadFromFile("images/Credits3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	background->setPosition(glm::vec2(0, 0));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void CreditsGameState::update(int deltaTime)
{
}

void CreditsGameState::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
}

void CreditsGameState::keyPressed(int key)
{
	if (key == 27) // Escape code
	{
		Game::instance().popGameState();
		Game::instance().pushGameState(&MenuGameState::instance());
	}

	keys[key] = true;
}

void CreditsGameState::keyReleased(int key)
{
	keys[key] = false;
}

void CreditsGameState::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void CreditsGameState::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void CreditsGameState::mouseMove(int x, int y)
{
}

void CreditsGameState::mousePress(int button)
{
}

void CreditsGameState::mouseRelease(int button)
{
}

void CreditsGameState::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
